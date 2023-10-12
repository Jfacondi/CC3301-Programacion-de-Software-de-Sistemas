#include <stdlib.h>
#include <string.h>

#include "comprimir.h"
typedef unsigned int uint;

uint comprimir(uint *a, int nbits) {
  uint comprimido= 0;
  int mask = ~((0xffffffff<< (nbits-1))<<1);
  for(int i=nbits;i<= sizeof(uint)<<3;i+=nbits){
    comprimido= comprimido << (nbits-1) <<1;
    uint elemento = *a & mask;
    comprimido |= elemento;
    a++;
  }
  return comprimido;
}
