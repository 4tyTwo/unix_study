#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
  int fd[2];
  int status;
  switch (fork()) {
    case -1:
      printf("Error while calling fork #1\n");
      exit(1);
    case 0:
      // child 1
      pipe(fd); // Create a pipe between parent & child
      switch (fork()) {
        case -1:
          printf("Error while calling fork #2\n");
          exit(2);
        case 0:
          close(0); // close stdin
          dup(fd[0]);
          close(fd[0]);
          close(fd[1]); // must be closed so execl won't be paused
          execl("./substring.out", "substring", 0);
          exit(0);
        default:
          close(1); // close stdout
          dup(fd[1]);
          close(fd[1]);
          close(fd[0]); // must be closed so execl won't be paused
          execl("./case_swap.out", "case_swap", 0);
      }
    default:
      wait(&status); // block until childs are finished
      exit(0);
  }
}