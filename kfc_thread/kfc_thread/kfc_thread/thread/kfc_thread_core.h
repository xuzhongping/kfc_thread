//
//  kfc_thread_core.h
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#ifndef kfc_thread_core_h
#define kfc_thread_core_h

#include <stdio.h>
#include "kfc_list.h"
#include "kfc_thread_macro.h"


#define KFC_STACK_MAGIC 0x12345678
#define KFC_STACK_FIRST 0x87654321


typedef enum{
    KFC_THREAD_RUNNING = 0,
    KFC_THREAD_READY,
    KFC_THREAD_BLOCKED,
    KFC_THREAD_DIED
}kfc_thread_status;

typedef void kfc_thread_func(void *);


// 线程栈
typedef struct {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    void (*rip)(kfc_thread_func *func,void *func_arg);
    
    // 以下参数只在线程的第一次启动时使用
    void (*unused_ret_addr);// 此处可省略，因为x86-64的函数调用约定6个参数以内用寄存器传递
    kfc_thread_func *func;
    void *func_arg;
    void (*died)(void); // died handle func
}kfc_thread_stack;

// pcb
typedef struct {
    uint64_t *stack_point;
    uint first_call;
    kfc_thread_status status;
    uint priority;
    char name[16];
    uint ticks;
    uint32_t thread_ticks;
    kfc_list_elem ready_tag;
    kfc_list_elem total_tag;
    uint32_t stack_guard;
}kfc_thread;

// scheduler
typedef struct {
    uint32_t total_ticks;
    kfc_thread *main_thread;
    kfc_thread *runnning_thread;
    kfc_list ready_list;
    kfc_list total_list;
}kfc_scheduler;

_KFC_EXPORT_THREAD_UNUSABLE_FUNC;


#pragma mark - public function
/**
 初始化线程库
 */
void kfc_thread_init(void);

/**
 启动一个线程

 @param name 线程名称
 @param priority 优先级
 @param func 调用函数
 @param func_arg 函数参数
 @return 线程结构
 */
kfc_thread * kfc_thread_start(char *name,uint priority,kfc_thread_func *func,void *func_arg);

#endif /* kfc_thread_h */
