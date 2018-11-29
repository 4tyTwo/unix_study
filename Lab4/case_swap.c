#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

void case_swap(char *string) {
    for (int i = 0; i < strlen(string); ++i)
        if (islower(string[i]))
            string[i] = string[i] - 32;
        else 
            if (isupper(string[i]))
                string[i] = string[i] + 32;
}

int main() {
    char string[100];
    fgets(string, sizeof(string), stdin);
    case_swap(string);
    printf("%s", string);
    return 0;
}