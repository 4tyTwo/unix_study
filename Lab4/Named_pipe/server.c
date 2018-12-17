#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "server.h"

int main() {
    int fdpub, fdpriv, fd;
    struct message msg;
    int n;
    char line[LINESIZE];
    while (1) {
        if ((fdpub = open("public", O_RDONLY)) == -1) {
            perror("public");
            exit(1);
        }
        while (read(fdpub, (char *)&msg, sizeof(msg)) > 0) {
            if ((fd = open(msg.filename, O_RDONLY)) == -1) {
                perror(msg.filename);
                break;
            }
            // Личный канал открываем для записи. Сервер спит, пока клиент не откроет свой конец личного канала.
            if ((fdpriv = open(msg.privfifo, O_WRONLY)) == -1) {
                perror(msg.privfifo);
                break;
            }
            // Данные из файла копируем в личный канал.
            while ((n = read(fd, line, LINESIZE)) > 0) {
                // фильтр case_swap
                for (int i = 0; i < strlen(line); i++) {
                    if (islower(line[i]))
                        line[i] = line[i] - 32;
                    else if (isupper(line[i]))
                        line[i] = line[i] + 32;
                }
                write(fdpriv, line, n);
            }
            close(fd); // Закрываем файл.
            close(fdpriv); //Закрываем личный канал.
        }
        close(fdpub); // Закрываем общедоступный канал.
    }
}
