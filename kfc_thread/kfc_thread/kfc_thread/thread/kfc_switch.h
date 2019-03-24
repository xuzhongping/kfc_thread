//
//  kfc_switch.h
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/10.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#ifndef kfc_switch_h
#define kfc_switch_h

#include <stdio.h>
#include "kfc_thread_core.h"

void _kfc_switch(kfc_thread *cur,kfc_thread *next);
void _kfc_first_switch(kfc_thread *cur,kfc_thread *next);

void _kfc_died_switch(kfc_thread *next);
void _kfc_died_first_switch(kfc_thread *next);

#endif /* kfc_switch_h */
