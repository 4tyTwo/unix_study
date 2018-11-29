#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


int main() {
    int tube[2];
    pipe(tube);
    if (fork() == 0) {
      // this is the child process
      close(tube[0]); // reading end of the pipe
      dup2(tube[1], 1); // stdout ---> pipe writing end
	  execl("./substring.out", "substring.out", NULL);
    }
    else {
      if (fork() == 0) {
        close(tube[1]); // writing end of the pipe
        dup2(tube[0], 0);  // stdin ----> pipe reading end
		execl("./case_swap.out", "case_swap.out", NULL);
      }
    }
  return 0;
}
