#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// custom domi gia tin trapoula

struct Card {
    char aksia;
    char symbolo;
};

// arxikopoiish synartiseon

void shuffle(struct Card deck[], int megethos);
void show(struct Card deck[]);

// anoigma main

int main(void) {
   
   struct Card deck[52];
   char aksia[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
   char symbolo[] = {'H', 'D', 'C', 'S'};
   int metritis = 0;

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            deck[metritis].aksia = aksia[i];
            deck[metritis].symbolo = symbolo[j];
            metritis++;
    }
}

// synarthseis

shuffle(deck, 52);
show(deck);
}

// orismos synarthshs anakatematos

void shuffle(struct Card deck[], int megethos) {
    srand(5565); 
    for (int i = 0; i < megethos; i++) {
       int j = rand() % megethos;
       struct Card temp = deck[i];
       deck[i] = deck[j];
       deck[j] = temp;
    }
}
// orismos synarthshs emfanisis tvn xartiwn 
void show(struct Card deck[]) {
int metritis = 0;

// titlos pasientzas

printf("Pasientza: \n");
printf("___________\n");
printf("\n");

// oi protes 4 sthles

for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
printf("%c%c ", deck[metritis].aksia, deck[metritis].symbolo);
metritis++;
    }
    printf("\n");
}

// epomenes 4 sthles

for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
printf("%c%c ", deck[metritis].aksia, deck[metritis].symbolo);
metritis++;
    }
    printf("\n");
}
}