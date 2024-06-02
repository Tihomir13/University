#include <stdio.h>
#include <shared.h>

int main() {

  char *buffer;
  buffer = (char *)getmem(1322);

 for(int i = 'a'; i <= 'z'; i++) {
   printf("letter: %c \n", *buffer);
   for(int k = 0; k < 10000000; k++);
 }
}