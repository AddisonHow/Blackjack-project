#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "cards.h"
#include "game.h"
/*
struct game{
    bool continuePlaying;
    int StartingMoney;
    int CurMoney;
    struct card* pHand[11];
    struct card* dHand[11];
};
*/

struct game* createGame(){
    struct game* game = malloc(sizeof(struct game));
    game->continuePlaying = true;
    game->topOfDeckIndex = 4;
    return game;
}
void createAndDealHands(struct card** shuffleCardDeck, struct game* game){
    //struct card* tempCard = malloc(sizeof(struct card));
    for(int i = 0; i < 11; i++){
        game->pHand[i] = NULL;
        game->dHand[i] = NULL;
    }
    game->pHand[0] = shuffleCardDeck[0];
    game->dHand[0] = shuffleCardDeck[1];
    game->pHand[1] = shuffleCardDeck[2];
    game->dHand[1] = shuffleCardDeck[3];

    //tempCard = game->pHand[0];

    //printf("player card1: %s of %ss\n", tempCard->name, tempCard->suit);

    
}
void printPoints(struct card* hand[]){
    int points = 0;
    int aceCount = 0;

    for(int i = 0; i < 11; i++){
        if(hand[i] == NULL){
            break;
        }
        points += hand[i]->cVal;
        if(strcmp(hand[i]->name, "ace") == 0){
            aceCount++;
        }
    }

    int softTotal = points;       // ace = 11
    int hardTotal = points - 10;  // ace = 1

    if(aceCount > 0 && softTotal <= 21){
        printf("your points: %d or %d\n", hardTotal, softTotal);
    } else {
        // either no ace, or soft total is already over 21 so only one valid total
        while(points > 21 && aceCount > 0){
            points -= 10;
            aceCount--;
        }
        printf("your points: %d\n", points);
    }
}
int trackPoints(struct card* hand[]){
    int points = 0;
    int aceCount = 0;
    for(int i = 0; i < 11; i++){
        if(hand[i] == NULL){
            break;
        }
        points += hand[i]->cVal;
        if(strcmp(hand[i]->name, "ace") == 0){
            aceCount++;
        }
    }
    if(aceCount > 0 && points > 21){
        while(points > 21 && aceCount > 0){
            points -= 10;
            aceCount--;
        }
    }
    return points;
}

void getPlayerBet(struct game* game){
    int pBet = 0;
    do{
    printf("how much would you like to bet?\n");
    scanf("%d", &pBet);
        if(game->curMoney > game->bet){
            printf("you dont have enough money to make this wager;");
        }
    }while(game->curMoney < pBet || pBet < 0);
    game->bet = pBet;
}

void getPlayerStartingMoney(struct game* game){
    int money = 0;
    printf("how much money would you like to enter the table with?\n");
    scanf("%d", &money);

    game->startingMoney = money;
    game->curMoney = money;

}
//checks to see if player has enough money to double down. 
//returns 1 if yes 0 if no
int doubleDown(struct game* game){
    if(game->bet * 2 > game->curMoney){
        printf("you dont have enough money to double down.");
        return 0;
    }
    else{return 1;}
}
int insuranceOrNoInsurance(struct game* game){
    struct card* tempCard = game->dHand[0];
    int insurance = 0;

    if(strcmp(tempCard->name, "ace") == 0){
        printf("would you like insurance -1- for yes and -2- for no?\n");
        scanf("%d", &insurance);
    }
    int dPoint = trackPoints(game->dHand);
        //player baught insurance and dealer doesnt have blackJack
        if(insurance == 1 && dPoint != 21){
            game->curMoney = game->curMoney - (game->bet / 2);
            printf("dealer didnt have black jack, you lost your insurance");
            return 1;
        }
        else if((trackPoints(game->pHand) == trackPoints(game->dHand)) && trackPoints(game->dHand) == 21){
            printf("you and dealer had 21, so you push");
            return 2;
            //push
        }
        //dealer has blackjack and player loses
        else if(insurance == 0 && trackPoints(game->dHand) == 21){
            
            game->curMoney = game->curMoney - game->bet;
            printf("dealer has blackjack you lost");
            return 3;
        }
        return 0;

}

