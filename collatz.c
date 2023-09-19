#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int numero = atoi(argv[1]);
  pid_t pid;
  pid = fork();
  int resultado;

  /* the size (in bytes) of shared memory object */
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char *name = "OS";

  /* shared memory file descriptor */
  int shm_fd;
  /* pointer to shared memory obect */
  void *ptr;
  /* create the shared memory object */

  if (pid == 0) {
    int numero = atoi(argv[1]);
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    /* configure the size of the shared memory object */
    ftruncate(shm_fd, SIZE);
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    while (numero != 1) {
      if (numero % 2 == 0) {
        numero /= 2;
      } else {
        numero = 3 * numero + 1;
      }

      sprintf(ptr, "numero: %d\n", numero);
      int digitos = 0, a = numero;
      while (a >= 1) {
        a /= 10;
        digitos++;
      }
      ptr += strlen("numero: \n") + digitos;
    }
  }

  
  if (pid > 0) {
    wait(NULL);
    /* open the shared memory object */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    /* read from the shared memory object */
    printf("%s", (char *)ptr);
    /* remove the shared memory object */
    shm_unlink(name);
  }
  return 0;
}

