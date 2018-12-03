#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define R 0
#define W 1

int main() {
  int p[2], q[2];
  FILE *fdopen(), *fp;
  pipe(p);
  pipe(q);
  switch (fork()) {
    case 0:
      // child
      // P stream
      close(p[W]);
      close(R);
      dup(p[R]);
      close(p[R]);
      // Q stream
      close(q[R]);
      close(W);
      dup(q[W]);
      close(q[W]);
      //
      execl("./substring.out", "substring", 0);
      printf("Error calling substring\n");
    case -1:
      printf("Error while calling fork\n");
      exit(1);
    default:
      close(p[R]);
      close(q[W]);
      fp = fdopen(p[W], "w");
      char st[100];
      fgets(st, sizeof(st), stdin);
      fwrite(st, sizeof(char), sizeof(st) + 2, fp);
      fclose(fp);
      close(R);
      dup(q[R]);
      close(q[R]);
      execl("./case_swap.out", "case_swap", 0);
      exit(0);
  }
}