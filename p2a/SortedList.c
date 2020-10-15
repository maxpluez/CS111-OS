#include "SortedList.h"
#include <string.h>
#include <sched.h>
#include <stdio.h>

int opt_yield = 0;

void SortedList_insert(SortedList_t *list, SortedListElement_t *element){
    if(element==NULL || list==NULL || list->key!=NULL){
        return;
    }
    //SortedList_t *head = list;
    while(list->next->key!=NULL && strcmp(list->next->key, element->key)<=0){
        //printf("inside while loop: %s\n", list->next->key);
        //if(strcmp(list->next->key, element->key)==0){
        //    printf("Same key\n");
            //exit(3);
        //}
        //printlist(head);
        if(opt_yield & INSERT_YIELD){
            sched_yield();
        }
        list = list->next;
    }
    if(opt_yield & INSERT_YIELD){
        sched_yield();
    }
    element->next = list->next;
    element->prev = list;
    list->next->prev = element;
    list->next = element;
}

int SortedList_delete( SortedListElement_t *element){
    if(element==NULL || element->key==NULL){
        return 1;
    }
    if(opt_yield & DELETE_YIELD){
        sched_yield();
    }
    if(element->prev==NULL || element->prev->next==NULL || strcmp(element->prev->next->key, element->key)!=0){
        return 1;
    }
    if(element->next==NULL || element->next->prev==NULL || strcmp(element->next->prev->key, element->key)!=0){
        return 1;
    }

    if(opt_yield & DELETE_YIELD){
        sched_yield();
    }

    element->next->prev = element->prev;
    element->prev->next = element->next;
    element->prev = NULL;
    element->next = NULL;

    return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key){
    if(key==NULL || list==NULL || list->key!=NULL){
        return NULL;
    }
    list = list->next;
    while(list->key!=NULL && strcmp(list->key, key)!=0){
        if(opt_yield & LOOKUP_YIELD){
            sched_yield();
        }
        list = list->next;
    }
    return list;
}

int SortedList_length(SortedList_t *list){
    int result = 0;
    while(list->next->key!=NULL){
        result++;
        if(opt_yield & LOOKUP_YIELD){
            sched_yield();
        }
        list = list->next;
    }
    return result;
}