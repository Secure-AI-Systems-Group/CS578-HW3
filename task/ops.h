#ifndef __OPS_H_DEFINED__
#define __OPS_H_DEFINED__

#include <stdio.h>
#include <stdint.h>

/*
 *  A function that does the matrix multiplication.
 */
void mul2D(
  float** result,
  float* x, size_t xh, size_t xw, \
  float* w, size_t wh, size_t ww);

#endif