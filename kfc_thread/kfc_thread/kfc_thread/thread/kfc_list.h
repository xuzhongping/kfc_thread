//
//  kfc_list.h
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#ifndef kfc_list_h
#define kfc_list_h

#include <stdbool.h>
#include <stdio.h>

typedef struct kfc_list_elem{
    char name[16];
    struct kfc_list_elem *prev;
    struct kfc_list_elem *next;
}kfc_list_elem;


typedef struct {
    kfc_list_elem head;
    kfc_list_elem tail;
}kfc_list;


void _kfc_list_init(kfc_list *list);
void _kfc_list_insert(kfc_list_elem *before,kfc_list_elem *pelem);
void _kfc_list_append(kfc_list *plist,kfc_list_elem *pelem);
void _kfc_list_push(kfc_list *plist,kfc_list_elem *pelem);
void _kfc_list_remove(kfc_list *plist,kfc_list_elem *pelem);
kfc_list_elem * _kfc_list_pop(kfc_list *plist);
bool _kfc_list_empty(kfc_list *plist);
uint32_t _kfc_list_len(kfc_list *plist);
bool _kfc_list_find(kfc_list *plist,kfc_list_elem *pelem);


#endif /* kfc_list_h */
