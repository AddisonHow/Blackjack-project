#ifndef CARDS_H
#define CARDS_H

struct card{
    int cVal;
    char* suit;
    char* name;
};



int pointConv(struct card* card);

char* nameConv(int i);

struct card** createCardDeck();

struct card** shuffleCardDeck(struct card** cardDeck);
 

#endif
