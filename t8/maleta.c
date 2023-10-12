// Plantilla para maleta.c

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "maleta.h"

// Use la funcion leer para obtener los resultados del pipe
int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double llenarMaleta(double w[], double v[], int z[], int n,
                    double maxW, int k) {

  int pids[8];
  int fds[8][2];
  for(int i=0;i<8;i++){
    pipe(fds[i]);

  }
  for(int i=0;i<8;i++){
    pids[i] = fork();
    srandom(getUSecsOfDay()*getpid());


    if(pids[i]==0){
      close(fds[i][0]);
      double res = llenarMaletaSec(w,v,z,n,maxW,k/8);
      write(fds[i][1],&res,sizeof(double));
      write(fds[i][1],z,n*sizeof(int));
      exit(0);
    }
    else{
      close(fds[i][1]);
    }
  }
  double res= 0;
  for(int i=0;i<8;i++){
    double res_child;
    leer(fds[i][0],&res_child,sizeof(double));
    leer(fds[i][0],z,n*sizeof(int));
    close(fds[i][0]);
    waitpid(pids[i], NULL,0);
    if(res_child!=0){
      res=res_child;
    }
  }
  return res; // Modifique
}
