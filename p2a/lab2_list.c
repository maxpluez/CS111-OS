#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>
#include "SortedList.h"
#include <signal.h>

SortedList_t* head = NULL;
SortedListElement_t* elements = NULL;
char** keys = NULL;
long th = 1;
long in = 1;
long num_elements = 1;
char syncopt = 'n';
pthread_t* tid = NULL;
int* thread_nums = NULL;

pthread_mutex_t mock;
pthread_mutex_t exit_lock;
int sock = 0;

void release_exit_lock(){
  pthread_mutex_unlock(&exit_lock);
}

void error(char* msg, int e){
  pthread_mutex_lock(&exit_lock);
  fprintf(stderr, "%s\n", msg);
  if(syncopt=='m'){
    pthread_mutex_destroy(&mock);
  }
  if(head){
    free(head);
  }
  if(elements){
    free(elements);
  }
  if(keys){
    for(int i = 0; i < num_elements; i++){
      if(keys[i]){
        free(keys[i]);
      }
    }
    free(keys);
  }
  if(tid){
    free(tid);
  }
  if(thread_nums){
    free(thread_nums);
  }
  atexit(&release_exit_lock);
  exit(e);
}

void handler(int e){
  e=e;
  error("Race condition: Segmentation fault", 2);
}

char* keygen(int i){
  char* current = malloc(64*sizeof(char));
  for(int i = 0; i < 64; i++){
    current[i] = rand()%94+33;
  }
  keys[i] = current;
  return current;
}

void* justdoit(void* arg){
  if(syncopt=='m'){
    pthread_mutex_lock(&mock);
  }
  else if(syncopt=='s'){
    while (__sync_lock_test_and_set(&sock, 1));
  }
  int n = *((int*)arg);
  int start = n*in;
  int end = start+in;
  //printf("current thread num: %d; start: %d; end: %d\n", n, start, end);
  for(int i = start; i < end; i++){
    //printf("Thread %d inserting %s\n", current_thread_num, elements[i].key);
    SortedList_insert(head, (&elements[i]));
  }
  SortedList_length(head);
  //printf("%d\n", l);
  for(int i = start; i < end; i++){
    //printf("Thread %d deleting %s\n", current_thread_num, keys[i]);
    if(SortedList_delete(SortedList_lookup(head, keys[i]))==1){
      error("Race condition: Corrupted list", 2);
    }
  }
  if(syncopt=='m'){
    pthread_mutex_unlock(&mock);
  }
  else if(syncopt=='s'){
    __sync_lock_release(&sock);
  }
  return NULL;
}

int main(int argc, char** argv){
  opt_yield = 0;
  static struct option long_options[] = {
		{"threads", optional_argument, NULL, 't'},
		{"iterations", optional_argument, NULL, 'i'},
    {"yield", required_argument, NULL, 'y'},
    {"sync", required_argument, NULL, 's'},
		{0, 0, 0, 0}
  };
  int option;
  while((option=getopt_long(argc, argv, ":t::i::y:s:", long_options, NULL))!=-1){
    switch(option){
      case 't':
        th = atoi(optarg);
        break;
      case 'i':
        in = atoi(optarg);
        break;
      case 'y':
        for(size_t i = 0; i < strlen(optarg); i++){
          if(optarg[i]=='i'){
            opt_yield|=INSERT_YIELD;
          }
          if(optarg[i]=='d'){
            opt_yield|=DELETE_YIELD;
          }
          if(optarg[i]=='l'){
            opt_yield|=LOOKUP_YIELD;
          }
        }
        break;
      case 's':
        syncopt = optarg[0];
        break;
      case '?':
        error("Error: Unknow option", 1);
        break;
      case ':':
        error("Error: Missing argument", 1);
    }
  }

  char tag[15] = {'l', 'i', 's', 't', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
  if(opt_yield == 0){
    strcat(tag, "-none");
  } else {
    strcat(tag, "-");
  }
  if(opt_yield & INSERT_YIELD){
    strcat(tag, "i");
  }
  if(opt_yield & DELETE_YIELD){
    strcat(tag, "d");
  }
  if(opt_yield & LOOKUP_YIELD){
    strcat(tag, "l");
  }
  switch(syncopt){
    case 'n':
      strcat(tag, "-none");
      break;
    case 'm':
      strcat(tag, "-m");
      break;
    case 's':
      strcat(tag, "-s");
      break;
  }

  if (pthread_mutex_init(&exit_lock, NULL) != 0) { 
    error("\nError: Mutex init has failed", 1); 
  }

  if(syncopt=='m'){
    if (pthread_mutex_init(&mock, NULL) != 0) { 
        error("\nError: Mutex init has failed", 1); 
    }
  }

  head = malloc(sizeof(SortedList_t));
  head->next=head;
  head->prev=head;
  head->key=NULL;

  num_elements = th*in;
  elements = malloc(num_elements*sizeof(SortedListElement_t));
  keys = malloc(num_elements*sizeof(char*));
  for(int i = 0; i < num_elements; i++){
    elements[i].key = keygen(i);
    elements[i].prev = NULL;
    elements[i].next = NULL;
  }

  signal(SIGSEGV, handler);

  struct timespec tp;
  if(clock_gettime(CLOCK_MONOTONIC, &tp)==-1){
    error("Error: clock error", 1);
  }
  long begin_time = tp.tv_sec * 1000000000L + tp.tv_nsec;
  tid = malloc(th*sizeof(pthread_t));
  thread_nums = malloc(th*sizeof(int));
  for(int i = 0; i < th; i++){
    thread_nums[i]=i;
    if(pthread_create(&(tid[i]), NULL, &justdoit, &(thread_nums[i]))!=0){
      error("Error: thread creation failed", 1);
    }
  }
  for(int i = 0; i < th; i++){
    if(pthread_join(tid[i], NULL)!=0){
      error("Error: thread join failed", 1);
    }
  }
  if(clock_gettime(CLOCK_MONOTONIC, &tp)==-1){
    error("Error: clock error", 1);
  }
  long end_time = tp.tv_sec * 1000000000L + tp.tv_nsec;

  long numops = th*in*3;
  long duration = end_time-begin_time;
  long avgtime = duration/numops;

  printf("%s,%ld,%ld,1,%ld,%ld,%ld\n", tag, th, in, numops, duration, avgtime);

  if(syncopt=='m'){
    pthread_mutex_destroy(&mock);
  }
  
  if(head){
    free(head);
  }
  if(elements){
    free(elements);
  }
  if(keys){
    for(int i = 0; i < num_elements; i++){
      if(keys[i]){
        free(keys[i]);
      }
    }
    free(keys);
  }
  if(tid){
    free(tid);
  }
  if(thread_nums){
    free(thread_nums);
  }

  return 0;
}
