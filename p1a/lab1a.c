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
#include <sys/wait.h>

#define RET_BUF_SIZE 256

struct termios saved_attr;
int pid;

void reset_term(void){
  if(tcsetattr(0, TCSANOW, &saved_attr)==-1){
    fprintf(stderr, "Error: Reset terminal mode failed\r\n");
    exit(1);
  }
}

void set_term(void){
  struct termios attr;
  if(tcgetattr(0, &saved_attr)==-1){
    fprintf(stderr, "Error: Get terminal mode failed\r\n");
    exit(1);
  }
  atexit(reset_term);

  if(tcgetattr(0, &attr)==-1){
    fprintf(stderr, "Error: Get terminal mode failed\r\n");
    exit(1);
  }
  attr.c_iflag = ISTRIP;
  attr.c_oflag = 0;
  attr.c_lflag = 0;
  if(tcsetattr(0, TCSANOW, &attr)==-1){
    fprintf(stderr, "Error: Set terminal mode failed\r\n");
    exit(1);
  }
}

void exit_sequence(void){
  int status;
  waitpid(pid, &status, 0);
  kill(pid, SIGINT);
  fprintf(stderr, "SHELL EXIT SIGNAL=%d STATUS=%d\r\n", (status&0x007f), ((status&0xff00)>>8));
  reset_term();
  exit(0);
}

