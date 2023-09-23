/*pi con multi threads y mutex*/
//gcc -fopenmp pimultimutex.c -o pimultimutex -lm
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float total;
int puntosdentro = 0;
int total1 = 0;
omp_lock_t lock;

int main(int argc, char *argv[]) {
  total = atoi(argv[1]);
  omp_init_lock(&lock);

#pragma omp parallel
  {
    srand(time(NULL));
    int local_puntosdentro = 0;
    int local_total1 = 0;
    l
    for (int i = 0; i < total; i++) {
      double numero1 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
      double numero2 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
      if (pow(pow(numero1, 2) + pow(numero2, 2), .5) <= 1)
        local_puntosdentro++;
      local_total1++;
    }

    // Bloquear el mutex antes de actualizar las variables compartidas
    omp_set_lock(&lock);
    puntosdentro += local_puntosdentro;
    total1 += local_total1;
    // Desbloquear el mutex después de actualizar las variables compartidas
    omp_unset_lock(&lock);
  }

  double pi = 4 * (double)puntosdentro / total1;
  printf("PI: %f\n", pi);

  return 0;
}