void playerTurn(struct game* game, struct card** shuffledDeck){
    int choice = 1;
    int pHandI = 2;
    int hit = 0;
    
    struct card* tempCard2 = game->pHand[0];
    struct card* tempCard3 = game->pHand[1];
    printf("--------------------------------\n");
    printf("YOUR HAND\n");
    printf("--------------------------------\n");
    printf("your first card: %s of %ss\n", tempCard2->name, tempCard2->suit);
    printf("your second card: %s of %ss\n", tempCard3->name, tempCard3->suit);
    //printf("your points -%d-\n", trackPoints(game->pHand));
    printPoints(game->pHand);
    int curPoints = trackPoints(game->pHand);
    //printf("current points: %d\n", curPoints);
    if(curPoints == 21){
                printf("congrats you got a blackjack\n");
                game->curMoney = game->curMoney + game->bet + game->bet / 2;
                printf("you have -%d$- left\n", game->curMoney);
                return;
            }


    printf("would you like to hit(1), stay(2), or double down(3).");
    scanf("%d", &choice);

    if(choice == 3 && (doubleDown(game) == 1)){

        game->bet = game->bet * 2;
        struct card* tempCard = shuffledDeck[game->topOfDeckIndex];
            game->topOfDeckIndex = game->topOfDeckIndex + 1;
            game->pHand[pHandI] = tempCard;
            pHandI++;
            int curPoints = trackPoints(game->pHand);
            printf("you drew: %s of %ss\n", tempCard->name, tempCard->suit);  // show what card was drawn
            printf("current points: %d\n", curPoints);
            if(curPoints > 21){
                printf("you busted :(\n");
                game->curMoney = game->curMoney - game->bet;
                printf("you have -%d$- left to play with\n", game->curMoney);
                
                
            }
        }
    if(choice == 2){
        exit;
    }

    else{
        hit = 1;
       while(hit == 1){
    printf("would you like to hit -1- or stay -2- or double down -3-\n");
    scanf("%d", &hit);
        if(hit == 1){
            struct card* tempCard = shuffledDeck[game->topOfDeckIndex];
            game->topOfDeckIndex = game->topOfDeckIndex + 1;
            game->pHand[pHandI] = tempCard;
            pHandI++;
            int curPoints = trackPoints(game->pHand);
            printf("you drew: %s of %ss\n", tempCard->name, tempCard->suit);  // show what card was drawn
            printf("current points: %d\n", curPoints);
            if(curPoints > 21){
                printf("you busted :(\n");
                game->curMoney = game->curMoney - game->bet;
                printf("you have -%d$- left to play with\n", game->curMoney);
                hit = 2;
                
            }
            //else if(trackPoints(game->pHand) == 21){
            else if(tempCard2->cVal + tempCard3->cVal == 21){
                printf("congrats you got a blackjack\n");
                game->curMoney = game->curMoney + game->bet;
                printf("you have -%d$- left\n", game->curMoney);
                hit = 2;
            }
        }
         
        else{hit = 2;}
    }
    }

}
//old player turn function.
/*
void playerTurn(struct game* game, struct card** shuffledDeck){
    int hit = 1;
    int pHandI = 2;
    
    struct card* tempCard2 = game->pHand[0];
    struct card* tempCard3 = game->pHand[1];
    printf("--------------------------------\n");
    printf("YOUR HAND\n");
    printf("--------------------------------\n");
    printf("your first card: %s of %ss\n", tempCard2->name, tempCard2->suit);
    printf("your second card: %s of %ss\n", tempCard3->name, tempCard3->suit);
    //printf("your points -%d-\n", trackPoints(game->pHand));
    printPoints(game->pHand);
    //int curPoints = trackPoints(game->pHand);
    //printf("current points: %d\n", curPoints);
    if(tempCard2->cVal + tempCard3->cVal == 21){
                printf("congrats you got a blackjack\n");
                game->curMoney = game->curMoney + game->bet + game->bet / 2;
                printf("you have -%d$- left\n", game->curMoney);
                return;
            }
//------------
    while(hit == 1){
    printf("would you like to hit -1- or stay -2- or double down -3-\n");
    scanf("%d", &hit);
        if(hit == 1){
            struct card* tempCard = shuffledDeck[game->topOfDeckIndex];
            game->topOfDeckIndex = game->topOfDeckIndex + 1;
            game->pHand[pHandI] = tempCard;
            pHandI++;
            int curPoints = trackPoints(game->pHand);
            printf("you drew: %s of %ss\n", tempCard->name, tempCard->suit);  // show what card was drawn
            printf("current points: %d\n", curPoints);
            if(curPoints > 21){
                printf("you busted :(\n");
                game->curMoney = game->curMoney - game->bet;
                printf("you have -%d$- left to play with\n", game->curMoney);
                hit = 2;
                
            }
            //else if(trackPoints(game->pHand) == 21){
            else if(tempCard2->cVal + tempCard3->cVal == 21){
                printf("congrats you got a blackjack\n");
                game->curMoney = game->curMoney + game->bet;
                printf("you have -%d$- left\n", game->curMoney);
                hit = 2;
            }
        }
         
        else{hit = 2;}
         
    }   
    

}
    */
