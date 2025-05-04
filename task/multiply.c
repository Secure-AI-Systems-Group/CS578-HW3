#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include <sys/stat.h>

#include <util.h>

#include "io.h"
#include "ops.h"

/*
 *  Static: the datafile location
 */
static char* operand1 = "operand1.csv";
static char* operand2 = "operand2.csv";


/*
 *  Main: load the data from the csvfile
 */
int main(int argc, char *argv[])
{
  /*
   *  load the simulation data
   */
  size_t num_data = 0;
  size_t num_feat = 0;
  float* op1 = load_operand1(operand1, &num_data, &num_feat);

  // sanity check
  if (op1 == NULL) {
    printf("[multiply] Error: cannot load the first operand\n");
    free(op1);
    return -1;
  }
  printf("[multiply] successfully load the first operand.\n");


  /*
   *  load the network parameter
   */
  size_t h_dim = 0;
  size_t w_dim = 0;
  float* op2 = load_operand2(operand2, &h_dim, &w_dim);

  // sanity check
  if (op2 == NULL) {
    printf("[multiply] Error: cannot load the second operand\n");
    free(op1);
    free(op2);
    return -1;
  }
  printf("[multiply] successfully load the second operand.\n");


  /*
   *  compute the matrix multiplication
   *  & measures the time for each multiplication of elements
   */
  size_t totsize = num_data * h_dim * w_dim;
  float* asample = NULL;

  for (size_t sidx = 0; sidx < num_data; sidx++) {

    // allocate the memory if not exists
    if (asample == NULL) {
      asample = (float *) malloc(num_feat * sizeof(float));
    }

    // copy the sample data to the memory
    for (size_t fidx = 0; fidx < num_feat; fidx++) {
      size_t didx = sidx * num_feat + fidx;
      asample[fidx] = op1[didx];
    }

    // compute the multiplication
    float* result = NULL;
    mul2D(&result, asample, 1, num_feat, op2, h_dim, w_dim);

    // sanity check
    if (op2 == NULL) {
      printf("[multiply] Error: mul2D does not work, abort\n");
      free(asample);
      free(op1);
      free(op2);    
      free(result);
      return -1;
    }
    printf("[multiply] successfully ran the matrix multiplication.\n");

    // free the allocated memory
    free(result);

    // make a delay
    delayloop(10000);
  }

  /*
   *  free the allocated memory
   */
  free(asample);
  free(op1);
  free(op2);
  return 0;
}
