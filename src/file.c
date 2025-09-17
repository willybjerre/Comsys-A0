#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.




int handleEmpty(FILE *fil){
  fseek(fil, 0, SEEK_END);
  int position_in_file = ftell(fil);
  fseek(fil, 0, SEEK_SET);
  return position_in_file == 0;
}
  

int handleASCII(FILE *fil){

  int check_if_Ascii = 1;

  fseek(fil, 0, SEEK_SET);
  int c = fgetc(fil);
  while (c != EOF)
  {
    if (c > 127) {
      check_if_Ascii = 0;
      return check_if_Ascii;
    }
    c = fgetc(fil);
  }
  return check_if_Ascii;
}

int handleISO(FILE *fil){
  int check_if_Ascii = 0;

  fseek(fil, 0, SEEK_SET);
  int c = fgetc(fil);
  while (c != EOF)
  {
    if (c > 127) {
      return 1;
    }
    c = fgetc(fil);
  }
  return check_if_Ascii;
}

int handleUTF(FILE *fil){
  fseek(fil, 0, SEEK_SET);
  int c = fgetc(fil);
  while (c != EOF)
  {
    unsigned char byte = (unsigned char)c;
    if (byte <= 0x7F){
      continue;
    }
    else if ((byte & 0xC0) == 0xC0){
      int byte1 = fgetc(fil);
      if ((byte1 & 0xC0) == 0x80){
        return 1;
      }
    }
    else if ((byte & 0xE0) == 0xE0){
      int byte1 = fgetc(fil);
      int byte2 = fgetc(fil);
      if ((byte1 & 0xC0) == 0x80 && (byte2 & 0xC0) == 0x80){
        return 1;
      }
    }
    else if ((byte & 0xF0) == 0xF0){
      int byte1 = fgetc(fil);
      int byte2 = fgetc(fil);
      int byte3 = fgetc(fil);
      if ((byte1 & 0xC0) == 0x80 && (byte2 & 0xC0) == 0x80 && (byte3 & 0xC0) == 0x80){
        return 1;
      }
    }  
    
    }
    return 0;
}


int main(int argc, char* argv[]) {
  if (argc > 2){
    printf("too many arguments");
    return 0;
  }

  if (argc == 1){
    printf("Usage: file path");
    return 0;
  }

  char* path = argv[1];
  FILE *fil = fopen(path, "rb");

  if (fil == NULL){
    fprintf(stdout, "%s: cannot determine (%s)\n",
    path, strerror(errno));
    return 0;
  }

  if (handleEmpty(fil)){
    printf("empty\n");
    fclose(fil);
    return 1;
  }
  if (handleASCII(fil)){
    printf("ASCII text\n");
    fclose(fil);
    return 1;
  }
  if (handleUTF(fil)){
    fclose(fil);
    printf("UTF-8 Unicode text\n");
    return 1;
  }
  if (handleISO(fil)){
    fclose(fil);
    printf("ISO-8859 text\n");
    return 1;
  }
  else{
    fclose(fil);
    printf("data file\n");
    return 1;
  }
  fclose(fil);
  return 0;
}