void dealerTurn(struct game* game, struct card** shuffledDeck){
if(trackPoints(game->pHand) > 21){
    return;
}
if(game->pHand[2] == NULL && trackPoints(game->pHand) == 21){
        return;
    }

int dealInd = 2;
struct card* tempCard2 = game->dHand[0];
struct card* tempCard3 = game->dHand[1];
printf("--------------------------------\n");
printf("DEALER'S HAND\n");
printf("--------------------------------\n");
printf("dealers first card: %s of %ss\n", tempCard2->name, tempCard2->suit);
sleep(2);
printf("dealers second card: %s of %ss\n", tempCard3->name, tempCard3->suit);
sleep(2);
printf("dealer points -%d-\n", trackPoints(game->dHand));
//printf("dealer points before loop: %d\n", trackPoints(game->dHand));
fflush(stdout);
while(trackPoints(game->dHand) < 17){
    struct card* tempCard = shuffledDeck[game->topOfDeckIndex];
    game->dHand[dealInd] = tempCard;
    dealInd++;
    game->topOfDeckIndex = game->topOfDeckIndex + 1;
    printf("%s of %ss\n", tempCard->name, tempCard->suit);
    fflush(stdout);  // force print before sleeping
    sleep(2);
    printf("dealer points -%d-\n", trackPoints(game->dHand));
    fflush(stdout);
}
    printf("--------------------------------\n");
    printf("YOUR POINTS: %d  |  DEALER POINTS: %d\n", trackPoints(game->pHand), trackPoints(game->dHand));  // side by side summary
    printf("--------------------------------\n");
    if(trackPoints(game->dHand) > 21){
        printf("dealer busted\n");
        
        game->curMoney = game->curMoney + game->bet;
        printf("you now have -%d$-\n", game->curMoney);

    }
    else if(trackPoints(game->dHand) == trackPoints(game->pHand)){
        printf("pushed\n");
        printf("you now have -%d$-\n", game->curMoney);
    }
    else if(trackPoints(game->pHand) > trackPoints(game->dHand)){
        printf("you win the hand\n");
        game->curMoney = game->curMoney + game->bet;
    }
    else{
        printf("dealer wins\n");
        game->curMoney = game->curMoney - game->bet;
        printf("you now have -%d$-\n", game->curMoney);

    }

}


void printDealerFaceupCard(struct game* game){
    //int card = 0;
    struct card* tempCard = game->dHand[0];
    printf("dealer card: %s of %ss\n", tempCard->name, tempCard->suit);
}






void playAgain(struct game* game){
    int continueYorN = 0;
    printf("================================\n");
    printf("would you like to play another round? -1- for yes and -2- for no\n");
    scanf("%d", &continueYorN);

    if(continueYorN == 2){
        game->continuePlaying = false;
    }
}

