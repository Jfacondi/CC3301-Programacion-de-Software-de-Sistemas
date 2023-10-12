#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

#define MAXTAM (800+2)

int main(int argc, char *argv[]) {
  if(argc!=3){
    fprintf(stderr,"Uso: %s <diccionario> <llave>\n", "./consultar.bin");
    return -1;
  }

  FILE *f = fopen(argv[1], "r");
  /*Avisamos si no existe el archivo*/
  if (f == NULL){
  perror(argv[1]);
  return -1;
  }

  /*Lectura inicial del archivo y calculo de tamanho de lineas*/
  char buf[MAXTAM];
  int iniciolinea= ftell(f);
  fgets(buf,MAXTAM,f);
  int finallinea= ftell(f);
  int tamanholinea= finallinea-iniciolinea;
  if(tamanholinea==0){
      fprintf(stderr, "%s: el dicionario esta vacio\n", argv[1]);
      return -1;
  }

  /*calculo de tamanho del archivo para conseguir el numero de lineas*/
  fseek(f,0,SEEK_END);
  int posicionfinal= ftell(f);
  int lineas= 0;
  lineas= posicionfinal/tamanholinea;
  /*trabajo con la palabra entregada(calculo de hash, copia de la palabra y de n)*/
  char palabra[MAXTAM];
  strcpy(palabra,argv[2]);
  int hash= hash_string(argv[2]);
  char buff[MAXTAM];
  int n=hash % lineas;
  if(posicionfinal % tamanholinea != 0){
    fprintf(stderr,"%s: el tamaño del archivo no es multiplo del tamaño de la linea\n", argv[1]);
    return -1;
  }

  /*nos movemos a la linea en donde deberia estar la llave y se lee por primera vez
  para almacenar en el buff*/
  int i=n;
  fseek(f,n*tamanholinea,SEEK_SET);
  fread(buff,tamanholinea,1,f);
  /*ciclo for el cual compara si la palabra con la definicion que se encuentra
  en la linea para luego proceder a printear la definicion y al final del ciclo
  hace un fread para tener preparada la siguiente linea para la continuacion del ciclo for
  */

  while(i!=n-1){
    int y=0;
    char letra[2];
    char *c=buff;
    while(*c !=':'){
      c++;
      y++;
      if(y==strlen(palabra)){
        break;
      }
    }
    *c='\0';
    if(strcmp(buff,"\n")==0){
      fprintf(stderr,"%s: el diccionario no contiene la llave %s\n", argv[1], argv[2]);
      return -1;
    }
    if(strcmp(palabra,buff)==0){
      fseek(f,tamanholinea*i,SEEK_SET);
      fgets(buff,strlen(palabra)+1,f);
      fgets(letra,2,f);
      if (strcmp(letra,":")!=0){
        fprintf(stderr,"%s: linea %d no posee : para terminar la llave\n", argv[1], i);
        return -1;
        }
      else{
        fgets(buff,tamanholinea-strlen(palabra)-1,f);
        printf("%s\n",buff);
        return 0;
      }
    }
    i++;
    if (i==lineas){
    i=0;
    }
    fseek(f,tamanholinea*i,SEEK_SET);
    fgets(buff,MAXTAM,f);
    if (strlen(buff)!=tamanholinea){
      fprintf(stderr,"%s: linea %d de tamaño incorrecto\n", argv[1], i-1);
        return -1;
    }


    if(i==n-1){
      fprintf(stderr,"%s: el diccionario no contiene la llave %s\n", argv[1], argv[2]);
      return -1;
    }
  }
  /*cerramos el archivo*/
 fclose(f);
 return 0;
}
