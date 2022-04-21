#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>
#include "algorithm.h"

using namespace std;

//take input within 10 seconds, or else bet 1 chip only.
int int_userInput (int userChip, int compChip){
    int user_input;
    cout << "How many more chips would you like to bet? ";
    cin >> user_input;
    
    //restrict maximum chip input to both userChip and compChip. Can't bet more than a player's all in.
    while (user_input > userChip || user_input > compChip){
        cout << "How many more chips would you like to bet? ";
        cin >> user_input;
    }
    return user_input;
}

//computer algorithm to be implemented
int int_compInput (int userCard, int userBetTotal, int compBetTotal){
    int comp_input;
    cout << "Computer has bet";
    comp_input = algorithm (userCard, userBetTotal, compBetTotal);
    return comp_input;
}

//generate cards in Deck
void generateDeck(int deck[])
{
    //fill in the 10 cards in the deck in order.
    for (int i = 0; i < 10; i++){
        deck[i] = i + 1;
    }

    //shuffle the cards in deck.
    for (int i = 0; i < 9; i++)
    {
        //create random index j to swap with i.
        int j = rand() % 10;

        //swap the two cards in deck.
        int temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

void roundGame(int round, bool & userWin, int userDeck[], int compDeck[], int & userChip, int & compChip){
    cout << endl << "<this round is round " << round+1 << ">"<< endl;
    //print useful information (computer's card, user & computer's remaining number of chips).
    cout << "let's reveal the cards. You can only see the card of the computer." << endl;
    //tester
    // cout << setw(21) << "user's card is:  " << userDeck[round] << endl;
    //tester
    cout << setw(21) << "computer's card is:  " << compDeck[round] << endl;
    cout << setw(21) << "user:  " << userChip << " chip(s) left." << endl;
    cout << setw(21) << "computer:  " << compChip << " chip(s) left." << endl << endl;

    //the minimum bet for each round is 1 chip.
    //both userChip and compChip are not 0 
    userChip--;
    compChip--;
    int userBetTotal = 1;
    int compBetTotal = 1;
    static int prevBetTotal = 0;
    cout << "each player starts with betting at least one chip." << endl;
    
    //take input from the first player.
    int int_input;
    char char_input;
    bool userFirst = userWin;
    while (1) {
        if (userFirst == true){ //user's turn
            //get the user bet
            int_input = int_userInput(userChip, compChip);
            if (int_input > userChip) { //to set the max boundary of the int_input 
                int_input = userChip;
            }
            userChip -= int_input;
            userBetTotal += int_input;
        }
        
        else{ //computer's turn 
            //get the computer bet
            int_input = int_compInput(userDeck[round], userBetTotal, compBetTotal);
            if (int_input > compChip) { //to set the max boudary of the int_input
                int_input = compChip;
            }
            compChip -= int_input;
            compBetTotal += int_input;
        }
        cout << endl << "your total bet: " << userBetTotal << endl;
        cout << "computer's total bet: " << compBetTotal << endl << endl;
        int betTotal = userBetTotal + compBetTotal + prevBetTotal;
        if (int_input == 0) {
            if (userFirst == true) { //computer wins and user gives up
                userWin = false; //to reset - change the turn to computer
                if (userDeck[round] == 10) { //penalty when user gives up and user's card is 10
                    cout << "there is a penalty of 10 chips" <<endl;
                    if (userChip < 10 ) {
                        betTotal += userChip;
                        userChip = 0;
                    } else {
                        betTotal += 10;
                        userChip -= 10;
                    }
                }
                compChip = compChip + betTotal;
                prevBetTotal = 0;
                cout << "computer win!" << endl;
                cout << "computer is taking " << betTotal << "chip(s)." << endl;
                cout << "your card was " << userDeck[round] << endl;
                break;
            } else { //user wins
                userWin = true;
                if (compDeck[round] == 10) { //penalty when computer gives up and computer's card is 10
                    cout << "there is a penalty of 10 chips" <<endl;
                    if (compChip < 10 ) {
                        betTotal += compChip;
                        compChip = 0;
                    } else {
                        betTotal += 10;
                        compChip -= 10;
                    }
                }
                userChip = userChip + betTotal;
                prevBetTotal = 0;
                cout << "you win!" << endl;
                cout << "you are taking " << betTotal <<"chip(s)."<< endl;
                cout << "your card was " << userDeck[round] << endl;
                break;
            }
        }
        if ((userBetTotal == compBetTotal) || (userChip == 0 || compChip == 0)) {
            if (userDeck[round] > compDeck[round]) { //user wins
                userWin = true;
                userChip = userChip + betTotal;
                prevBetTotal = 0;
                cout << "you win!" << endl;
                cout << "you are taking " << betTotal << "chip(s)."<< endl;
                cout << "your card was " << userDeck[round] << endl;
                break;
            } else if (userDeck[round] < compDeck[round]) { //computer wins
                userWin = false;
                compChip = compChip + betTotal;
                prevBetTotal = 0;
                cout << "computer win!" << endl;
                cout << "computer is taking " << betTotal << "chip(s)." << endl;
                cout << "your card was " << userDeck[round] << endl;
                break;
            } else { //when cards are the same
            //round ends
            // userBetTotal + compBetTotal accumulate to next round
                prevBetTotal = userBetTotal + compBetTotal;
                cout << "your card was " << userDeck[round] << endl;
                cout << "draw! this round betting " << prevBetTotal << " moves to the next round" << endl;
                break;
            }
        }
    
        userFirst = !userFirst; //toggle turn 
    }
}

int main(){

    //print the game's rule for the user.

    //generate random seed using current time.
    srand(time(NULL));

    //both players receive 20 chips each.
    int userChip = 20;
    int compChip = 20;

    //create 2 decks: userDeck and compDeck.
    int userDeck[10];
    int compDeck[10];

    //generate the 10 cards in each deck.
    generateDeck(userDeck);
    generateDeck(compDeck);

    //decide who bets first. The player with the higher random generated card bets first.
    bool userWin;
    cout << "let's decide who bets first. The player with a higher card will get to bet first." << endl;

    int orderDeck[10];
    generateDeck(orderDeck);

    int user = orderDeck[0];
    int comp = orderDeck[1];

    //print the cards and who bets first.
    cout << "Your card is " << user << ". Computer's card is " << comp << "." << endl;
    if (user > comp){
        userWin = true; 
        cout << "You can bet first." << endl<< endl;
    }
    else{
        userWin = false;
        cout << "The computer bets first." << endl<<endl;
    }

    cout << "The card sets are shuffled. Round starts." << endl;
    //round continues until all 20 cards are used, or until a player looses all chips.
    for (int round = 0; round < 10; round++){
        if (userChip != 0 && compChip != 0){
            roundGame(round, userWin, userDeck, compDeck, userChip, compChip);
        } else {
            break;
        }
    }
    
    cout << endl << "<game over>" << endl;
    
    cout << "you have " << userChip << "chip(s) remaining." << endl;
    cout << "the computer has " << compChip << "chip(s) remaining." << endl;
    
    //announce the winner of the game.
    if (userChip > compChip){
        cout << "Congratulations, you won the game!" << endl;
    }
    else{
        cout << "The computer wins the game. Better luck next time!" << endl;
    }
    
    return 0;
}
