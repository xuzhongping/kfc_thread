//
//  kfc_list.c
//  kfc_thread
//
//  Created by 徐仲平 on 2019/3/6.
//  Copyright © 2019 徐仲平. All rights reserved.
//

#include "kfc_list.h"
#include <string.h>

void _kfc_list_init(kfc_list *list){
    list->head.prev = NULL;
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
//    strcpy(list->head.name,"head");
//    strcpy(list->tail.name,"tail");
}

void _kfc_list_insert(kfc_list_elem *before,kfc_list_elem *pelem){
    if (pelem == NULL) {
        return;
    }
    before->prev->next = pelem;
    pelem->prev = before->prev;
    pelem->next = before;
    before->prev = pelem;
}

void _kfc_list_append(kfc_list *plist,kfc_list_elem *pelem){
    if (pelem == NULL) {
        return;
    }
    _kfc_list_insert(&plist->tail, pelem);
}
void _kfc_list_push(kfc_list *plist,kfc_list_elem *pelem){
    if (pelem == NULL) {
        return;
    }
    _kfc_list_insert(plist->head.next, pelem);
}

void _kfc_list_remove(kfc_list *plist,kfc_list_elem *pelem){
    if (_kfc_list_find(plist,pelem )) {
        pelem->prev->next = pelem->next;
        pelem->next->prev = pelem->prev;
    }
}
kfc_list_elem * _kfc_list_pop(kfc_list *plist){
    if (_kfc_list_empty(plist)) {
        return NULL;
    }
    kfc_list_elem *elem = plist->head.next;
    _kfc_list_remove(plist, elem);
    return elem;
}
bool _kfc_list_empty(kfc_list *plist){
    return plist->head.next == &plist->tail;
}
uint32_t _kfc_list_len(kfc_list *plist){
    uint32_t len = 0;
    kfc_list_elem *elem = &plist->head;
    while (elem->next != &plist->tail) {
        len ++;
        elem = elem->next;
    }
    return len;
}

bool _kfc_list_find(kfc_list *plist,kfc_list_elem *pelem){
    kfc_list_elem *elem = &plist->head;
    while (elem->next != &plist->tail) {
        if (elem->next == pelem) {
            return true;
        }
        elem = elem->next;
    }
    return false;
}
