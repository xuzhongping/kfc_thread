//
//  kfc_timer.c
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#include "kfc_timer.h"
#include <unistd.h>
#include <assert.h>
#include "kfc_thread_core.h"
#include "kfc_driver.h"

void _kfc_timer_handle(int signum){
    _KFC_DRIVER_CLOSE;

    kfc_thread *cur_thread = _kfc_running_thread();
    assert(cur_thread->stack_guard == KFC_STACK_MAGIC);
    
    cur_thread->thread_ticks ++;
    if (cur_thread->ticks == 0) {
        _kfc_thread_schedule();
    }else{
        cur_thread->ticks --;
    }
    _KFC_DRIVER_OPEN;
}
