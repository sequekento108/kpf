#include "social.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

char *readfolderselector(char *npc, int point, int select) {
  DIR *folder;
  struct dirent *entry;
  int files = 0;
  folder = opendir(npc);
  if (folder == NULL) {
    perror("Unable to read directory");
  }

  while ((entry = readdir(folder))) {
    switch (point) {
      // friend enemies
    case 0:
      if (!strstr(entry->d_name, ".")) {
        files++;
        if(files == select)
         return entry->d_name;
      }
      break;
      // npc
    case 1:
      if (endswithfoonpc(entry->d_name) == 0) {
        files++;
        if(files == select)
         return entry->d_name;
      }
      break;
    default:
      break;
    }
  }

  closedir(folder);
  return NULL;
}

int readfolder(char *npc, int point) {
  DIR *folder;
  struct dirent *entry;
  int files = 0;
  folder = opendir(npc);
  if (folder == NULL) {
    perror("Unable to read directory");
  }

  while ((entry = readdir(folder))) {
    switch (point) {
      // friend enemies
    case 0:
      if (!strstr(entry->d_name, ".")) {
        files++;
        printf("%s %3d: %s\n", npc, files, entry->d_name);
      }
      break;
      // npc
    case 1:
      if (endswithfoonpc(entry->d_name) == 0) {
        files++;
        printf("%s %3d: %s\n", npc, files, entry->d_name);
      }
      break;
    default:
      break;
    }
  }

  closedir(folder);
  return files;
}

int endswithfoonpc(char *string) {
  string = strrchr(string, '.');
  if (string != NULL)
    return (strcmp(string, ".npcpet"));
  return -1;
}