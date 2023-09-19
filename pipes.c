#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 250
#define READ_END 0
#define WRITE_END 1
int main(void) {

  char write_msg[BUFFER_SIZE] = "Hola mundo NASHE xD";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  int fd2[2];
  pid_t pid;

  /* create the pipe */
  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }
  if (pipe(fd2) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  /* fork a child process */
  pid = fork();

  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }

  if (pid > 0) { /* parent process */
    /* close the unused end of the pipe */
    close(fd[READ_END]);
    /* write to the pipe */
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
    /* close the write end of the pipe */
    close(fd[WRITE_END]);
    wait(NULL);
    close(fd2[WRITE_END]);
    read(fd2[READ_END], read_msg, BUFFER_SIZE);
    printf("%s", read_msg);
    close(fd2[READ_END]);
  }

  else { /* child process */
    /* close the unused end of the pipe */
    close(fd[WRITE_END]);
    close(fd2[READ_END]);
    /* read from the pipe */
    read(fd[READ_END], read_msg, BUFFER_SIZE);

    for (int i = 0, len = strlen(read_msg); i < len; i++) {
      if (read_msg[i] == ' ')
        ;
      else if (read_msg[i] < 'a')
        read_msg[i] += 32;
      else
        read_msg[i] -= 32;
    }

    write(fd2[WRITE_END], read_msg, strlen(read_msg) + 1);
    /* close the write end of the pipe */
    close(fd2[WRITE_END]);
    close(fd[READ_END]);
  }
  return 0;
}
