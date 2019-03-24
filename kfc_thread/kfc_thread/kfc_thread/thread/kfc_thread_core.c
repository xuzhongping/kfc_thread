//
//  kfc_thread.c
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#include "kfc_thread_core.h"
#include <assert.h>
#include "kfc_switch.h"
#include "kfc_driver.h"
#include <stdlib.h>
#include <string.h>


#pragma mark - declaration

#define KFC_PAGE_SIZE 4096
#define KFC_PCB_SIZE KFC_PAGE_SIZE * 3


static kfc_scheduler _scheduler;

#pragma mark - util

kfc_thread * _kfc_running_thread(){
    return _scheduler.runnning_thread;
}

kfc_thread * _kfc_main_thread(){
    return _scheduler.main_thread;
}

#pragma mark - entry

static void _kfc_thread_entry(kfc_thread_func *func,void *func_arg){
    _KFC_DRIVER_OPEN;
    func(func_arg);
}

static void _kfc_thread_died(void){
    _KFC_DRIVER_CLOSE;
    kfc_thread *died_thread = _scheduler.runnning_thread;
    _scheduler.runnning_thread = NULL;
    kfc_list_elem *thread_tag = _kfc_list_pop(&_scheduler.ready_list);
    kfc_thread *next = elem2entry(kfc_thread, ready_tag, thread_tag);
    next->status = KFC_THREAD_RUNNING;
    _scheduler.runnning_thread = next;
    _kfc_list_remove(&_scheduler.total_list, &died_thread->total_tag);
    KFC_ALIGN_RSP_16; 
    free(died_thread);
    if (next->first_call & 0x1) {
        _kfc_died_switch(next);
    }else{
        _kfc_died_first_switch(next);
    }
}

#pragma mark - init

/**
 初始化线程pcb

 @param thread 线程
 @param name 名称
 @param priority 优先级
 */
static void _kfc_thread_init(kfc_thread *thread,char *name,uint priority,uint first){
    memset(thread,0,KFC_PCB_SIZE);
    strcpy(thread->name,name);
//    strcpy(thread->ready_tag.name, name);
//    strcpy(thread->total_tag.name, name);
    thread->first_call = first;
    thread->priority = priority;
    thread->stack_point = (uint64_t *)((uint64_t)thread + KFC_PCB_SIZE);
    thread->ticks = priority;
    thread->thread_ticks = 0;
    thread->stack_guard = KFC_STACK_MAGIC;
}


/**
 初始化线程栈

 @param thread 线程
 @param func 线程调用函数
 @param func_arg 函数参数
 */
static void _kfc_thread_stack_init(kfc_thread *thread,kfc_thread_func *func,void *func_arg){
    thread->stack_point = (uint64_t *)((uint64_t)(thread->stack_point) - sizeof(kfc_thread_stack));
    // 0x00007f912d009600
//    thread->stack_point -= sizeof(kfc_thread_stack); // sizeof(kfc_thread_stack) = 160
    // 0x00007f912d009100
    kfc_thread_stack *thread_stack = (kfc_thread_stack *)thread->stack_point;
    thread_stack->rip = _kfc_thread_entry;
    thread_stack->func = func;
    thread_stack->func_arg = func_arg;
    thread_stack->died = _kfc_thread_died;
}


/**
 构建调度器
 */
static void _kfc_make_scheduler(){
    kfc_thread *main_thread = (kfc_thread *)calloc(KFC_PCB_SIZE,0);
    _scheduler.main_thread = main_thread;
    _scheduler.runnning_thread = main_thread;
    _scheduler.total_ticks = 0;
    _kfc_thread_init(main_thread, "main", 5,1);
    _kfc_list_init(&_scheduler.total_list);
    _kfc_list_init(&_scheduler.ready_list);
    _kfc_list_append(&_scheduler.total_list, &main_thread->total_tag);
}


/**
 开始调度线程
 */
void _kfc_thread_schedule(){
    kfc_thread *cur = _scheduler.runnning_thread;
    _scheduler.runnning_thread = NULL;
    if (cur->status == KFC_THREAD_RUNNING) {
        assert(!_kfc_list_find(&_scheduler.ready_list, &cur->ready_tag));
        _kfc_list_append(&_scheduler.ready_list, &cur->ready_tag);
        cur->ticks = cur->priority;
        cur->status = KFC_THREAD_READY;
    }
    assert(!_kfc_list_empty(&_scheduler.ready_list));
    
    kfc_list_elem *thread_tag = _kfc_list_pop(&_scheduler.ready_list);
    kfc_thread *next = elem2entry(kfc_thread, ready_tag, thread_tag);
    next->status = KFC_THREAD_RUNNING;
    _scheduler.runnning_thread = next;
    
    if (next->first_call & 0x1) {
        _kfc_switch(cur, next);
    }else{
        _kfc_first_switch(cur, next);
    }
}


#pragma mark - public


/**
 初始化线程库
 */
void kfc_thread_init(){
    _kfc_make_scheduler();
}

kfc_thread * kfc_thread_start(char *name,uint priority,kfc_thread_func *func,void *func_arg){
    kfc_thread *thread = (kfc_thread *)malloc(KFC_PCB_SIZE);
    memset(thread, 0, KFC_PCB_SIZE);
    
    _kfc_thread_init(thread, name, priority,0);
    _kfc_thread_stack_init(thread, func, func_arg);
    if (_kfc_list_find(&_scheduler.ready_list, &thread->ready_tag)) {
        return thread;
    }

    if (_kfc_list_find(&_scheduler.total_list, &thread->total_tag)) {
        return thread;
    }
    
    _kfc_list_append(&_scheduler.ready_list, &thread->ready_tag);
    _kfc_list_append(&_scheduler.total_list, &thread->total_tag);
    
    return thread;
}
