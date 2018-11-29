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
    if (fork() == 0) {
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
        execl("./substring.out", "substring.out", NULL);
        printf("error\n");
    } 
    else {
        if (fork() == 0) {
            close(p[R]);
            close(q[W]);
            fp = fdopen(p[W],"w");
			char st[100];
			fgets(st, sizeof(st), stdin);
            fwrite(st, sizeof(char), sizeof(st) + 2, fp);
            fclose(fp);
            close(R);
            dup(q[R]);
            close(q[R]);
			execl("./case_swap.out", "case_swap.out", NULL);
        }
    }
    return 0;
}