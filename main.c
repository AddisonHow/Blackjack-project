#include "cards.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){
    
srand(time(NULL));  

struct card** cardDeck = createCardDeck();

struct game* game = createGame();

struct card** shuffledDeck = shuffleCardDeck(cardDeck);

//struct card* tempCard;

getPlayerStartingMoney(game);



 //printf("phand at [0] = %s of %ss\n", tempCard->name, tempCard->suit);

    while(game->continuePlaying == true){

        shuffledDeck = shuffleCardDeck(shuffledDeck);
        
        createAndDealHands(shuffledDeck, game);

        

        getPlayerBet(game);
        
        printDealerFaceupCard(game);

        int insurance = insuranceOrNoInsurance(game);
        
        if(insurance == 3 || insurance == 2){
            continue;
        }

        //printPoints(game->pHand);
        
        playerTurn(game, shuffledDeck);

        dealerTurn(game, shuffledDeck);
        
        playAgain(game);
    }

    printf("thanks for playing! you started with %d$ and left the table with %d$\n", game->startingMoney, game->curMoney);

}
