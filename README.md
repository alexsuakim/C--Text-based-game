# project proposal

1. Group Members:
  Soo-ah Kim (3035661061)
  Boyeong Choi (3035662388)
  
2. Game: Indian Poker

3. Rules: 
  There are two players: the user and the computer.
  The user and the computer each gets a separate deck of 10 cards ranging from A to 10, and the players get 20 chips each.
  One card each from the two decks are randomly chosen. The players have to show their card to the other player every round, but cannot see their own card.
  The players will guess if their card is higher or lower than the other player's, and they can choose the number of chips they will bet accordingly.
  The minimum bet is 1 chip. Each player can either bet higher than the other's bet, bet the same amount, or choose to give up.
  If the players bet the same amount, the cards will be open to both players and the winner of the round will win all the chips from the round. If the two cards are eqiuvalent and there is no winner, the chips from that round will be added to the next round's bet.
  If the player bets more than the other's bet, then the round continues, and the other player gets the choice to either bet more, bet the same amount, or give up.
  If the player decides to give up, then the player loses all the previous bets, regardless of the result of the cards(except for when the player's card turns out to be 10). If there were no previous bets, then the player will lose 1 chip. If the players' card turns out to be 10, then the player loses 10 chips.
  The rounds continue until one of the players have no chips left.
  
  
 4. List of features 
  - Random generator of one card from each player’s deck (from 1 ~ 10)
       (1) generation of numbers from 1 to 10 and randomly shuffle their order in an array 
  - Storing cards used into an array 
       (2) use an array to keep track of the cards randomly generated in previous rounds
  - Store the user and computer's arrays of random generated cards of each round in the heap
  - ask the user to choose level to decide the number of cards in a deck)-----> decide the array size during runtime (dynamic programming using *) ----> easy, norml, hard mode. As the level of difficulty increases, the number of cards in a deck increases.
       (3) dynamic memory management
  - Saving the user's play record (to accumulate the number of win / lose rounds)
       (4) file intput to call previous txt file
       (4) file output to update the txt file after the user's rounds
  - Computer betting algorithm about how to deal with the user’s cards and betting choices
       (4) implement the computer algorithm file into the main file
  - The <main function file> calls the <computer betting algorithm function file> 
       (5) program codes in multiple files
  - Header file, Makefile for automating compiling process
       (5) program codes in multiple files
  
 
  
