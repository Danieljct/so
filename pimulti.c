//gcc -fopenmp -lm  main.c -o main
/*ejemplo multithread con omp*/
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float total, total1 = 0, puntosdentro;

int main(int argc, char *argv[]) {

total = atoi(argv[1]);
  
#pragma omp parallel
  {
    srand(time(NULL));
    for (int i = 0; i < total; i++) {
      double numero1 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
      double numero2 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
      if (pow(pow(numero1, 2) + pow(numero2, 2), .5) <= 1)
        puntosdentro++;
      total1++;
    }
  }

  double pi = 4 * puntosdentro / total1;
  printf("PI: %f\n", pi);

  return 0;
}

