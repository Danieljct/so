#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int cantidad;
long long* sucesion;

void *fib(void *param); /* the thread */

int main(int argc, char *argv[]) {

  cantidad = atoi(argv[1]);
  sucesion = malloc(cantidad*sizeof(long long));

  /*Configuracion promedio*/
  pthread_t tid0;
  pthread_attr_t attr0;
  pthread_attr_init(&attr0);
  pthread_create(&tid0, &attr0, fib, NULL);
  pthread_join(tid0, NULL);

  for(int i = 0; i < cantidad; i++){
    printf("%d, ",sucesion[i]);
  }
  free(sucesion);
}

void *fib(void *param) {
  sucesion[0] = 0; 
  sucesion[1] = 1;
  for(int i = 2; i< cantidad; i++){
    sucesion[i] = sucesion[i-1]+sucesion[i-2];
  }
}
