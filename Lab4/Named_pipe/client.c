#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "server.h"

char *substring(const char *string, int pos, int len) {
    char *newstring;
    newstring = malloc(sizeof(char) * (len + 1));
    strcpy(newstring, string);
    int j = 0;
    for (int i = pos; i < pos + len; ++i) {
        newstring[j++] = string[i];
    }
    newstring[j] = '\0';
    return newstring;
}

char *delete_substring(const char *string, int start) {
    int i = start;
    while (string[start] == string[i] && start < strlen(string))
        ++i;
    int substrlen = i - start;
    int length = strlen(string) - substrlen;
    char *newstring = malloc(sizeof(char) * length + 1);
    newstring = substring(string, 0, start);
    char *tmp2 = substring(string, i, strlen(string) - i);
    strcat(newstring, tmp2);
    return newstring;
}

char *delete_substrings(const char *string, int start) {
    char *tmp;
    tmp = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(tmp, string);
    for (int i = start; i < strlen(tmp) - 1; ++i) {
        if (tmp[i] == tmp[i + 1])
            return delete_substrings(delete_substring(tmp, i), i);
    }
    return tmp;
}

int main(int argc, char **argv){
    struct message msg;
    int n, fdpub, fdpriv;
    char line[LINESIZE];
    /* синтезировать имя личного программного канала и создать этот канал с правами чтения и записи для всех процессов*/
    sprintf(msg.privfifo, "Fifo % d", getpid());
    if (mkfifo(msg.privfifo, S_IFIFO | 0666) == -1) {
        perror(msg.privfifo);
        exit(1);
    }
    /* общедоступный именованный канал (создается перед запуском сервера %mkfifo public) открывается на запись, и в него записываются имена личного канала и требуемого файла */
    if ((fdpub = open(PUBLIC, O_WRONLY)) == -1) {
        perror(PUBLIC);
        exit(2);
    }
    strcpy(msg.filename, argv[1]);
    write(fdpub, (char *)&msg, sizeof(msg));
    /* личный именованный канал открывается для чтения */
    if ((fdpriv = open(msg.privfifo, O_RDONLY)) == -1) {
        perror(msg.privfifo);
        exit(3);
    }
    /*распечатать данные, полученные из личного канала */
    while ((n = read(fdpriv, line, LINESIZE)) > 0) {
        char delim[] = "\n";
        char *ptr = strtok(line, delim);
        while (ptr != NULL) {
            printf("%s\n", delete_substrings(ptr, 0));
            ptr = strtok(NULL, delim);
        }
    }
    /*личный именованный канал закрывается и удаляется из текущего каталога */
    close(fdpriv);
    unlink(msg.privfifo);
    exit(0);
}
