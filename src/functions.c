#include "functions.h"

int isInt(char *number){
  int i, c;

  for(i=0; i<strlen(number); i++){
    c = number[i];
    if(c < 48 || c > 57 || c == 0){
      return 1;
    }
  }
  return 0;
}
