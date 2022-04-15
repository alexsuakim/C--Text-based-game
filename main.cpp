#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

using namespace std;

void userInput (){

}

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

int main(){
    
    //create random seed using time.
    srand(time(NULL));
    
    //create 2 decks: userDeck and compDeck.
    int userDeck[10];
    int compDeck[10];
    
    //generate the 10 cards in each deck.
    generateDeck(userDeck);
    generateDeck(compDeck);


    return 0;


}
