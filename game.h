#ifndef GAME_H
#define GAME_H
#include <stdbool.h>

struct game{
    bool continuePlaying;
    int startingMoney;
    int curMoney;
    struct card* pHand[11];
    struct card* dHand[11];
    int bet;
    int topOfDeckIndex;
    bool doubleDown;
};
struct game* createGame();
void createAndDealHands(struct card** shuffleCardDeck, struct game* game);
void printPoints(struct card* hand[]);
int trackPoints(struct card* hand[]);
void getPlayerStartingMoney(struct game* game);
int doubleDown(struct game* game);
int insuranceOrNoInsurance(struct game* game);
void getPlayerBet(struct game* game);
void playAgain(struct game* game);
void playerTurn(struct game* game, struct card** shuffledDeck);
void printDealerFaceupCard(struct game* game);
void dealerTurn(struct game* game, struct card** shuffledDeck);
#endif
