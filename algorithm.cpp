#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

int algorithm (int userCard, int userBetTotal, int compBetTotal) {
    int compBet;
    static int turnNumber = 0;
    if (userCard >=1 && userCard <=3) {
        switch (turnNumber) {
            case 0: //comp first turn 
                if (userBetTotal == 1) { //only with user default betting info
                    //random of 3, 4, or 5
                    random_device rd; //random seed
                    mt19937 gen(rd()); 
                    uniform_int_distribution<int> dis(3,5); //inclusive 3~5
                    compBet = dis(gen);
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
    }
    return compBet;
}