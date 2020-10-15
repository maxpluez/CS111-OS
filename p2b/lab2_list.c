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

SortedList_t** heads = NULL;
SortedListElement_t* elements = NULL;
char** keys = NULL;
long th = 1;
long in = 1;
long num_elements = 1;
char syncopt = 'n';
pthread_t* tid = NULL;
int* thread_nums = NULL;
int num_lists = 1;

long total_lock_acquisition_time = 0;
long total_lock_operations = 0;

pthread_mutex_t** mocks = NULL;
pthread_mutex_t exit_lock;
pthread_mutex_t time_lock;
int** socks = NULL;

void release_exit_lock(){
  pthread_mutex_unlock(&exit_lock);
}

void error(char* msg, int e){
  pthread_mutex_lock(&exit_lock);
  fprintf(stderr, "%s\n", msg);
  if(syncopt=='m'&&mocks){
    for(int i = 0; i < num_lists; i++){
      pthread_mutex_destroy(mocks[i]);
    }
  }
  if(syncopt!='n'){
    pthread_mutex_destroy(&time_lock);
  }
  if(heads){
    for(int i = 0; i < num_lists; i++){
      if(heads[i]){
        free(heads[i]);
      }
    }
    free(heads);
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
  if(syncopt=='m'&&mocks){
    for(int i = 0; i < num_lists; i++){
      free(mocks[i]);
    }
    free(mocks);
  }
  if(syncopt=='s'&&socks){
    for(int i = 0; i < num_lists; i++){
      free(socks[i]);
    }
    free(socks);
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

int hash_it(const char* key){
  return (key[0]%num_lists);
}

int get_length(){
  long result = 0;
  for(int i = 0; i < num_lists; i++){
    result += SortedList_length(heads[i]);
  }
  return result;
}

void* justdoit(void* arg){
  struct timespec tp2;
  long begin_time2 = 0;
  long end_time2 = 0;
  long lock_acquisition_time = 0;
  long lock_operations = 0;
  
  int n = *((int*)arg);
  int start = n*in;
  int end = start+in;
  int whichhead = 0;

  //Step 1: Insert
  for(int i = start; i < end; i++){
    whichhead = hash_it(elements[i].key);
    if(syncopt!='n'){
      if(clock_gettime(CLOCK_MONOTONIC, &tp2)==-1){
        error("Error: clock error", 1);
      }
      begin_time2 = tp2.tv_sec * 1000000000L + tp2.tv_nsec;
    }
    if(syncopt=='m'){
      lock_operations++;
      pthread_mutex_lock(mocks[whichhead]);
    }
    else if(syncopt=='s'){
      lock_operations++;
      while (__sync_lock_test_and_set(socks[whichhead], 1));
    }
    SortedList_insert(heads[whichhead], (&elements[i]));
    if(syncopt=='m'){
      pthread_mutex_unlock(mocks[whichhead]);
    }
    else if(syncopt=='s'){
      __sync_lock_release(socks[whichhead]);
    }
    if(syncopt!='n'){
      if(clock_gettime(CLOCK_MONOTONIC, &tp2)==-1){
        error("Error: clock error", 1);
      }
      end_time2 = tp2.tv_sec * 1000000000L + tp2.tv_nsec;
      lock_acquisition_time += end_time2-begin_time2;
    }
  }

  //Step 2: Length
  long length = 0;
  for(int i = 0; i < num_lists; i++){
    if(syncopt!='n'){
      if(clock_gettime(CLOCK_MONOTONIC, &tp2)==-1){
        error("Error: clock error", 1);
      }
      begin_time2 = tp2.tv_sec * 1000000000L + tp2.tv_nsec;
    }
    if(syncopt=='m'){
      lock_operations++;
      pthread_mutex_lock(mocks[i]);
    }
    else if(syncopt=='s'){
      lock_operations++;
      while (__sync_lock_test_and_set(socks[i], 1));
    }
    length += SortedList_length(heads[i]);
    //fprintf(stderr, "Length: %ld\n", length);
    if(syncopt=='m'){
      pthread_mutex_unlock(mocks[i]);
    }
    else if(syncopt=='s'){
      __sync_lock_release(socks[i]);
    }
    if(syncopt!='n'){
      if(clock_gettime(CLOCK_MONOTONIC, &tp2)==-1){
        error("Error: clock error", 1);
      }
      end_time2 = tp2.tv_sec * 1000000000L + tp2.tv_nsec;
      lock_acquisition_time += end_time2-begin_time2;
    }
  }

  //Step 3: Lookup and Delete
  for(int i = start; i < end; i++){
    whichhead = hash_it(keys[i]);
    if(syncopt!='n'){
      if(clock_gettime(CLOCK_MONOTONIC, &tp2)==-1){
        error("Error: clock error", 1);
      }
      begin_time2 = tp2.tv_sec * 1000000000L + tp2.tv_nsec;
    }
    if(syncopt=='m'){
      lock_operations++;
      pthread_mutex_lock(mocks[whichhead]);
    }
    else if(syncopt=='s'){
      lock_operations++;
      while (__sync_lock_test_and_set(socks[whichhead], 1));
    }
    if(SortedList_delete(SortedList_lookup(heads[whichhead], keys[i]))==1){
      error("Race condition: Corrupted list", 2);
    }
    if(syncopt=='m'){
      pthread_mutex_unlock(mocks[whichhead]);
    }
    else if(syncopt=='s'){
      __sync_lock_release(socks[whichhead]);
    }
    if(syncopt!='n'){
      if(clock_gettime(CLOCK_MONOTONIC, &tp2)==-1){
        error("Error: clock error", 1);
      }
      end_time2 = tp2.tv_sec * 1000000000L + tp2.tv_nsec;
      lock_acquisition_time += end_time2-begin_time2;
    }
  }

  //Step 4: Update Times
  if(syncopt!='n'){
    pthread_mutex_lock(&time_lock);
    total_lock_acquisition_time += lock_acquisition_time;
    total_lock_operations += lock_operations;
    pthread_mutex_unlock(&time_lock);
  }
  
  return NULL;
}

int main(int argc, char** argv){
  signal(SIGSEGV, handler);
  opt_yield = 0;
  static struct option long_options[] = {
		{"threads", optional_argument, NULL, 't'},
		{"iterations", optional_argument, NULL, 'i'},
    {"yield", required_argument, NULL, 'y'},
    {"sync", required_argument, NULL, 's'},
    {"lists", required_argument, NULL, 'l'},
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
      case 'l':
        if(atoi(optarg)<=0)
          error("Error, Invalid argument", 1);
        num_lists = atoi(optarg);
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

  if(syncopt!='n'){
    if (pthread_mutex_init(&time_lock, NULL) != 0) { 
      error("\nError: Mutex init has failed", 1); 
    }
  }

  if(syncopt=='m'){
    mocks = malloc(num_lists*sizeof(pthread_mutex_t*));
    for(int i = 0; i < num_lists; i++){
      mocks[i] = malloc(sizeof(pthread_mutex_t));
      if (pthread_mutex_init(mocks[i], NULL) != 0) {
        error("\nError: Mutex init has failed", 1);
      }
    }
  }

  if(syncopt=='s'){
    socks = malloc(num_lists*sizeof(int*));
    for(int i = 0; i < num_lists; i++){
      socks[i] = malloc(sizeof(int));
      *socks[i] = 0;
    }
  }

  heads = malloc(num_lists*sizeof(SortedList_t*));
  for(int i = 0; i < num_lists; i++){
    heads[i] = malloc(sizeof(SortedList_t));
    heads[i]->next = heads[i];
    heads[i]->prev = heads[i];
    heads[i]->key = NULL;
  }
  
  num_elements = th*in;
  elements = malloc(num_elements*sizeof(SortedListElement_t));
  keys = malloc(num_elements*sizeof(char*));
  for(int i = 0; i < num_elements; i++){
    elements[i].key = keygen(i);
    elements[i].prev = NULL;
    elements[i].next = NULL;
  }

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
  long avg_wait_for_lock = 0;
  if(syncopt!='n'){
    avg_wait_for_lock = total_lock_acquisition_time/total_lock_operations;
  }

  printf("%s,%ld,%ld,%d,%ld,%ld,%ld,%ld\n", tag, th, in, num_lists, numops, duration, avgtime, avg_wait_for_lock);

  if(syncopt=='m'&&mocks){
    for(int i = 0; i < num_lists; i++){
      pthread_mutex_destroy(mocks[i]);
    }
  }

  if(syncopt!='n'){
    pthread_mutex_destroy(&time_lock);
  }
  
  if(heads){
    for(int i = 0; i < num_lists; i++){
      if(heads[i]){
        free(heads[i]);
      }
    }
    free(heads);
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

  if(syncopt=='m'&&mocks){
    for(int i = 0; i < num_lists; i++){
      free(mocks[i]);
    }
    free(mocks);
  }
  if(syncopt=='s'&&socks){
    for(int i = 0; i < num_lists; i++){
      free(socks[i]);
    }
    free(socks);
  }

  return 0;
}
