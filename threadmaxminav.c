#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int media, max, min;
void *promedio(void *param); /* the thread */
void *minimo(void *param);   /* the thread */
void *maximo(void *param);   /* the thread */

int main(int argc, char *argv[]) {

  int arreglo[argc - 1];
  for (int i = 0; i < argc - 1; i++) {
    arreglo[i] = atoi(argv[i + 1]);
  }
  /*Configuracion promedio*/
  pthread_t tid0;
  pthread_attr_t attr0;
  pthread_attr_init(&attr0);
  pthread_create(&tid0, &attr0, promedio, arreglo);
  pthread_join(tid0, NULL);

  /*Configuracion minimo*/
  pthread_t tid1;
  pthread_attr_t attr1;
  pthread_attr_init(&attr1);
  pthread_create(&tid1, &attr1, minimo, arreglo);
  pthread_join(tid1, NULL);

  /*Configuracion maximo*/
  pthread_t tid2;
  pthread_attr_t attr2;
  pthread_attr_init(&attr2);
  pthread_create(&tid2, &attr2, maximo, arreglo);
  pthread_join(tid2, NULL);

  printf("Promedio: %d\n", media);
  printf("Minimo: %d\n", min);
  printf("Maximo: %d\n", max);
}

void *promedio(void *param) {
  int *arreglo = (int *)param;
  int suma = 0;
  int i;
  for (i = 0; arreglo[i] != -1; i++) {
    suma += arreglo[i];
  }
  media = suma / i;
  pthread_exit(0);
}

void *minimo(void *param) {
  int *arreglo = (int *)param;
  min = arreglo[0];
  for (int i = 0; arreglo[i] != -1; i++) {
    if (min > arreglo[i])
      min = arreglo[i];
  }
}

void *maximo(void *param) {
  int *arreglo = (int *)param;
  max = arreglo[0];
  for (int i = 0; arreglo[i] != -1; i++) {
    if (max < arreglo[i])
      max = arreglo[i];
  }
}
