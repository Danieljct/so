#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int numero;

void *primos(void *param); /* the thread */

int main(int argc, char *argv[]) {

  numero = atoi(argv[1]);

  /*Configuracion promedio*/
  pthread_t tid0;
  pthread_attr_t attr0;
  pthread_attr_init(&attr0);
  pthread_create(&tid0, &attr0, primos, NULL);
  pthread_join(tid0, NULL);
}

void *primos(void *param) {
  for (int i = 1; i < numero; i++) {
    int flag = 0;
    for (int j = 2; j <= i / 2 + 1; j++) {
      if (i % j == 0) {
        flag = 1;
      }
    }
    if (!flag)
      printf("El numero %d es primo\n", i);
  }
}
