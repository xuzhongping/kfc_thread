//
//  kfc_thread_macro.h
//  kfc
//
//  Created by 徐仲平 on 2019/3/22.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#ifndef kfc_thread_macro_h
#define kfc_thread_macro_h


#pragma mark - kfc_driver_h

#define _KFC_EXTERB_DRIVER_LOCK \
extern pthread_mutex_t _kfc_lock

#define _KFC_EXTERN_DRIVER_VAR \
extern volatile int _kfc_driver

#define _KFC_EXTERN_DRIVER_OP \
void _kfc_driver_open(void); \
void _kfc_driver_close(void)


#define _KFC_DRIVER_OPEN \
pthread_mutex_lock(&_kfc_lock); \
_kfc_driver = 1; \
_kfc_driver_open(); \
pthread_mutex_unlock(&_kfc_lock)


#define _KFC_DRIVER_CLOSE \
pthread_mutex_lock(&_kfc_lock); \
_kfc_driver = 0; \
_kfc_driver_close(); \
pthread_mutex_unlock(&_kfc_lock)



#pragma mark - kfc_thread_core_h

#define _KFC_EXPORT_THREAD_UNUSABLE_FUNC \
void _kfc_thread_schedule(void);    \
kfc_thread * _kfc_running_thread(void); \
kfc_thread * _kfc_main_thread(void)


#define offset(struct_type,member)  \
(uint64_t)(&((struct_type *)0)->member)

#define elem2entry(struct_type,struct_member_name,elem_ptr) \
(struct_type *)((uint64_t)elem_ptr - offset(struct_type,struct_member_name));


#define KFC_ALIGN_RSP_16    \
asm volatile("andq $0xFFFFFFFFFFFFFFF0,%rsp")



#endif /* kfc_thread_macro_h */
