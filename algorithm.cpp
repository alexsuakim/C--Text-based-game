#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

int algorithm (int userCard, int userBetTotal, int compBetTotal) {
    int compBet;
    static int turnNumber = 0;
    srand(time(NULL));

    if (userCard <=3) { //scenario #1
        switch (turnNumber) {
            case 0: //comp first turn 
                if (userBetTotal == 1) { //only with user default betting info
                    //random of 3, 4, or 5
                    compBet = (rand() % 3) + 3;
                    turnNumber = 1;
                } else { //with updated user betting info
                    //userBetTotal - compBetTotal +1 
                    compBet = userBetTotal - compBetTotal +1;
                    turnNumber = 2;
                }
                break;
            case 1: //
                compBet = userBetTotal - compBetTotal +1;
                turnNumber = 2;
                break;
            case 2: //last turn for comp to end
                compBet = userBetTotal - compBetTotal;
                turnNumber = 0; //reset
                break;
        } 
    } else if (userCard <= 7){ //scenario #2
        switch (turnNumber) {
            case 0: //comp first turn 
                if (userBetTotal == 1) { //only with user default betting info
                    //random of 1, 2, or 3
                    compBet = (rand() % 3) + 1;
                    turnNumber = 1;
                } else { //with updated user betting info
                    //bet the same Total as user and end the round
                    compBet = userBetTotal - compBetTotal;
                    turnNumber = 0;
                }
                break;
            case 1: //
                compBet = userBetTotal - compBetTotal;
                turnNumber = 0;
                break;
        } 
    } else if (userCard <= 9) { //scenario #3
        compBet = 0;
        turnNumber = 0; //reset
    } else if (userCard == 10) {
        switch (turnNumber) {
            case 0: //comp first turn 
                if (userBetTotal == 1) { //only with user default betting info
                    //random of 0, 3, 4, or 5
                    compBet = rand() % 6;
                    if (compBet <= 2) { 
                        compBet = 0;
                        turnNumber = 0; //end the round
                    } else {
                        turnNumber = 1;
                    }
                    
                } else { //with updated user betting info
                    compBet = 0;
                    turnNumber = 0;
                }
                break;
            case 1: 
                compBet = 0;
                turnNumber = 0;
                break;
        } 
    }
    if (compBet > 20) {
        compBet = compBet % 10;
    }
    return compBet;
}
