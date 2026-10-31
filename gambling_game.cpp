#include <iostream>
#include <cmath>
#include <ctime>
#include <limits>
using namespace std;

void checkValidInteger(int& input, int minInt, int maxInt, string outputMSG){
    while (!(cin >> input) or (input < minInt) or (input > maxInt)) {
        cout << outputMSG;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return;
}

// Sort for neatness
void sort(int &n1, int &n2, int &n3) {
    if (n1 > n2 and n1 > n3) {
        swap(n1,n3);
    }
    else if (n2 > n1 and n2 > n3) {
        swap(n2,n3);
    }
    if (n1 > n2) {
        swap(n2,n1);
    }
}

//Get winning numbers in range and sort 'em
void getWinningNumbers(int &win1, int&win2, int&win3, int max) {
    win1 = int(rand() % max + 1);
    win2 = int(rand() % max + 1);
    win3 = int(rand() % max + 1);
    
    //Try again if we get the same number
    while (win2 == win1) {
        win2 = int(rand() % max + 1);
    }
    
    while (win3 == win1 or win3 == win2) {
        win3 = int(rand() % max + 1);
    }
    
    
    sort(win1, win2, win3);
}

//Check which numbers won
int numberCorrect(int a, int b, int c, int w1, int w2, int w3) {
   int correct = 0;
   if (a == w1 or a == w2 or a == w3) {
       correct += 1;
   }
   if (b == w1 or b == w2 or b == w3) {
       correct += 1;
   }
   if (c == w1 or c == w2 or c == w3) {
       correct += 1;
   }
   return correct;
}

//Calculate how much to pay
int payoff(int numCorrect, int bet) {
    switch (numCorrect) {
        case 0:
            return -bet;
        case 1:
            return floor(bet * 1.5);
        case 2:
            return floor(bet * 4);
        case 3:
            return floor(bet * 100);
    }
    //Prevent error message
    return 0;
}

int getBet(int maxBet) {
    int tempBet = 0;
    cout << "Enter your bet ($1 to $" << maxBet << "): ";
    checkValidInteger(tempBet,1,maxBet,"Invalid bet, try again: ");
    return tempBet;
}

//Get what we're betting on
void getPicks(int &a, int &b, int &c, int max) {
    cout << "Enter your 3 number guesses (1-" << max << "): ";
    while(true) {
        checkValidInteger(a,1,max,"Invalid guess 1, try again: ");
        
        while (true) {
            checkValidInteger(b,1,max,"Invalid guess 2, try again: ");
            if (b == a) {
                cout << "Guess 2 must be unique, try again: ";
            }
            else {
                break;
            }
        }
            
        while (true) {
            checkValidInteger(c,1,max,"Invalid guess 3, try again: ");
            if ((c == a) or (c == b)) {
                cout << "Guess 3 must be unique, try again: ";
            }
            else {
                break;
            }
        }
        
        sort(a, b, c);
        break;
    }
}

int main()
{
    //SETUP VARS
    
    //Random seed
    srand(time(0));
    
    //Money and bet
    int money = 100;
    int bet = 0;
    
    //Guesses
    int guessA; int guessB; int guessC;
    
    //Winning vars
    int maxRandom = 10;
    int winA; int winB; int winC;
    int correctGuesses = 0;
    
    //Win, loss and continue vars
    bool canPlayAgain = true;
    int winThreshold = 1500;
    
    //INITIAL MSG 
    cout << "Your inital cash is " << money << " dollars." << endl;
    
    //GAME LOOP
    do {
        bet = getBet(money);
        
        //GET NUMBERS TO BET ON AND SORT THEM
        getPicks(guessA, guessB, guessC, maxRandom);
        cout << "Your guesses were: " << guessA << ", " << guessB << ", " << guessC << "." << endl;
        
        //GET WINNING NUMBERS AND DISPLAY
        getWinningNumbers(winA,winB,winC,maxRandom);
        cout << "Winning numbers were: " << winA << ", " << winB << ", " << winC << "." << endl;
        
        //CHECK AND PAYOUT
        correctGuesses = numberCorrect(guessA, guessB, guessC, winA, winB, winC);
        if (correctGuesses == 1) {
            cout << correctGuesses << " number was correct." << endl;
        }
        else {
            cout << correctGuesses << " numbers were correct." << endl;
        }
        int payout = payoff(correctGuesses,bet);
        money += payout;
        if (payout > 0) {
             cout << "Payout: $" << payout << ". Current Total: $" << money << endl;
        }
        else {
            cout << "Payout: -$" << bet <<". Current Total: $" << money << endl;
        }
        
        //Spacing
        cout << endl;
        
        //CHECK FOR LOSS OR WIN AND ASK TO PLAY AGAIN
        if (money == 0) {
            cout << "Sorry, you're busted." << endl;
            canPlayAgain = false;
        }
        else if (money > winThreshold) {
            cout << "You broke the bank!" << endl;
            canPlayAgain = false;
        }
        else {
            cout << "Play again? (y/n): ";
            char playAgain;
            cin >> playAgain;
            if (playAgain == 'y' or playAgain == 'Y') {
                canPlayAgain = true;
            }
            else {
                canPlayAgain = false;
            }
        }
    } while(canPlayAgain);
    
    return 0;
}