#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
 *  A function that loads the data in a csv format
 */
float* load_operand1(char* fname, size_t* ndata, size_t* nfeat) {
  FILE* fp;

  // open the file
  if ((fp = fopen(fname, "r")) == NULL) {
    printf("Error: %s\n", strerror(errno));
    exit(1);
  }

  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  size_t feat_nrow = 0;
  size_t feat_ncol = 0;
  bool nrow_stop = false;

  while ((read = getline(&line, &len, fp)) != -1) {
    size_t widx = 0;
    char *token = NULL;

    // find out the number of samples by waiting until the "-----" division in the csv file
    if (line[0] == '-' && line[1] == ',' && line[2] == '-') {
      *ndata = *ndata + 1;
      nrow_stop = true;         // stop recording feature dimensions, we already know
    }

    // find out the number of features (in a row)
    if (feat_ncol == 0) {
      for (token = strtok(line, ",");
           token && *token;
           token = strtok(NULL, ",")) {
        feat_ncol = feat_ncol + 1;
      }
    }

    // find out the number of rows
    if (!nrow_stop) {
      feat_nrow += 1;
    }
  }

  // read the 2d data, the number of features in each row * the number of rows until we face "-----"
  *nfeat = feat_nrow * feat_ncol; 

  // close the opened file
  fclose(fp);

  // re-open the file
  if ((fp = fopen(fname, "r")) == NULL) {
    printf("Error: [load_mnist_simdata] cannot re-open the file %s\n", fname);
    exit(1);
  }

  // allocate memory w.r.t the 2D-matrix size (samples * features)
  size_t size = (*ndata) * (*nfeat);
  float* simdata = (float *) malloc(size * sizeof(float));
  if (simdata == NULL) {
    printf("Error: [load_mnist_simdata] cannot allocate the mem. (size: %d)\n", (int)size);
    exit(1);
  }

  // initialize the allocated memory address
  for (size_t i = 0; i < size; i++) {
    simdata[i] = 0.;
  }

  // load the data values from a csv file
  size_t sidx = 0;
  size_t fidx = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    char *token = NULL;

    // increase the sample index (sidx)
    if (line[0] == '-' && line[1] == ',' && line[2] == '-') {
      sidx++;
      fidx = 0;     // set feature index to zero
    }

    // otherwise parse and store the data
    else {
      for (token = strtok(line, ",");
           token && *token;
           token = strtok(NULL, ",")) {

        size_t didx = sidx*(*nfeat) + fidx;
        simdata[didx] = atof(token);
        fidx++;
      }
    }

  }

  // close the opened file
  fclose(fp);

  return simdata;
}

float* load_operand2(char* fname, size_t* hdim, size_t* wdim){
  FILE* fp;

  // open the file
  if ((fp = fopen(fname, "r")) == NULL) {
    printf("Error: [load_network_parameter] cannot open the file %s\n", fname);
    exit(1);
  }

  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  // read the file line by line
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t widx = 0;
    char *token = NULL;

    // find out the number of features
    if (*wdim == 0) {
      for (token = strtok(line, ",");
           token && *token;
           token = strtok(NULL, ",")) {
        *wdim = *wdim + 1;
      }
    }

    // find out the number of samples
    *hdim = *hdim + 1;
  }

  // close the opened file
  fclose(fp);

  // re-open the file
  if ((fp = fopen(fname, "r")) == NULL) {
    printf("Error: [load_network_parameter] cannot re-open the file %s\n", fname);
    exit(1);
  }

  // allocate memory w.r.t the 2D-matrix size (samples * features)
  size_t size = (*hdim) * (*wdim);
  float* netparam = (float *) malloc(size * sizeof(float));
  if (netparam == NULL) {
    printf("Error: [load_network_parameter] cannot allocate the mem. (size: %d)\n", (int)size);
    exit(1);
  }

  // initialize the allocated memory address
  for (size_t i = 0; i < size; i++) {
    netparam[i] = 0.;
  }

  // load the data values from a csv file
  size_t hidx = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t widx = 0;
    char *token = NULL;

    for (token = strtok(line, ",");
         token && *token;
         token = strtok(NULL, ",")) {

        size_t didx = hidx*(*wdim) + widx;
        netparam[didx] = atof(token);
        widx++;
    }

    hidx++;
  }

  // close the opened file
  fclose(fp);

  return netparam;
}