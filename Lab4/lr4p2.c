#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define R 0
#define W 1
#define TRUE 1
#define FALSE 0
#define PERIOD '.'

int main(int argc, char **argv) {
    int pid, c, NEWLINE = TRUE, total;
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
            fwrite(argv[1], sizeof(char), sizeof(argv[1]) + 1, fp);
            fclose(fp);
            close(R);
            dup(q[R]);
            close(q[R]);
            char c[100];
            fgets(c, sizeof(c), stdin);
            printf("Substring returned: %s", c);
        }
    }
    return 0;
}