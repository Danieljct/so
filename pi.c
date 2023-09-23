/*ej thread simple*/
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

float puntosdentro, total;

void *maximo(void *param); /* the thread */

int main(int argc, char *argv[]) {

  total = atoi(argv[1]);
  /*Configuracion promedio*/
  pthread_t tid0;
  pthread_attr_t attr0;
  pthread_attr_init(&attr0);
  pthread_create(&tid0, &attr0, maximo, NULL);
  pthread_join(tid0, NULL);
  double pi;
  pi = 4 * puntosdentro / total;
  printf("PI: %f\n", pi);
}

void *maximo(void *param) {
  srand(time(NULL));
  for (int i = 0; i < total; i++) {
    double numero1 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    double numero2 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;   
    if (pow(pow(numero1, 2) + pow(numero2, 2), .5) <= 1)
      puntosdentro++;
  }
}

