//
//  main.c
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/24.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#include <stdio.h>
#include "kfc_thread.h"

void threadA_func(void *arg){
    char *name = arg;
    while (1) {
        printf("%s\n",name);
    }
}

void threadB_func(void *arg){
    char *name = arg;
    while (1) {
        printf("%s\n",name);
    }
}

int main(int argc, const char * argv[]) {
    
    kfc_thread_init();
    
    kfc_thread_start("threadA", 5, threadA_func, "A thread");
    kfc_thread_start("threadB", 5, threadB_func, "B thread");
    kfc_driver_init();
    while (1){
        printf("main thread\n");
    }

    while (1);
    return 0;
}
