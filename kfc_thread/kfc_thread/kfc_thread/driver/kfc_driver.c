//
//  kfc_driver.c
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#include "kfc_driver.h"
#include<unistd.h>

#include "kfc_timer.h"

#include <sys/wait.h>

volatile int _kfc_driver = 0;

pthread_mutex_t _kfc_lock;

// ms x 10
#define _KFC_DRIVER_INTERVAL 1000 * 10

// 阻塞信号为了信号处理函数的不触发
static sigset_t _new_set,_old_set;

void * _kfc_signal_alrm_loop(void *arg){
    while (1) {
        pthread_mutex_lock(&_kfc_lock);
        if (_kfc_driver == 1) {
            _kfc_driver = 0;
            kill(0, SIGALRM);
            usleep(_KFC_DRIVER_INTERVAL);
        }
        pthread_mutex_unlock(&_kfc_lock);
    }
    return 0;
}

void _kfc_sigset_init(){
    sigaddset(&_new_set, SIGALRM);
}

void kfc_driver_init(){
    signal(SIGALRM, _kfc_timer_handle);
    pthread_t signal_thread;
    pthread_create(&signal_thread, NULL, _kfc_signal_alrm_loop, NULL);
    pthread_detach(signal_thread);
    _kfc_sigset_init();
    _KFC_DRIVER_OPEN;
    pthread_mutex_init(&_kfc_lock, NULL);
}

void _kfc_driver_open(void){
    sigprocmask(SIG_UNBLOCK, &_new_set, &_old_set);
}

void _kfc_driver_close(void){
    sigprocmask(SIG_BLOCK, &_new_set, &_old_set);
}