void exit_signal_handler(int e){
  fprintf(stderr, "Signal received: %d\r\nExiting...", e);
  exit_sequence();
}
/*
void int_signal_handler(int e){
  fprintf(stderr, "Signal received: %d\r\nExiting...", e);
  kill(pid, SIGKILL);
  exit(1);
}
*/
int main(int argc, char** argv){
  //handle arguments
  if(argc > 2){
    fprintf(stderr, "Error: Too many arguments\nUsage: ./lab1a [--shell]\n");
    exit(1);
  }

  if(argc == 2 && strcmp(argv[1], "--shell")!=0){
    fprintf(stderr, "Error: Unknow option %s\nUsage: ./lab1a [--shell]\n", argv[1]);
    exit(1);
  }
  
  set_term();

  //--shell
  if(argc==2 && strcmp(argv[1], "--shell")==0){
    int fda[2];
    int fdb[2];
    if(pipe(fda)==-1){
      fprintf(stderr, "Error: Pipe creation failed\r\n");
      exit(1);
    }
    if(pipe(fdb)==-1){
      fprintf(stderr, "Error: Pipe creation failed\r\n");
      exit(1);
    }
    if(signal(SIGPIPE, exit_signal_handler)==SIG_ERR){
      fprintf(stderr, "Error: Creating signal handler for SIGPIPE failed\r\n");
      exit(1);
    }    
    if((pid=fork())<0){
      fprintf(stderr, "Error: Fork failed\r\n");
      exit(1);
    }
    if(pid == 0){
      if(close(fda[1])==-1){
	fprintf(stderr, "Error: Closing pipe failed\r\n");
	exit(1);
      }
      if(close(fdb[0])==-1){
	fprintf(stderr, "Error: Closing pipe failed\r\n");
	exit(1);
      }
      if(close(0)==-1){
	fprintf(stderr, "Error: Closing shell's stdin failed\r\n");
	exit(1);
      }
      if(dup(fda[0])==-1){
	fprintf(stderr, "Error: Duplicating pipe to shell's stdin failed\r\n");
	exit(1);
      }
      if(close(fda[0])==-1){
	fprintf(stderr, "Error: Closing pipe failed\r\n");
	exit(1);
      }
      if(close(1)==-1){
	fprintf(stderr, "Error: Closing shell's stdout failed\r\n");
	exit(1);
      }
      if(close(2)==-1){
	fprintf(stderr, "Error: Closing shell's stderr failed\r\n");
	exit(1);
      }
      if(dup(fdb[1])==-1){
	fprintf(stderr, "Error: Duplicating pipe to shell's stdout failed\r\n");
	exit(1);
      }
      if(dup(fdb[1])==-1){
	fprintf(stderr, "Error: Duplicating pipe to shell's stderr failed\r\n");
	exit(1);
      }
      if(close(fdb[1])==-1){
	fprintf(stderr, "Error: Closing pipe failed\r\n");
	exit(1);
      }
      /*
      if(signal(SIGINT, int_signal_handler)==SIG_ERR){
	fprintf(stderr, "Error: Creating signal handler for SIGINT failed\r\n");
	exit(1);
      }
      */
      char* args[] = {"/bin/bash", NULL};
      if(execvp("/bin/bash", args) == -1){
	fprintf(stderr, "Unable to start program /bin/bash\r\n");
	exit(1);
      }
    }
    if(pid > 0){
      if(close(fda[0])==-1){
	fprintf(stderr, "Error: Closing pipe failed\r\n");
	exit(1);
      }
      if(close(fdb[1])==-1){
	fprintf(stderr, "Error: Closing pipe failed\r\n");
	exit(1);
      }
      char c;
      //size_t ret_buf_size = 256;
      //char* ret_buf = malloc(ret_buf_size*sizeof(char));
      char ret_buf[RET_BUF_SIZE];
      //if(!ret_buf){
      //fprintf(stderr, "Error: Malloc failed\n");
      //exit(1);
      //}
      for(size_t i = 0; i < RET_BUF_SIZE; i++){
	ret_buf[i] = 0;
      }
      struct pollfd fds[2];
      //int poll_ret;
      fds[0].fd = 0;
      fds[0].events = POLLIN;
      fds[1].fd = fdb[0];
      fds[1].events = POLLIN | POLLERR | POLLHUP;
      char retchar = '\r';
      char ctrlcchar[5] = {'^', 'C', '\r', '\n', 0};
      char ctrldchar[5] = {'^', 'D', '\r', '\n', 0};
      //ctrlcchar[0] = '^';
      //ctrlcchar[1] = 'C';
      //ctrldchar[0] = '^';
      //ctrldchar[1] = 'D';
      /*
      if(signal(SIGINT, exit_signal_handler)==SIG_ERR){
	fprintf(stderr, "Error: Creating signal handler for SIGINT failed\r\n");
	exit(1);
      }
      */
      while(1){
	/*poll_ret = */poll(fds, 2, 0);
	if(fds[0].revents & POLLIN){
	  if(read(0, &c, 1)<=0){
	    fprintf(stderr, "Error: Read from stdin failed\r\n");
	    exit(1);
	  }
	  if(c == '\003'){
	    if(write(1, ctrlcchar, 4)<=0){
	      fprintf(stderr, "Error: Write to stdout failed\r\n");
	      exit(1);
	    }
	    kill(pid, SIGINT);
	    //exit(1);
	  }
	  if(c == '\004'){
	    if(write(1, ctrldchar, 4)<=0){
	      fprintf(stderr, "Error: Write to stdout failed\r\n");
	      exit(1);
	    }
	    if(close(fda[1])==-1){
	      fprintf(stderr, "Error: Closing pipe on exit failed\r\n");
	      exit(1);	      
	    }
	  }
	  if(c == '\r' || c == '\n'){
	    if(write(1, &retchar, 1)<=0){
	      fprintf(stderr, "Error: Write to stdout failed\r\n");
	      exit(1);	      
	    }
	    c = '\n';
	  }
	  if(write(1, &c, 1)<=0){
	    fprintf(stderr, "Error: Write to stdout failed\r\n");
	    exit(1);
	  }
	  write(fda[1], &c, 1);
	}
	if(fds[1].revents & POLLIN){
	  if(read(fdb[0], ret_buf, RET_BUF_SIZE)<0){
	    fprintf(stderr, "Error: Read from shell failed\r\n");
	    exit(1);	    
	  }
	  for(size_t i = 0; i < RET_BUF_SIZE; i++){
	    if(ret_buf[i]=='\004'){
	      exit_sequence();
	    }
	    if(ret_buf[i]==0){
	      break;
	    }
	    if(ret_buf[i]=='\n'){
	      if(write(1, &retchar, 1)<=0){
		fprintf(stderr, "Error: Write to stdout failed\r\n");
		exit(1);
	      }
	    }
	    if(write(1, (ret_buf+(i*sizeof(char))), 1)<=0){
	      fprintf(stderr, "Error: Write to stdout failed\r\n");
	      exit(1);
	    }
	    ret_buf[i]=0;
	  }
	}
	if(fds[1].revents & (POLLERR|POLLHUP)){
	  exit_sequence();
	}
      }
    }
    return 0;
  }

  //normal case
  char c;
  size_t buf_size = 1;
  char* buf = malloc(buf_size*sizeof(char));
  if(!buf){
    fprintf(stderr, "Error: Malloc failed\r\n");
    exit(1);
  }
  for(size_t i = 0; i < buf_size; i++){
    buf[i]=0;
  }
  size_t size = 0;
  while (1) {
    if(size==buf_size){
      if(write(1, buf, size)<=0){
	fprintf(stderr, "Error: Write to stdout failed\r\n");
	exit(1);	
      }
      for(size_t i = 0; i < size; i++){
	buf[i]=0;
      }
      size = 0;
    }
    if(read(0, &c, 1)<=0){
      fprintf(stderr, "Error: Read from stdin failed\r\n");
      exit(1);
    }
    if (c == '\004'){
      if(write(1, buf, size)<0){
	fprintf(stderr, "Error: Write to stdout failed\r\n");
	exit(1);
      }
      break;
    }
    if(c == '\003'){
      if(write(1, buf, size)<0){
	fprintf(stderr, "Error: Write to stdout failed\r\n");
	exit(1);	
      }
      free(buf);
      exit(1);
    }
    if(c == '\r' || c == '\n'){
      if(size==buf_size-1){
	buf[size++] = '\r';
	if(write(1, buf, size)<0){
	  fprintf(stderr, "Error: Write to stdout failed\r\n");
	  exit(1);
	}
	for(size_t i = 0; i < size; i++){
	  buf[i]=0;
	}
	char lf = '\n';
	if(write(1, &lf, 1)<=0){
	  fprintf(stderr, "Error: Write to stdout failed\r\n");
	  exit(1);
	}
	size=0;
	continue;
      }
      buf[size++] = '\r';
      buf[size++] = '\n';
      continue;
    }
    buf[size++] = c;
  }
  reset_term();
  free(buf);
  return 0;
}
