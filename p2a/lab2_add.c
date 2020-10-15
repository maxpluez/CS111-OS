#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

long long counter = 0;
long th = 1;
long in = 1;
char syncopt = 'n';
int opt_yield = 0;

pthread_mutex_t mock;
int sock = 0;

void error(char* msg){
  fprintf(stderr, "%s\n", msg);
  if(syncopt=='m'){
    pthread_mutex_destroy(&mock);
  }
  exit(1);
}

void add(long long *pointer, long long value) {
  long long sum = *pointer + value;
  if (opt_yield)
    sched_yield();
  *pointer = sum;
}

void mad(long long *pointer, long long value) {
  pthread_mutex_lock(&mock);
  long long sum = *pointer + value;
  if (opt_yield)
    sched_yield();
  *pointer = sum;
  pthread_mutex_unlock(&mock);
}

void sad(long long *pointer, long long value) {
  while (__sync_lock_test_and_set(&sock, 1));
  long long sum = *pointer + value;
  if (opt_yield)
    sched_yield();
  *pointer = sum;
  __sync_lock_release(&sock);
}

void cad(long long *pointer, long long value) {
  long long old = *pointer;
  if (opt_yield)
    sched_yield();
  while(__sync_val_compare_and_swap(pointer, old, old+value)!=old){
    old = *pointer;
  }
}

void* justdoit(void* arg){
  switch(syncopt){
    case 'n':
      for(int i = 0; i < in; i++){
        add(&counter, 1);
      }
      for(int i = 0; i < in; i++){
        add(&counter, -1);
      }
      break;
    case 'm':
      for(int i = 0; i < in; i++){
        mad(&counter, 1);
      }
      for(int i = 0; i < in; i++){
        mad(&counter, -1);
      }
      break;
    case 's':
      for(int i = 0; i < in; i++){
        sad(&counter, 1);
      }
      for(int i = 0; i < in; i++){
        sad(&counter, -1);
      }
      break;
    case 'c':
      for(int i = 0; i < in; i++){
        cad(&counter, 1);
      }
      for(int i = 0; i < in; i++){
        cad(&counter, -1);
      }
      break;
  }
  arg=arg;
  return NULL;
}

int main(int argc, char** argv){
  static struct option long_options[] = {
		{"threads", optional_argument, NULL, 't'},
		{"iterations", optional_argument, NULL, 'i'},
    {"yield", no_argument, NULL, 'y'},
    {"sync", required_argument, NULL, 's'},
		{0, 0, 0, 0}
  };
  int option;
  while((option=getopt_long(argc, argv, ":t::i::ys:", long_options, NULL))!=-1){
    switch(option){
      case 't':
        th = atoi(optarg);
        break;
      case 'i':
        in = atoi(optarg);
        break;
      case 'y':
        opt_yield=1;
        break;
      case 's':
        syncopt = optarg[0];
        break;
      case '?':
        fprintf(stderr, "Error: Unknow option\n");
        exit(1);
    }
  }

  char tag[15] = {'a', 'd', 'd', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
  if(opt_yield){
    strcat(tag, "-yield");
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
    case 'c':
      strcat(tag, "-c");
      break;
  }

  if(syncopt=='m'){
    if (pthread_mutex_init(&mock, NULL) != 0) { 
        error("\nError: Mutex init has failed"); 
    }
  }

  struct timespec tp;
  if(clock_gettime(CLOCK_REALTIME, &tp)==-1){
    error("Error: clock error");
  }
  long begin_time = tp.tv_sec * 1000000000L + tp.tv_nsec;
  pthread_t* tid = malloc(th*sizeof(pthread_t));
  for(int i = 0; i < th; i++){
    if(pthread_create(&(tid[i]), NULL, &justdoit, NULL)!=0){
      error("Error: thread creation failed");
    }
  }
  for(int i = 0; i < th; i++){
    if(pthread_join(tid[i], NULL)!=0){
      error("Error: thread join failed");
    }
  }
  if(clock_gettime(CLOCK_REALTIME, &tp)==-1){
    error("Error: clock error");
  }
  long end_time = tp.tv_sec * 1000000000L + tp.tv_nsec;

  long numops = th*in*2;
  long duration = end_time-begin_time;
  long avgtime = duration/numops;

  printf("%s,%ld,%ld,%ld,%ld,%ld,%lld\n", tag, th, in, numops, duration, avgtime, counter);

  if(syncopt=='m'){
    pthread_mutex_destroy(&mock);
  }
  free(tid);
  return 0;
}
