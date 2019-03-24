//
//  kfc_driver.h
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//


#ifndef kfc_driver_h
#define kfc_driver_h

#include <pthread.h>
#include <stdio.h>
#include<signal.h>

#include "kfc_thread_macro.h"

_KFC_EXTERN_DRIVER_VAR;
_KFC_EXTERN_DRIVER_OP;
_KFC_EXTERB_DRIVER_LOCK;


void kfc_driver_init(void);


#endif /* kfc_driver_h */
