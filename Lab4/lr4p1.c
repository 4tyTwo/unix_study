#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

char* substring(const char* string, int pos, int len) {
  char *newstring;
  newstring  = malloc(sizeof(char) * (len + 1));
  strcpy(newstring, string);
  int j = 0;
  for (int i = pos; i < pos + len; ++i) {
    newstring[j++] = string[i];
  }
  newstring[j] = '\0';
  return newstring;
}

char* delete_substring(const char* string, int start) {
  int i = start;
  while (string[start] == string[i] && start < strlen(string))
    ++i;
  int substrlen = i - start;
  int length = strlen(string) - substrlen;
  char* newstring = malloc(sizeof(char) * length + 1);
  newstring = substring(string, 0, start);
  char* tmp2 = substring(string, i, strlen(string) - i);
  strcat(newstring, tmp2);
  return newstring;
}

char* delete_substrings_inner(const char* string, int start_pos) {
  char* tmp;
  tmp = malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(tmp, string);
  for (int i = start_pos; i < strlen(tmp) - 1; ++i) {
    if (tmp[i] == tmp[i + 1])
      return delete_substrings_inner(delete_substring(tmp, i), i);
  }
  return tmp;
}

char* delete_substrings(const char* string) {
  return delete_substrings_inner(string, 0);
}

void capitalize(char* string) {
  for (int i = 0; i < strlen(string); ++i)
    if (islower(string[i]) != 0)
      string[i] = string[i] - 32;
}

int main() {
    int tube[2];
    pipe(tube);
    if (fork() == 0) {
      // this is the child process
      close(tube[0]); // reading end of the pipe
      dup2(tube[1], 1); // stdout ---> pipe writing end
      char test[] = "tteebqaaq";
      printf("%s\n", delete_substrings(test));
    }
    else {
      if (fork() == 0) {
        close(tube[1]); // writing end of the pipe
        dup2(tube[0], 0);  // stdin ----> pipe reading end
        char c[100];
        fgets(c, sizeof(c), stdin);
        capitalize(c);
        printf("RETURNED: %s\n", c);
      }
    }
  return 0;
}
