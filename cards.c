#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cards.h"

/*
struct card{
    int cVal;
    char* suit;
    char* name;
};*/
/*
struct cardDeck{
    struct card* cardDeck[51];
};
*/


int pointConv(struct card* card){

    if(strcmp(card->name, "king") == 0 || strcmp(card->name, "jack") == 0 || strcmp(card->name, "queen") == 0  ){
        card->cVal = 10;
    }
    else if(strcmp(card->name, "ace") == 0 ){
        card->cVal = 11;
    }
    else{
        card->cVal = atoi(card->name);
    }
    return card->cVal;
}
char* nameConv(int i){
    char* name;
    if(i == 1){
        name = "ace";
    }
    else if(i == 11){
        name = "jack";
    }
    else if(i == 12){
        name = "queen";
    }
    else if(i == 13){
        name = "king";
    }
    else{
        char* buf = malloc(4);
        snprintf(buf, 4, "%d", i);
        name = buf;
    }
    return name;
}

////////
struct card** createCardDeck(){

struct card** cardDeck = malloc(52 * sizeof(struct card*));
//create an array of 52 cards
/*for(int i = 0; i < 52; i++){
    struct card* newCard = malloc(sizeof(struct card));
    cardDeck[i] = newCard;
}*/

    for(int i = 1; i <= 13; i++){
        //new card struct with heart suit inserted at i'th index 
        struct card* newHeart = malloc(sizeof(struct card));
            newHeart->suit = "heart";
            newHeart->name = nameConv(i);
            newHeart->cVal = pointConv(newHeart);
            cardDeck[i - 1] = newHeart;
            
        
        //new card struct with heart suit inserted at i'th + 13 index 
        struct card* newSpade = malloc(sizeof(struct card));
            newSpade->suit = "spade";
            newSpade->name = nameConv(i);
            newSpade->cVal = pointConv(newSpade);
            cardDeck[i + 12] = newSpade;
        //new card struct with heart suit inserted at i'th + 26 index 
        struct card* newClub = malloc(sizeof(struct card));
            newClub->suit = "club";
            newClub->name = nameConv(i);
            newClub->cVal = pointConv(newClub);
            cardDeck[i + 25] = newClub;
        //new card struct with heart suit inserted at i'th + 39 index 
        struct card* newDiamond = malloc(sizeof(struct card));
            newDiamond->suit = "diamond";
            newDiamond->name = nameConv(i);
            newDiamond->cVal = pointConv(newDiamond);
            cardDeck[i + 38] = newDiamond;

    }
    return cardDeck;
}



struct card** shuffleCardDeck(struct card** cardDeck){

    struct card** shuffledDeck = cardDeck;
    struct card* tempCard1 = malloc(sizeof(struct card));
    for(int i = 0; i < 52; i++){
    tempCard1 = shuffledDeck[i];
        int randIdc1 = rand() % 52;
        int randIdc2 = rand() % 52;
        if(randIdc1 != i){
            shuffledDeck[i] = shuffledDeck[randIdc1];
            shuffledDeck[randIdc1] = tempCard1;  
        }
        else{
            shuffledDeck[i] = shuffledDeck[randIdc2];
            shuffledDeck[randIdc2] = tempCard1;
            //printf("shuffledDeck: %s of %ss\n", shuffledDeck[i]->name, shuffledDeck[i]->suit);
        }
    }
    for(int i = 0; i < 52; i++){
    //printf("shuffledDeck: %s of %ss\n", shuffledDeck[i]->name, shuffledDeck[i]->suit);
    }
    return shuffledDeck;
}

/*
int main(){

srand(time(NULL));  

struct card** cardDeck = createCardDeck();

struct card** shuffledDeck = shuffleCardDeck(cardDeck);



}
*/




