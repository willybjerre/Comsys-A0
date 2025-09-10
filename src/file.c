#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.

int print_hello_world(void) {
  return fprintf(stdout, "Hello, world!\n");
}

int handleEmpty(FILE *fil){

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

  FILE *fil = argv[1];
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
  if (argc > 1){
    printf("too many arguments");
    return 1;
  }
  int retval = EXIT_SUCCESS;

  if (print_hello_world() <= 0) {
    retval = EXIT_FAILURE;
  }

  return retval;
}
