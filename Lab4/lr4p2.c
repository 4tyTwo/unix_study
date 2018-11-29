#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define R 0
#define W 1
#define TRUE 1
#define FALSE 0

void case_swap(char *string) {
    for (int i = 0; i < strlen(string); ++i)
        if (islower(string[i]))
            string[i] = string[i] - 32;
        else if (isupper(string[i]))
            string[i] = string[i] + 32;
}

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
            fwrite(argv[1], sizeof(char), sizeof(argv[1]) + 2, fp);
            fclose(fp);
            close(R);
            dup(q[R]);
            close(q[R]);
            char c[101];
            fgets(c, sizeof(c), stdin);
            case_swap(c);
            printf("Substring returned and case swapped: %s\n", c);
        }
    }
    return 0;
}