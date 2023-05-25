#include "inventory.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void openinventory(Tamagotchi *t) {
  printf("## INVENTORY \n");
  int countitem, selectionoptionuser = 0;
  for (int i = 0; i < 100; i++) {
    if (t->inventory[i] >= 1) {
      countitem++;
      printf("Value inventory pos %i with value %i \n", i, t->inventory[i]);
    }
  }
  printf("## Select pos item for use 9999 for back\n");
  scanf("%d", &selectionoptionuser);
  if (selectionoptionuser != 9999)
    useitem(t, selectionoptionuser);
}

void useitem(Tamagotchi *t, int pos) {
  if (t->inventory[pos] >= 1) {
    switch (pos) {
    case POTION:
      t->life += 30;
      break;
    case SUPERPOTION:
      t->life += 60;
      break;
    case ULTRAPOTION:
      t->life += 100;
      break;
    case ELIXIR_HAPPINESS:
      t->happiness += 200;
      break;
    case ELIXIR_INTELLIGENCE:
      t->intelligence += 2;
      break;
    case ELIXIR_STRENGHT:
      t->strength += 2;
      break;
    case ELIXIR_AGILITY:
      t->agility += 2;
      break;
    case ELIXIR_CRITIC:
      t->critic++;
      break;
    case ELIXIR_DEFEND:
      t->defend += 2;
      break;
    case EMERGENCYFOOD:
      t->hunger += 100;
      break;

    default:
      break;
    }
    t->inventory[pos]--;
  }
}

void winrandomitem(Tamagotchi *t) {
  int randomcriticpotion = rand() % 8;
  int randomitemwin = rand() % 8;

  switch (randomitemwin) {
  case 7:
    if (randomcriticpotion == randomitemwin) {
      t->inventory[7]++;
    } else {
      t->inventory[8]++;
    }
    break;

  default:
    t->inventory[randomitemwin]++;
    break;
  }
}