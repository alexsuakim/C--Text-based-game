#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

//take input within 10 seconds, or else bet 1 chip only.
int int_userInput (void){
    int user_input;
    cout << "How many more chips would you like to bet? ";
    cin >> user_input;
    return user_input;
}


//이 함수도 컴퓨터 알고리즘 아직 없어서 일단 결과 보려고 인풋받는걸로 해놨는데 나중에 수정해야됨. 칩 갯수 int로 받는 함수.
int int_compInput (void){
    int comp_input;
    cout << "How many chips would computer like to bet? ";
    cin >> comp_input;
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
    cout << endl << "this round is round " << round+1 << endl;
    //print useful information (computer's card, user & computer's remaining number of chips).
    cout << "let's reveal the cards. You can only see the card of the computer." << endl;
    cout << setw(21) << "computer's card is:  " << compDeck[round] << endl;
    cout << setw(21) << "user:  " << userChip << " chip(s) left." << endl;
    cout << setw(21) << "computer:  " << compChip << " chip(s) left." << endl << endl;

    //the minimum bet for each round is 1 chip.
    //userChip and compChip are not 0 
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
        //if betfirst == user then it is an even number.
        if (userFirst == true){
            //ask if the user wants to give up or bet.
            //if give up, reveal user's bet. Then the computer wins user's and computer's total bet and the round ends.
            //if bet,
            int_input = int_userInput();
            if (int_input > userChip) { //to set the max boundary of the int_input 
                int_input = userChip;
            }
            userChip -= int_input;
            userBetTotal += int_input;
        }
        
        else{ //computer turn 
            //ask if computer wants to give up or bet.
            int_input = int_compInput();
            if (int_input > compChip) { //to set the max boudary of the int_input
                int_input = compChip;
            }
            compChip -= int_input;
            compBetTotal += int_input;
        }
        cout << "your total bet: " << userBetTotal << endl;
        cout << "computer's total bet: " << compBetTotal << endl << endl;
        int betTotal = userBetTotal + compBetTotal + prevBetTotal;
        if (int_input == 0) {
            if (userFirst == true) { //computer wins
                userWin = false;
                compChip = compChip + betTotal;
                prevBetTotal = 0;
                cout << "computer win!" << endl;
                cout << "computer is taking " << betTotal << endl;
                cout << "your card was " << userDeck[round] << endl;
                break;
            } else { //user wins
                userWin = true;
                userChip = userChip + betTotal;
                prevBetTotal = 0;
                cout << "you win!" << endl;
                cout << "you are taking " << betTotal << endl;
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
                cout << "you are taking " << betTotal << endl;
                cout << "your card was " << userDeck[round] << endl;
                break;
            } else if (userDeck[round] < compDeck[round]) { //computer wins
                userWin = false;
                compChip = compChip + betTotal;
                prevBetTotal = 0;
                cout << "computer win!" << endl;
                cout << "computer is taking " << betTotal << endl;
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
    int user = rand() % 10 + 1;
    int comp = rand() % 10 + 1;
    //generate random cards until the user's card and the computer's card are different.
    while (user == comp){
        int user = rand() % 10 + 1;
        int comp = rand() % 10 + 1;
    }
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

    //round continues until all 20 cards are used, or until a player looses all chips.
    for (int round = 0; round < 10; round++){
        if (userChip != 0 && compChip != 0){
            roundGame(round, userWin, userDeck, compDeck, userChip, compChip);
        } else {
            break;
        }
    }
    cout << endl << "game over" << endl;
    cout << "the number of your chip is " << userChip << endl;
    cout << "the number of the computer's chip is " << compChip << endl;

    return 0;
}