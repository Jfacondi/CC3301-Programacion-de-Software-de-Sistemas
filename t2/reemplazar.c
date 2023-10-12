#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

char *reemplazo(char *s, char c, char *pal) {
  int cnt=0;
  char *x =s;
  int z=strlen(pal);
  while (*x != 0) {
    if(*x == c){
      cnt= cnt+z;
      }
    else{
      cnt++;
      }
    x++;
  }
  char *resultado= (char *)malloc(cnt+1);
  char *y = resultado;
  x=s;
  while (*x != 0){
    if(*x == c){
      strcpy(y,pal);
      y=y+z;
      }
    else{
      (*y)=(*x);
      y++;
      }
    x++;
  }
  (*y)=0;
  return resultado;
}

void reemplazar(char *s, char c, char *pal) {
  int cnt=0;
  char *x=s;
  int z=strlen(pal);
  while (*x != 0){
    if(*x==c){
      cnt=cnt+z;
      }
    else{
      cnt++;
      }
    x++;
  }
  if (z == 0) {
    x = s;
    while (*x != 0) {
      if (*x == c) {
        char* temp = x;
        char* temp2=x+1;
        while (*temp != 0) {
          (*temp) = (*temp2);
          temp++;
          temp2++;
        }
      }
      else {
      x++;
      }
    }
  }

  else if (z==1){
    x=s;
    while (*x !=0){
      if(*x==c){
        (*x)=(*pal);
      }
      x++;
    }
  }
  else{
    char* pald=pal+z-1;
    char* v=s+cnt;
    while(x>=s){
      if(*x==c){
        pald=pal+z-1;
        while(pald>=pal){
          (*v)=(*pald);
          pald--;
          v--;
        }
      }
      else{
        (*v)=(*x);
        v--;
      }
      x--;
    }
  }
}
