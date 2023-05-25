//
//  KodPet.c
//  KodPetFlipper
//
//  Created by KodamaDeveloper
//
#include "system/kodpet.h"
#include "system/battle.c"
#include "system/battle.h"
#include "system/inventory.c"
#include "system/inventory.h"
#include "system/savedata.c"
#include "system/savedata.h"
#include "system/social.c"
#include "system/social.h"
#include "system/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Flipper

//#include <furi.h>
//#include <gui/gui.h>
//#include <input/input.h>

// Initialize a new Tamagotchi with default values
Tamagotchi *createTamagotchi() {
  Tamagotchi *t = malloc(sizeof(Tamagotchi));
  t->status = HUNGRY;
  t->hunger = 50;
  t->happiness = 50;
  t->cycle = 0;
  t->care = 10;
  t->evolution = EGG;
  t->level = 0;
  t->intelligence = 1;
  t->strength = 1;
  t->agility = 1;
  t->critic = 1;
  t->defend = 1;
  t->life = 100;
  t->name = "KodPet";
  t->money = 0;
  int countitem = 0;
  for (int i = 0; i < 100; i++) {
    t->inventory[i] = 0;
  }
  t->inventory[0] = 3;
  readsocial(t);
  if (savedataControl(t, "n", NULL))
    return t;
  return t;
}

// Perform an action on the Tamagotchi
void doAction(Tamagotchi *t, int action) {
  int probcritic = rand() % 10;
  int probcritictmp = rand() % 10;
  char *selector;
  switch (action) {
  case FEED:
    t->money -= 3;
    t->hunger += 30;
    if (t->life <= 99)
      t->life++;
    t->happiness += 6;
    t->care--;
    printf("########  LAST ACTION: FEED\n");
    break;
  case MEDICINE:
    if (t->status == SICK) {
      t->status = HAPPY;
      t->happiness -= 13;
      t->money -= 3;
    }
    printf("########  LAST ACTION: MEDICINE\n");
    break;
  case PLAY:
    t->happiness += 12;
    t->care--;
    printf("########  LAST ACTION: PLAY\n");
    break;
  case CARE:
    t->care += 10;
    if (t->care > 30) {
      t->care = 30;
      t->happiness += HAPPY_FOR_CARE;
    }
    printf("########  LAST ACTION: CARE\n");
    break;
  case STUDY:
    t->intelligence++;
    t->hunger -= 30;
    printf("########  LAST ACTION: STUDY\n");
    break;
  case WORK:
    t->strength++;
    t->hunger -= 30;
    t->happiness -= 10;
    t->money += 15;
    printf("########  LAST ACTION: WORK\n");
    break;
  case INVESTIGATE:
    t->agility++;
    t->hunger -= 38;
    t->money -= 10;
    printf("########  LAST ACTION: INVESTIGATE\n");
    break;
  case TRAIN:
    if (probcritic == probcritictmp)
      t->critic++;
    t->defend++;
    t->hunger -= 60;
    t->happiness++;
    printf("########  LAST ACTION: TRAIN\n");
    break;
  case TOOL:
    t->hunger--;
    t->happiness += 8;
    t->life++;
    t->care--;
    printf("########  LAST ACTION: TRAIN\n");
    break;
  case OPENINVENTORY:
    openinventory(t);
    printf("########  LAST ACTION: OPENINVENTORY\n");
    break;
  case EXPEDITION:
    t->hunger -= 30;
    t->happiness += 8;
    t->care--;
    printf("########  LAST ACTION: EXPEDITION: ");
    int actionexpedition = rand() % 3;
    switch (actionexpedition) {
    case FRIEND:
      printf("and you found friend %s \n",
             readfolderselector("friends", 0, rand() % t->friends + 1));
      winrandomitem(t);
      t->hunger -= 13;
      t->happiness += 50;
      break;
    case ENEMY:
      selector = readfolderselector("enemies", 0, rand() % t->enemies + 1);
      printf("and you found enemy %s \n", selector);
      Tamagotchi *enemyt = malloc(sizeof(Tamagotchi));
      char pathenemies[100] = "enemies/";
      strcat(pathenemies, selector);

      if (savedataControl(enemyt, "n", pathenemies) == 0) {
        printf("nices data enemny load \n");
        if (whowinbattlegotchi(t, enemyt) == 0) {
          printf("You win in BATTLE!! ^^ \n");
          t->cycle += 3;
          t->life++;
          t->happiness += 50;
          t->money += 20;
          winrandomitem(t);
        } else {
          printf("You losed in BATTLE!! :( \n");
          t->cycle += 1;
          t->happiness -= 13;
        }
      }
      break;
    case NPC:
      printf("and you found npc X with the personality Y  %s \n",
             readfolderselector("npc", 1, rand() % t->npcs + 1));
             t->money += 60;
      break;
    default:
      break;
    }
    break;
  case DUELFRIEND:
    selector = readfolderselector("friends", 0, rand() % t->friends + 1);
    printf("and you found duel friend wirh %s \n", selector);
    Tamagotchi *enemyt = malloc(sizeof(Tamagotchi));
    char pathenemies[100] = "friends/";
    strcat(pathenemies, selector);
    if (savedataControl(enemyt, "n", pathenemies) == 0) {
      printf("nices data friend load \n");
      if (whowinbattlegotchi(t, enemyt) == 0) {
        printf("You win in BATTLE!! ^^ \n");
        t->life++;
        t->happiness += 25;
        t->money += 10;
      } else {
        printf("You losed in BATTLE!! :( \n");
        t->cycle += 1;
        t->happiness -= 6;
        t->money -= 9;
      }
    }
    printf("########  LAST ACTION: DUEL FRIEND\n");
    break;
  }
}

