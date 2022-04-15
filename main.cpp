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
    for (int j = 0; j < i - 1; j++){
        if (card == deck[j]){
            card = rand() % 10 + 1;
            check_duplicate(deck[], card);
    }
    return card;
}

void random_generate(deck[]){
    int card;
    srand((unsigned int) time(NULL));
    card = rand() % 10 + 1;
    deck[0] = card;
    for (int i = 1; i < 10; i++){
        card = check_duplicate(deck[], i);
        deck[i] = card;
    }
}

int main(){
    int userDeck[10];
    int compDeck[10];
    random_generate(userDeck);
    random_generate(compDeck);

    cout << "userDeck: " << endl;
    for (int i = 0; i < 10; i++){
        cout << userDeck[i] << endl;
    }

    cout << "compDeck: " << endl;
    for (int i = 0; i < 10; i++){
        cout << compDeck[i] << endl;
    }
    return 0;

  
}
