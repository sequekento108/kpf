#include "savedata.h"
#include "./kodpet.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void dataopen(char *selector) {
  char ch, *fname, social[100], socialt[100];
  FILE *fpts, *fptt;

  printf("\n\n Decrypt a text file :\n");
  printf("--------------------------\n");

  if (selector == NULL) {
    fname = "memorycard/data.txt";
  } else {
    strcat(social, selector);
    fname = social;
    strcat(fname, "/data.txt");
  }

  fpts = fopen(fname, "w");
  if (fpts == NULL) {
    printf(" File does not exists or error in opening..!! 001");
    exit(7);
  }

  if (selector == NULL) {
    fptt = fopen("memorycard/temp.txt", "r");
  } else {
    strcat(socialt, selector);
    strcat(socialt, "/temp.txt");
    fptt = fopen(socialt, "r");
  }

  if (fptt == NULL) {
    printf(" File does not exists or error in opening..!! 002");
    fclose(fpts);
    exit(9);
  }
  while (1) {
    ch = fgetc(fptt);
    if (ch == EOF) {
      break;
    } else {
      ch = ch - 100;
      fputc(ch, fpts);
    }
  }
  printf(" The file %s desprotected successfully..!!\n\n", fname);
  fclose(fpts);
  fclose(fptt);
}
void dataclose(char *selector) {
  char *fname, ch, social[100], socialt[100];
  FILE *fpts, *fptt;

  printf("\n\n Encrypt a text file :\n");
  printf("--------------------------\n");

  if (selector == NULL) {
    fname = "memorycard/data.txt";
  } else {
    strcat(social, selector);
    fname = social;
    strcat(fname, "/data.txt");
  }

  fpts = fopen(fname, "r");
  if (fpts == NULL) {
    printf(" File does not exists or error in opening..!! 003");
    exit(1);
  }
  if (selector == NULL) {
    fptt = fopen("memorycard/temp.txt", "w");
  } else {
    strcat(socialt, selector);
    strcat(socialt, "/temp.txt");
    fptt = fopen(socialt, "w");
  }
  if (fptt == NULL) {
    printf(" Error in creation of file temp.txt ..!!");
    fclose(fpts);
    exit(2);
  }
  while (1) {
    ch = fgetc(fpts);
    if (ch == EOF) {
      break;
    } else {
      ch = ch + 100;
      fputc(ch, fptt);
    }
  }
  fclose(fpts);
  fclose(fptt);
  fpts = fopen(fname, "w");
  if (fpts == NULL) {
    printf(" File does not exists or error in opening..!! 004");
    exit(3);
  }
  if (selector == NULL) {
    fptt = fopen("memorycard/temp.txt", "r");
  } else {
    fptt = fopen(socialt, "r");
    printf("%s", socialt);
  }
  if (fptt == NULL) {
    printf(" File does not exists or error in opening..!! 005");
    fclose(fpts);
    exit(4);
  }
  while (1) {
    ch = fgetc(fptt);
    if (ch == EOF) {
      break;
    } else {
      fputc(ch, fpts);
    }
  }
  printf(" File %s successfully protected ..!!\n\n", fname);
  fclose(fpts);
  fclose(fptt);
}

int parseInt(char *chars) {
  int sum = 0;
  int len = strlen(chars);
  for (int x = 0; x < len; x++) {
    int n = chars[len - (x + 1)] - '0';
    sum = sum + powInt(n, x);
  }
  return sum;
}

int powInt(int x, int y) {
  for (int i = 0; i < y; i++) {
    x *= 10;
  }
  return x;
}

int savedataControl(Tamagotchi *t, char *mode, char *selector) {
  char *fileName, social[100], socialt[100];
  if (selector == NULL) {
    fileName = "memorycard/data.txt";

  } else {
    strcat(social, selector);
    fileName = social;
    strcat(fileName, "/data.txt");
  }

  char *normal = "n";
  char *save = "s";
  if (!access(fileName, F_OK) && mode == normal) {
    dataopen(selector);
    printf("The File %s\t was Found\n", fileName);
    FILE *file_pointer;
    char buffer[64], c;

    file_pointer = fopen(fileName, "r");
    printf("----read a line progress----\n");
    fgets(buffer, 50, file_pointer);
    printf("%s\n", buffer);

    printf("----read and parse data progress----\n");
    file_pointer = fopen(fileName, "r"); // reset the pointer
    char str1[10], str2[10], str3[10], str4[10], str5[10], str6[10], str7[10],
        str8[10], str9[10], str10[10], str11[10], str12[10], str13[10],
        str14[10], str15[10], str16[201];
    fscanf(file_pointer, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
           str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11,
           str12, str13, str14, str15, str16);

    printf("----read the entire file progress----\n");

    file_pointer = fopen(fileName, "r"); // reset the pointer
    while ((c = getc(file_pointer)) != EOF)
      printf("%c", c);

    t->status = parseInt(str1);
    t->hunger = parseInt(str2);
    t->happiness = parseInt(str3);
    t->cycle = parseInt(str4);
    t->care = parseInt(str5);
    t->evolution = parseInt(str6);
    t->level = parseInt(str7);
    t->intelligence = parseInt(str8);
    t->strength = parseInt(str9);
    t->agility = parseInt(str10);
    t->critic = parseInt(str11);
    t->defend = parseInt(str12);
    t->life = parseInt(str13);
    t->name = str14;
    t->money = parseInt(str15);
    int leninv = strlen(str16);
    int counti = 0;
    for (int i = 0; i < leninv; i++) {
      char ri = str16[i];
      int itemvalue = 0;
      switch (ri) {
      case 'i':
        counti++;
        break;
      case ' ':
        /* code */
        break;
      case '0':
      default:
        itemvalue = ri - '0';
        t->inventory[i - counti] = itemvalue;
        break;
      }
    }
    fclose(file_pointer);
    dataclose(selector);
    return 0;
  } else {
    if (mode != save) {
      printf("The File %s\t not Found\n", fileName);
    } else {
      printf("Saved progress control");
    }

    int i;
    FILE *fptr;
    char fn[64];
    char str[64];
    char inventord[400] = "";
    for (int i = 0; i < 100; i++) {

      // char *itemvalue;
      int val = t->inventory[i];
      char value = val + '0';
      // snprintf(itemvalue, 1, "%d", t->inventory[i]);
      // strncat(itemvalue, &value, 2);
      strncat(inventord, &value, 1);
      strcat(inventord, "i");
    }

    printf("Generated inventory");

    snprintf(str, sizeof(str),
             "%i %i %i %i %i %i %i %i %i %i %i %i %i %s %i %s", t->status,
             t->hunger, t->happiness, t->cycle, t->care, t->evolution, t->level,
             t->intelligence, t->strength, t->agility, t->critic, t->defend,
             t->life, t->name, t->money, inventord);
    fptr = fopen(fileName, "w"); // "w" defines "writing mode"
    for (i = 0; str[i]; i++) {
      /* write to file using fputc() function */
      fputc(str[i], fptr);
    }
    fclose(fptr);
    dataclose(NULL);
    return 0;
  }

  if (!access(fileName, R_OK)) {
    printf("The File %s\t can be read\n", fileName);
  } else {
    printf("The File %s\t cannot be read\n", fileName);
  }

  if (!access(fileName, W_OK)) {
    printf("The File %s\t it can be Edited\n", fileName);
    return 1;
  } else {
    printf("The File %s\t it cannot be Edited\n", fileName);
  }

  if (!access(fileName, X_OK)) {
    printf("The File %s\t is an Executable\n", fileName);
  } else {
    printf("The File %s\t is not an Executable\n", fileName);
  }
}
