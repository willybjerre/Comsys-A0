#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.

int print_hello_world(void) {
  return fprintf(stdout, "Hello, world!\n");
}

int handleEmpty(FILE *fil){
  fseek(fil, 0, SEEK_END);
  int position_in_file = ftell(fil);
  fclose(fil);

  return position_in_file == 0;
  
}
  

int handleASCII(FILE *fil){

}

int handleISO(FILE *fil){

}

int handleUTF(FILE *fil){

}

int handleData(FILE *fil){

}



int main(int argc, char* argv[]) {

  if (argc > 1){
    printf("too many arguments");
    return 1;
  }
  char* path = argv[1];
  FILE *fil = fopen(path, 'rb');
  if (handleEmpty(fil)){
    return 0;
  }
  if (handleASCII(fil)){
    return 0;
  }
  if (handleISO(fil)){
    return 0;
  }
  if (handleUTF(fil)){
    return 0;
  }
  if (handleData(fil)){
    return 0;
  }

  int retval = EXIT_SUCCESS;

  if (print_hello_world() <= 0) {
    retval = EXIT_FAILURE;
  }

  return retval;
}
