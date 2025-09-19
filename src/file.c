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
  int c;
 while ((c = fgetc(fil)) != EOF) {
    unsigned char byte = (unsigned char)c;

    if (byte <= 0x7F) {
        continue;
    }
    else if ((byte & 0xE0) == 0xC0) {
        int b1 = fgetc(fil);
        if (b1 == EOF || ((unsigned char)b1 & 0xC0) != 0x80)
            return 0; 
    }
    else if ((byte & 0xF0) == 0xE0) {
        int b1 = fgetc(fil), b2 = fgetc(fil);
        if (b2 == EOF) return 0;
        if (((unsigned char)b1 & 0xC0) != 0x80 ||
            ((unsigned char)b2 & 0xC0) != 0x80)
            return 0;
    }
    else if ((byte & 0xF8) == 0xF0) {
        int b1 = fgetc(fil), b2 = fgetc(fil), b3 = fgetc(fil);
        if (b3 == EOF) return 0;
        if (((unsigned char)b1 & 0xC0) != 0x80 ||
            ((unsigned char)b2 & 0xC0) != 0x80 ||
            ((unsigned char)b3 & 0xC0) != 0x80)
            return 0;
    }
    else {
        return 0; 
    }
}


return 1;
}

int handlefiles(int argc, char* argv[]){
    if (argc > 2){
        printf("too many arguments\n");
        return 1; 
    }

    if (argc == 1){
        printf("Usage: file path\n");
        return 1;  
    }

    char* path = argv[1];
    FILE *fil = fopen(path, "rb");

    if (fil == NULL){
        fprintf(stdout, "%s: cannot determine (%s)\n",
                path, strerror(errno));
        return 1;  
    }

    if (handleEmpty(fil)){
        printf("%s: empty\n", path);
        fclose(fil);
        return 0;  
    }
    if (handleASCII(fil)){
        printf("%s: ASCII text\n", path);
        fclose(fil);
        return 0;
    }
      if (handleUTF(fil)){
        printf("%s: Unicode text, UTF-8 text\n", path);
        fclose(fil);
        return 0;
    }
    if (handleISO(fil)){
        printf("%s: ISO-8859 text\n", path);
        fclose(fil);
        return 0;
    }
    else{
    printf("%s: data\n", path);
    fclose(fil);
    return 0;
    }

}

int main(int argc, char* argv[]) {
    return handlefiles(argc, argv);
}
