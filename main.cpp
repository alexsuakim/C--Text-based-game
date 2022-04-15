#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

//take input within 10 seconds.
//input (g/s/h). g = give up. s = bet the same amount. h = bet higher.
char userInput (){

}


//computer algorithm on betting.
void compInput (){

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

void roundGame(int round, int userDeck[], int compDeck[], int & userChip, int & compChip){
    
    //print useful information (computer's card, user & computer's remaining number of chips).
    cout << setw(21) << "computer's card is:  " << compDeck[round] << endl;
    cout << setw(21) << "user:  " << userChip << " chip(s) left." << endl;
    cout << setw(21) << "computer:  " << compChip << " chip(s) left." << endl;
    
    //take input from the user.
    //char user_input = userInput();
    char user_input;
    cin >> user_input;
    
    /*if (user_input == 'g'){
        cout <<    
    }*/
    
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
        cout << "You can bet first." << endl;
    }
    else{
        cout << "The computer bets first." << endl;
    }
    
    //round continues until all 20 cards are used, or until a player looses all chips.
    for (int round = 0; round < 10; round++){
        if (userChip != 0 && compChip != 0){
            roundGame(round, userDeck, compDeck, userChip, compChip);
        }
    }
    return 0;


}
