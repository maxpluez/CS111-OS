#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <signal.h>

struct termios saved_attr;

void reset_term(void){
  tcsetattr(0, TCSANOW, &saved_attr);
}

void set_term(void){
  struct termios attr;
  tcgetattr(0, &saved_attr);
  atexit(reset_term);

  tcgetattr(0, &attr);
  attr.c_iflag = ISTRIP;
  attr.c_oflag = 0;
  attr.c_lflag = 0;
  tcsetattr(0, TCSANOW, &attr);
}

int main(int argc, char** argv){
  set_term();

  //--shell
    int fda[2];
    int fdb[2];
    int pid;
    pipe(fda);
    pipe(fdb);
    if((pid=fork())<0){
      exit(1);
    }
    if(pid == 0){
      close(fda[1]);
      close(fdb[0]);
      close(0);
      dup(fda[0]);
      close(1);
      close(2);
      dup(fdb[1]);
      dup(fdb[1]);      
      char c;
      struct pollfd fdp;
      fdp.fd = 0;
      fdp.events = POLLIN;
      while(1){
	if(read(fda[0], &c, 1)>0){
	  printf("Child received\n");
	  write(fdb[1], &c, 1);
	}
      }
    }
    if(pid > 0){
      close(fda[0]);
      close(fdb[1]);
      char c;
      size_t ret_buf_size = 256;
      char* ret_buf = malloc(ret_buf_size*sizeof(char));
      for(int i = 0; i < ret_buf_size; i++){
	ret_buf[i]=0;
      }
      struct pollfd fds[2];
      int poll_ret;
      fds[0].fd = 0;
      fds[0].events = POLLIN;
      fds[1].fd = fdb[0];
      fds[1].events = POLLIN;
      while(1){
	poll_ret = poll(fds, 2, 0);
	if(fds[0].revents & POLLIN){
	  //printf("Got from keyboard\n");
	  read(0, &c, 1);
	  if(c == '\003'){
	    kill(pid, SIGINT);
	    return 0;
	  }
	  write(1, &c, 1);
	  if(write(fda[1], &c, 1)>0){
	    //printf("Parent sent\n");
	  }
	  
	}
	if(fds[1].revents & POLLIN){
	  //printf("Got from shell\n");
	  read(fdb[0], ret_buf, ret_buf_size);
	  write(1, ret_buf, ret_buf_size);
	  for(int i = 0; i < ret_buf_size; i++){
	    ret_buf[i]=0;
	  }	  
	}
      }
    }
    return 0;
}
