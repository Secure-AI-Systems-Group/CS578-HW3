#ifndef __IO_H_DEFINED__
#define __IO_H_DEFINED__

/*
 *  a function that loads the matrices
 */
float* load_operand1(char* fname, size_t* ndata, size_t* nfeat);
float* load_operand2(char* fname, size_t* hdim, size_t* wdim);


#endif