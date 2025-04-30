#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *  A function that does the matrix multiplication.
 *   - X: 1   x 784 (input)
 *   - W: 128 x 784 (weights)
 *   - O: 1   x 128 (output)
 */
void mul2D(
  float** result,
  float* x, size_t xh, size_t xw, \
  float* w, size_t yh, size_t yw)
{

  /*
   * Error cases: in multiplication of X * W...
   */
  if (xw != yw) {
    printf("[mul2D] Error: dimensions should match " \
           "[x-width: %zd != y-width: %zd]\n", xw, yw);
    exit(1);
  }

  /*
   *  Dimensions of resulting matrices
   *  (Note: W [weight matrix] is already transposed, so consider different edge-lengths)
   */
  size_t res_size  = xh * yh;

  /*
   *  Memory allocations for the results
   */
  float* mresult = (float *) malloc(res_size * sizeof(float));
  if (mresult == NULL) {
    printf("[mul2D] Error: cannot allocate memory for the result\n");
    exit(1);
  }

  /*
   *  Do the multiplication:
   *  Note that this code block comes from the ATen GEMM in PyTorch
   */
  size_t i, j, k;

  float *w_ = w;
  for (i = 0; i < xh; i++)
  {
    float *x_ = x;
    for (j = 0; j < yh; j++)
    {

      /*
       *  Multiplication for a single element
       *   in the resulting matrix (i-x-j = ij)
       */
      float sum = 0.;
      for (k = 0; k < yw /* same as xw */; k++) {

        // multiplications
        sum += x_[k] * w_[k];

      }

      /*
       *  store the multiplication result,
       *   and increase the pointer by 'yw'
       */
      mresult[i*yh + j] = sum;
      w_ += yw;

    }
    x_ += xw;

  }

  /*
   *  Store and pass the pointers to the caller
   */
  *result = mresult;
}
