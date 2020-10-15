#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void sigsegv_handler(int e){
  fprintf(stderr, "Error: Segmentation fault by option --segfault registered by --catch\n");
  fprintf(stderr, "Error Signal: %s \n", strerror(e));
  exit(4);
}

int main(int argc, char**argv){
  //flags
  int in = 0;
  int out = 0;
  int seg = 0;
  int cat = 0;
  char* input_file = NULL;
  char* output_file = NULL;
  int len;
  static struct option long_options[] = {
					 {"input", required_argument, NULL, 'i'},
					 {"output", required_argument, NULL, 'o'},
					 {"segfault", no_argument, NULL, 's'},
					 {"catch", no_argument, NULL, 'c'},
					 {0, 0, 0, 0}
  };
  int option;
  while((option=getopt_long(argc, argv, ":i:o:sc", long_options, NULL))!=-1){
    switch(option){
    case 'i':
      in = 1;
      len = strlen(optarg);
      input_file=malloc((len+1)*sizeof(char));
      strcpy(input_file, optarg);
      break;
    case 'o':
      out = 1;
      len = strlen(optarg);
      output_file=malloc((len+1)*sizeof(char));
      strcpy(output_file, optarg);
      break;
    case 's':
      seg=1;
      break;
    case 'c':
      cat=1;
      break;
    case '?':
      fprintf(stderr, "Error: Unknown argument\n");
      fprintf(stderr, "Usage: ./lab0 --input <input_file_path> --output <output_file_path> --segfault --catch\n");
      if(input_file){
	free(input_file);
      }
      if(output_file){
	free(output_file);
      }
      exit(1);
      break;
    case ':':
      fprintf(stderr, "Error: An argument must be provided for --input or --output\n");
      fprintf(stderr, "Usage: ./lab0 --input <input_file_path> --output <output_file_path> --segfault --catch\n");
      if(input_file){
	free(input_file);
      }
      if(output_file){
	free(output_file);
      }            
      exit(1);
    }
  }
  if(in == 1){
    int ifd = open(input_file, O_RDONLY);
    if(ifd<0){
      fprintf(stderr, "Error: Cannot open file %s on option --input\n", input_file);
      fprintf(stderr, "%s\n", strerror(errno));
      if(input_file){
	free(input_file);
      }
      if(output_file){
	free(output_file);
      }            
      exit(2);
    }
    close(0);
    dup(ifd);
    close(ifd);
  }
  if(out == 1){
    int ifd = creat(output_file, 0666);
    if(ifd<0){
      fprintf(stderr, "Error: Cannot create file %s on option --output\n", output_file);
      fprintf(stderr, "%s\n", strerror(errno));
      if(input_file){
	free(input_file);
      }
      if(output_file){
	free(output_file);
      }            
      exit(3);
    }
    close(1);
    dup(ifd);
    close(ifd);
  }
  if(cat==1){
    signal(SIGSEGV, sigsegv_handler);
  }
  if(seg==1){
    char* gotcha = NULL;
    *gotcha = 'g';
  }
  char* str = malloc(1);
  int* c = malloc(1);
  int index = 0;
  int stat;
  while(1){
    stat = read(0, c, 1);
    if(stat<=0)
      break;
    //write(1, c, 1);
    str=realloc(str, index+1);
    if(!str)
      exit(1);
    str[index]=*c;
    index++;
  }
  write(1, str, index);
  free(str);
  free(c);
  if(input_file){
    free(input_file);
  }
  if(output_file){
    free(output_file);
  }        
  return 0;
}
