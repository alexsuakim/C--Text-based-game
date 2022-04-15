#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

//take input within 10 seconds, or else give up.
//input (g/s/h). g = give up. s = bet the same amount. h = bet higher.
//보영아 이 함수 수정해주세여! 얘는 g/s/h char로 받는함수
char char_userInput (void){
    char user_input;
    cout << "It is your turn to bet. (g = give up, s = bet same amount, h = bet higher) : ";
    cin >> user_input;
    return user_input;
}

//  보영아 이것도 수정해주세요! 얘는 칩 몇개인지 int로 받는 함수
//take input within 10 seconds, or else bet 1 chip only.
int int_userInput (void){
    int user_input;
    cout << "How many chips would you like to bet? ";
    cin >> user_input;
    return user_input;
}


//computer algorithm on betting.
//이 함수도 컴퓨터 알고리즘 아직 없어서 일단 결과 보려고 인풋받는걸로 해놨는데 나중에 수정해야됨. (g/s/h) char로 받는 함수.
char char_compInput (void){
    char comp_input;
    cout << "It is the computer's turn to bet. (g = give up, s = bet same amount, h = bet higher) : ";
    cin >> comp_input;
    return comp_input;
}

//이 함수도 컴퓨터 알고리즘 아직 없어서 일단 결과 보려고 인풋받는걸로 해놨는데 나중에 수정해야됨. 칩 갯수 int로 받는 함수.
int int_compInput (void){
    int user_input;
    cout << "How many chips would you like to bet? ";
    cin >> user_input;
    return user_input;
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

void roundGame(int round, char betFirst, int userDeck[], int compDeck[], int & userChip, int & compChip){

    //print useful information (computer's card, user & computer's remaining number of chips).
    cout << "let's reveal the cards. You can only see the card of the computer." << endl;
    cout << setw(21) << "computer's card is:  " << compDeck[round] << endl;
    cout << setw(21) << "user:  " << userChip << " chip(s) left." << endl;
    cout << setw(21) << "computer:  " << compChip << " chip(s) left." << endl << endl;

    //the minimum bet for each round is 1 chip.
    userChip--;
    compChip--;
    int userBetTotal = 1;
    int compBetTotal = 1;
    
    //take input from the first player.
    int int_input;
    char char_input;
    
    //if betfirst == user then it is an even number.
    if (betFirst % 2 == 0){
        //ask if the user wants to give up or bet.
        //if give up, reveal user's bet. Then the computer wins user's and computer's total bet and the round ends.
        //if bet,
        int_input = int_userInput();
        userChip -= input;
        userBetTotal += input;
        betFirst++;
        cout << "the user has bet " << input << " chip(s)." << endl;
        cout << "your total bet: " << userBetTotal << endl;
        cout << "computer's total bet: " << compBetTotal << endl << endl;
    }
    
    //else if betfirst == computer then it is an odd number.
    else{
        //ask if computer wants to give up or bet.
        //ig give up, reveal user's bet. Then the user wins user's and computer's total bet and the round ends.
        //if bet,
        int_input = int_compInput();
        compChip -= input;
        compBetTotal += input;
        betfirst++;
        cout << "the computer has bet " << input << " chip(s)." << endl;
        cout << "your total bet: " << userBetTotal << endl;
        cout << "computer's total bet: " << compBetTotal << endl << endl;
    }
    
    //keep getting input until both players' total bets are equal.
    while (userBetTotal != compBetTotal){
        if (betFirst % 2 == 0){
            char_input = char_userInput();
            if (char_input == 'g'){
                //update betTotal, so that the betTotals of both players are equal and the while loop ends.
                //reveal user's bet.
                //the computer wins user's and computer's  total bet and the round ends.
            }
            else if (char_input == 's'){
                //update betTotal, so that the betTotals of both players are equal and the while loop ends.
                //reveal user's bet.
                //compare the cards of both players and decide the winner.
                //The winner wins user's and computer's  total bet and the round ends.
            }
            else if (char_input == 'h'){
                //call int_userInput function to ask for the number of chips to add on.
                int_input = int_userInput();
                //betFirst ++;
                //update chip and betTotal.
                //continue onto the while loop, because betTotals of both players are not equal.
            }
        }
        else {
            
        }
    }






    //if user inputs h, input how many chips higher than the current amount the user will bet.


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
    int betFirst;
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
        betFirst = 0; //even number if it's the user's turn to bet.
        cout << "You can bet first." << endl<< endl;
    }
    else{
        betFirst = 1; // odd number if it's the computer's turn to bet.
        cout << "The computer bets first." << endl<<endl;
    }

    //round continues until all 20 cards are used, or until a player looses all chips.
    for (int round = 0; round < 10; round++){
        if (userChip != 0 && compChip != 0){
            roundGame(round, betFirst, userDeck, compDeck, userChip, compChip);
        }
    }
    return 0;


}
