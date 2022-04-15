#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

using namespace std;

void userInput (){
   
}

void compInput (){
  
}

int check_duplicate(deck[], i){
    srand((unsigned int) time(NULL));
    int card = rand() % 10 + 1;
    for (j = 0; j < i - 1; j++){
        if (card == deck[j]){
            card = rand() % 10 + 1;
            check_duplicate(deck[], card);
    }
    return card;
}

int generate_random(deck[]){
    int card;
    srand((unsigned int) time(NULL));
    card = rand() % 10 + 1;
    deck[0] = card;
    for (i = 1; i < 10; i++){
        card = check_duplicate(deck[], i);
        deck[i] = card;
    }
  return card;
}

int main(){
    int userDeck[10];
    int compDeck[10];
    for 

  
}
