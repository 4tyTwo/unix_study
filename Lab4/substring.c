#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

char* delete_substrings(const char* string, int start) {
  char* tmp;
  tmp = malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(tmp, string);
  for (int i = start; i < strlen(tmp) - 1; ++i) {
    if (tmp[i] == tmp[i + 1])
      return delete_substrings(delete_substring(tmp, i), i);
  }
  return tmp;
}

int main() {
  char string[100];
  fgets(string, sizeof(string), stdin);
  char *newstring = delete_substrings(string, 0);
  fwrite(newstring, sizeof(char), sizeof(newstring) + 1, stdout);
  return 0;
}