#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>
#include "algorithm.h"

using namespace std;

//to present the record of play 
struct roundLog {
    int userCard;
    int compCard;
    int userChip;
    int compChip;
    string roundWinner;
};

vector <roundLog> roundLogs;

//takes the number of chips to bet from user 
int userInput (int userChip, int compChip, int compBetTotal, int userBetTotal){
    int user_input;
    cout << "How many more chips would you like to bet? ";
    cin >> user_input;
    
    //restrict maximum chip input to both userChip and compChip. Can't bet more than a player's all in.
    while (user_input > userChip || user_input > compChip){
        cout << "The maximum bet cannot exceed a player's all-in amount. Please input again." << endl;
        cout << "How many more chips would you like to bet? ";
        cin >> user_input;
    }

    // restrict the user total bet to be greater than the computer's total bet
    while ((user_input != 0) && ((user_input + userBetTotal) < compBetTotal)) {
        cout << "your total bet should be the same or greater than the computer's total bet" << endl;
        cout << "Please input again." << endl; 
        cout << "How many more chips would you like to bet? ";
        cin >> user_input;
    }

    return user_input;
}

//computer algorithm implemented 
//takes the number of chips to bet from computer
int compInput (int userCard, int userBetTotal, int compBetTotal){
    int comp_input;
    cout << "Computer has bet";
    comp_input = algorithm (userCard, userBetTotal, compBetTotal);
    return comp_input;
}

//generate cards in Deck and randomly shuffle their order
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

//actual play flow for each round
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
    roundLog log;

    while (1) {
        if (userFirst == true){ //user's turn
            //get the user bet
            int_input = userInput(userChip, compChip, compBetTotal, userBetTotal);
            userChip -= int_input;
            userBetTotal += int_input;
        }
        
        else{ //computer's turn 
            //get the computer bet
            int_input = compInput(userDeck[round], userBetTotal, compBetTotal);
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
                log.roundWinner = "computer";
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
                log.roundWinner = "user";
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
                log.roundWinner = "user";
                break;
            } else if (userDeck[round] < compDeck[round]) { //computer wins
                userWin = false;
                compChip = compChip + betTotal;
                prevBetTotal = 0;
                cout << "computer win!" << endl;
                cout << "computer is taking " << betTotal << "chip(s)." << endl;
                cout << "your card was " << userDeck[round] << endl;
                log.roundWinner = "computer";
                break;
            } else { //when cards are the same
            //round ends
            // userBetTotal + compBetTotal accumulate to next round
                prevBetTotal = userBetTotal + compBetTotal;
                cout << "your card was " << userDeck[round] << endl;
                cout << "draw! this round betting " << prevBetTotal << " moves to the next round" << endl;
                log.roundWinner = "none";
                break;
            }
        }
    
        userFirst = !userFirst; //toggle turn 
    }
    //update roundLog
    log.userCard = userDeck[round];
    log.compCard = compDeck[round];
    log.userChip = userChip;
    log.compChip = compChip;
    roundLogs.push_back(log);
}

int main(){

    //print the game's rule for the user.

    //generate random seed using current time.
    //srand(time(NULL));
    
    //generate random seed by taking input.
    int seed;
    cout << "Choose an integer to use as a seed to generate random card decks." << endl;
    cin >> seed;
    srand(seed);

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
    
    string finalWinner;
    //announce the winner of the game.
    if (userChip > compChip){
        cout << "Congratulations, you won the game!" << endl << endl;
        finalWinner = "user";
    }
    else{
        cout << "The computer wins the game. Better luck next time!" << endl << endl;
        finalWinner = "computer";
    }
    
    //print the log
    cout << "play history is...." << endl;
    for (int i = 0; i < roundLogs.size(); i++) {
        cout << "round: " << i+1 << endl;
        cout << "winner: " << roundLogs[i].roundWinner << endl;
        cout << "user card: " << roundLogs[i].userCard << endl;
        cout << "computer card: " << roundLogs[i].compCard << endl;
        cout << "the number of user chips: " << roundLogs[i].userChip << endl;
        cout << "the number of computer chips: " << roundLogs[i].compChip << endl << endl;

    }

    cout << "do you want to save the result? if yes, press 'Y/y'" << endl;
    char saveOption;
    cin >> saveOption;
    if ((saveOption == 'y') || (saveOption == 'Y')) {
        ofstream fout;
        fout.open("gameRecord.txt", ios::app);
        if (fout.fail()) {
            exit(1);
        }
        fout << "Final Winner: " << finalWinner << endl;
        fout << "User Chip: " << userChip << endl;
        fout << "computer Chip: " << compChip << endl;
        fout.close();
        cout << "the result is saved" << endl;
    }

    cout << "do you want to call your playing results? if yes, press 'Y/y'" << endl;
    cin >> saveOption;
    if ((saveOption == 'y') || (saveOption == 'Y')) {
        ifstream fin;
        fin.open("gameRecord.txt");
        if (fin.fail()) {
            exit(1);
        }
        else {
            if (fin.is_open()){
                cout << fin.rdbuf();
            }
        }
        fin.close();
    }
    
    return 0;
}
