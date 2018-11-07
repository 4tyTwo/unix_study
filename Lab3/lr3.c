// This program prints out names of all directories, that have subdirectories

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int is_hidden_dir(char *dir) {
  char exclude[] = ".";
  char exclude2[] = "..";
  if (strcmp(dir, exclude) == 0 || strcmp(dir, exclude2) == 0)
      return 1;
  return 0;
}


int has_sub_dirs(char *path) {
  DIR *dp;
  struct dirent *d;
  struct stat st;
  char rel_path[258]; // 255 as max length + ./ + /
  if ((dp = opendir(path)) == NULL)
    return -1;
  while ((d = readdir(dp))) {
    if (d->d_ino != 0) {
      if (is_hidden_dir(d->d_name) == 0) {
        strcpy(rel_path, "./");
        strcat(rel_path, path);
        strcat(rel_path, "/");
        strcat(rel_path, d->d_name);
        if (stat(rel_path, &st) == 0) {
          if (S_ISDIR(st.st_mode) == 1)
            return 1;
        }
        else
          printf("Stat failed, error: %d\n", errno);
      }
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  DIR *dp;
  struct dirent *d;
  printf("Subdirectories, that have subdirectories:\n");
  if ((dp = opendir(argv[1]))== NULL)
    return -1;
  while ((d = readdir(dp))) {
    if (d->d_ino != 0) {
      if(is_hidden_dir(d->d_name) == 0) {
        if (has_sub_dirs(d->d_name) == 1)
          printf("%s\n", d->d_name);
      }
    }
  }
  return 0;
}
