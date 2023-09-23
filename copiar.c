/*ejemplo de pipes + manejo de archivos*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *source_file = argv[1];
  const char *destination_file = argv[2];

  int pipe_fd[2]; // Pipe file descriptors
  pid_t pid;      // Process ID

  // Create a pipe
  if (pipe(pipe_fd) == -1) {
    perror("Pipe creation failed");
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if (pid < 0) {
    perror("Fork failed");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {      // Child process (reader)
    close(pipe_fd[1]); // Close the write end of the pipe

    // Open the destination file for writing
    int destination_fd =
        open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (destination_fd == -1) {
      perror("Error opening destination file");
      exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read from the pipe and write to the destination file
    while ((bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE)) > 0) {
      if (write(destination_fd, buffer, bytes_read) == -1) {
        perror("Error writing to destination file");
        exit(EXIT_FAILURE);
      }
    }

    // Close file descriptors
    close(pipe_fd[0]);
    close(destination_fd);
    exit(EXIT_SUCCESS);
  } else {             // Parent process (writer)
    close(pipe_fd[0]); // Close the read end of the pipe

    // Open the source file for reading
    int source_fd = open(source_file, O_RDONLY);

    if (source_fd == -1) {
      perror("Error opening source file");
      exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read from the source file and write to the pipe
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
      if (write(pipe_fd[1], buffer, bytes_read) == -1) {
        perror("Error writing to pipe");
        exit(EXIT_FAILURE);
      }
    }

    // Close file descriptors
    close(pipe_fd[1]);
    close(source_fd);

    // Wait for the child process to complete
    wait(NULL);
    exit(EXIT_SUCCESS);
  }

  return 0;
}