// Update the Tamagotchi's status based on its current values
void updateStatus(Tamagotchi *t) {
  if (t->hunger <= DEAD_HUNGER || t->happiness <= DEAD_HAPPINESS) {
    if (t->life >= 1) {
      t->life -= DAMAGE_FOR_CARE;
      t->strength--;
      if (t->life >= 1)
        return;
    }
    t->status = DEAD;
    return;
  } else if (t->hunger < 20 || t->happiness < 20) {
    t->status = SICK;
  } else if (t->happiness >= 70) {
    t->status = HAPPY;
  } else if (t->hunger < 50) {
    t->status = HUNGRY;
  } else {
    t->status = NORMAL;
  }

  if (t->status == DIRTY) {
    t->happiness--;
    t->life--;
  }

  if (t->care <= 0) {
    t->status = DIRTY;
    t->life--;
  }
  int lifesg = t->defend + 100 + (t->evolution * 25) + (t->level * 2);
  if (t->life >= lifesg) {
    t->life = lifesg;
  }

  if (t->cycle >= ((CYCLE_EVOLUTION * (1 + t->evolution)) + t->level)) {
    if (t->evolution < QUANTUM)
      t->evolution++;
    t->cycle = 0;
    t->level++;
    t->life += 100;
    printf("########  LEVEL UP!!!\n");
  }
  int maxhpp = 100 + t->intelligence;
  if (t->happiness >= maxhpp) {
    t->happiness = maxhpp;
    t->status = HAPPY;
  }
int maxh = 100 + t->strength;
    if (t->hunger > maxh) {
      t->hunger = 100;
    }
}

// Print the current status of the Tamagotchi
void printStatus(Tamagotchi *t) {
  int selectionoptionuser = 0;
  int countitem = 0;
  for (int i = 0; i < 100; i++) {
    if (t->inventory[i] >= 1) {
      countitem++;
    }
  }
  printf("Total Different Items: %i\n", countitem);
  printf("Friends: %i\n", t->friends);
  printf("Enemies: %i\n", t->enemies);
  printf("NPC: %i\n", t->npcs);
  printf("########   %s\n", t->name);
  printf("Hunger: %d/%i\n", t->hunger, 100 + t->strength);
  printf("Happiness: %d/%i\n", t->happiness, 100 + t->intelligence);
  switch (t->status) {
  case HUNGRY:
    printf("Status: Hungry\n");
    break;
  case SICK:
    printf("Status: Sick\n");
    break;
  case HAPPY:
    printf("Status: HAPPY\n");
    break;
  case POWERED:
    printf("Status: POWERED\n");
    break;
  case GOD:
    printf("Status: GOD\n");
    break;
  case NORMAL:
    printf("Status: NORMAL\n");
    break;
  case DIRTY:
    printf("Status: DIRTY\n");
    break;
  case DEAD:
    printf("Status: Dead\n");
    break;
  }
  printf("Cycle: %i\n", t->cycle);
  printf("Money: %i\n", t->money);
  printf("Evolution: %i\n", t->evolution);
  printf("Level: %i\n", t->level);
  printf("Intelligence: %i\n", t->intelligence);
  printf("Strength: %i\n", t->strength);
  printf("Agility: %i\n", t->agility);
  printf("Critic: %i\n", t->critic);
  printf("Defend: %i\n", t->defend);
  printf("Life: %i/%i\n", t->life, t->defend + 100 + (t->evolution * 25) + (t->level * 2));

  printf(
      "\n\n######## Select Option: \n 0. FEED. \n 1. MEDICINE \n 2. PLAY \n "
      "4. CARE \n 5. STUDY \n 6. WORK \n 7. INVESTIGATE \n 8. TRAIN \n 9. "
      "TOOL \n 10. EXPEDITION \n 11. DUEL FRIEND \n 12. OPEN INVENTORY \n 98. "
      "Random Cycle Time \n 99. Close test \n");
  scanf("%d", &selectionoptionuser);

  int actionrandom = rand() % 10;
  switch (selectionoptionuser) {
  case 98:
    doAction(t, actionrandom);
    break;
  case 99:
    exit(0);
    break;
  default:
    doAction(t, selectionoptionuser);
    break;
  }

  printf("########   Selected: %i\n", selectionoptionuser);
}

int main() {
  srand(time(NULL));

  Tamagotchi *t = createTamagotchi();

  // Main game loop
  while (t->status != DEAD) {
    // Randomly choose an action for the Tamagotchi to perform

    // Decrease hunger and happiness over time
    t->hunger -= CYCLE_HUNTER;
    t->happiness -= CYCLE_HAPPINESS;

    // Update the Tamagotchi's status based on its current values
    updateStatus(t);

    // Print the current status of the Tamagotchi
    printStatus(t);
    t->cycle++;

    if (savedataControl(t, "s", NULL) == 0)
      printf("Saved progress");

    // TODO: hospital
    if (t->status != DEAD && t->money >= TAXREVIVE) {
      int tax = TAXREVIVE * t->evolution;
      t->money -= tax;
      printf("In a state of danger, has been able to pay for hospital costs %i",
             tax);
      t->status = NORMAL;
    }
  }

  // Game over
  printf("Game over!\n");

  return 0;
}

void readsocial(Tamagotchi *t) {
  t->enemies = readfolder("enemies", 0);
  t->friends = readfolder("friends", 0);
  t->npcs = readfolder("npc", 1);
}
