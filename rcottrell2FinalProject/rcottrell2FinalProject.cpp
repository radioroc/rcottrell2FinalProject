/*
    Project Name: rcottrell2FinalProject
    Author: Ra'Heem Cottrell
    Date Lst Updated: 12/18/2020
    Purpose: A board game using a randome number generator to roll dice
*/
#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;
// global variable so that they can be used in all functions
int die1;
int die2;
int player1, player2, player3, player4;
int leadI, lastI;
bool playerwon = false;

// updates the values for leadI and lastI if needed
void checkminmax(int i) {
    if (i < lastI)
        lastI = i;
    else if (i > leadI)
        leadI = i;
    
}
//function to roll dice
void rollDice(int index) {
    char temp;
    cin.clear();
    //waits for a key to be pressed 
    cout << "Please press enter to roll the dice for player " << index << endl;
    cin.ignore();
    temp = cin.get();
    // if the user doesnt press enter instructs them to do so again
    while (temp != '\n') {
        cin.clear();
        cout << "Error: Please press enter to continue" << endl;
        cin.ignore();
        temp = cin.get();
        
    }
    // rolls the dice using srand to change the value of rand each time rand() is called
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    die1 = (rand()%6) + 1 ;
    die2 = (rand()%6 )+ 1;
    cout << die1 << ' ' << die2 << endl;


}

// function to print rules to user. keeps main clear
void rules() {
    cout << "Rules!" << endl << string(50, ' ') << endl << "1: In order for a player to start, you must roll a 2 or higher."
        << "\n2: The dice have special conditions:" << endl
        << "2 = Move two spaces\n3 = Move three spaces\n4 = Move back one space.\n5 = Move five spaces."
        << "\n6 = Move six spaces.\n7 = Swap spots with the leading layer / or nothing if player is in lead.\n8 = Move Eight spaces."
        << "\n9 = Move nine spaces.\n10 = Move ten spaces.\n11 = Swap spots with the last player / or do nothing if player is last."
        << "\n12 = Start Over" << endl << "A player must roll a double to start.\nIf a player lands on the same space as another,"
        << "the other player must return to the beginning." << "\nA player must roll an EXACT number to enter the winning space." << endl;
}

// struct for player to hold player number and whether the player has rolled a double after the first roll;
struct player {
    int pnumber;
    bool twice;
    bool tripple;
    

};

// function to carry out the first moves on the board
void firstMove(int rolls, player board[], int pnum) {
    int temppnum = 0;
     checkminmax(rolls);
        if (board[rolls].pnumber != pnum) {
            temppnum = board[rolls].pnumber;
            board[0].pnumber = board[rolls].pnumber;
            board[rolls].pnumber = pnum;
           
            
        }
        else {
            board[rolls].pnumber = pnum;
            
            
        }
        switch (pnum) {
        case 1: {
            player1 = rolls;
            break;
        }
        case 2: {
            player2 = rolls;
            break;
        }
        case 3: {
            player3 = rolls;
            break;
        }
        case 4: {
            player4 = rolls;
            break;
        }
        }
        switch (temppnum) {
        case 1: {
            player1 = 0;
            break;
        }
        case 2: {
            player2 = 0;
            break;
        }
        case 3: {
            player3 = 0;
            break;
        }
        case 4: {
            player4 = 0;
            break;
        }
        default:
            break;
        }

    
}


// function to display the location of the players 
void displayboard(player b[], int pamt) {
    switch (pamt) {
    case 2: {
        cout << "Player 1: " << player1 << "\nPlayer 2: " << player2 << endl;
        break;
    }
    case 3: {
        cout << "Player 1: " << player1 << "\nPlayer 2: " << player2 << "\nPlayer 3: " << player3 <<endl;
        break;
    }
    case 4: {
        cout << "Player 1: " << player1 << "\nPlayer 2: " << player2 << "\nPlayer 3: " << player3 << "\nPlayer 4: " << player4 << endl;
        break;
    }
    }

}

// function that returns a value that determines movement
int moverule(int r, int pnum) {
    switch (r) {
    case 2: 
        return (pnum +r);
    case 3: 
        return (pnum + r);
    case 4: 
        return (pnum - 1);
    case 5:
        return (pnum + r);
    case 6:
        return (pnum + r);
    case 7: 
        return 1;
    case 8:
        return (pnum + r);
    case 9: 
        return (pnum + r);
    case 10: 
        return (pnum + r);
    case 11: 
        return -1;
    case 12:
        return 0;
    default:
        return -2;


    }
    
}

// used to swap on a roll of 7 or 11
void swap(int finalindex) {
    if (player1 == leadI || player1 == lastI)
        player1 = finalindex;
    else if (player2 == leadI || player2 == lastI)
        player2 = finalindex;
    else if (player3 == leadI || player3 == lastI)
        player3 = finalindex;
    else if (player4 == leadI || player4 == lastI)
        player4 = finalindex;
}

// function to play a round of the game.
void playround(int rolls, player board[], int pnum) {
    int temp;
    int tempindex;
    int swapindex;
    // switch structure that changes the value of the corresponding player
    switch (pnum) {
    case 1: {
        
        // checks for exact movement to win
        if ((player1 + rolls) > 49) {
            cout << "you must roll the exact amount to win the game" << endl;
            break;
        }
        else {
            temp = moverule(rolls, player1);

            if (temp == 1) {
                // swap places with lead
                swapindex = player1;
                tempindex = board[leadI].pnumber;
                board[leadI].pnumber = pnum;
                board[player1].pnumber = tempindex;

                player1 = leadI;
                swap(swapindex);
                checkminmax(player1);
                break;


            }
            else if (temp == -1) {
                //swap places with last
                swapindex = player1;
                tempindex = board[lastI].pnumber;
                board[lastI].pnumber = pnum;
                board[player1].pnumber = tempindex;

                player1 = lastI;
                swap(swapindex);
                checkminmax(player1);
                break;

            }
            else if (temp == 0) {
                // starts over if roll is 12
                board[player1].pnumber = 0;
                board[0].pnumber = pnum;
                player1 = 0;
                checkminmax(player1);
                break;
            }
            else if (temp == -2) // will only occur with a logic error. prevents error during run.
                break;
            else {
                // makes changes based off the return value of moverule
                if (board[temp].pnumber != 1) {
                    board[0].pnumber = board[temp].pnumber;
                    board[temp].pnumber = 1;
                    player1 = temp;
                    checkminmax(player1);
                    break;
                }
                break;
            }

            break;

        }
        break;
    }
    case 2: {
        if ((player2 + rolls) > 49) {
            cout << "you must roll the exact amount to win the game" << endl;
            break;
        }
        else {
            temp = moverule(rolls, player2);

            if (temp == 1) {
                // swap places with lead
                swapindex = player2;
                tempindex = board[leadI].pnumber;
                board[leadI].pnumber = pnum;
                board[player2].pnumber = tempindex;

                player2 = leadI;
                swap(swapindex);
                checkminmax(player2);
                break;


            }
            else if (temp == -1) {
                //swap places with last
                swapindex = player2;
                tempindex = board[lastI].pnumber;
                board[lastI].pnumber = pnum;
                board[player2].pnumber = tempindex;

                player2 = lastI;
                swap(swapindex);
                checkminmax(player2);
                break;

            }
            else if (temp == 0) {
                board[player2].pnumber = 0;
                board[0].pnumber = pnum;
                player2 = 0;
                checkminmax(player2);
                break;
            }
            else if (temp == -2)
                break;
            else {
                
                if (board[temp].pnumber != 2) {
                    board[0].pnumber = board[temp].pnumber;
                    board[temp].pnumber = 2;
                    player2 = temp;
                    checkminmax(player2);
                    break;
                }
            }



        }

        break;

    }
    case 3: {
        if ((player3 + rolls) > 49) {
            cout << "you must roll the exact amount to win the game" << endl;
            break;
        }
        else {
            temp = moverule(rolls, player3);

            if (temp == 1) {
                // swap places with lead
                swapindex = player3;
                tempindex = board[leadI].pnumber;
                board[leadI].pnumber = pnum;
                board[player3].pnumber = tempindex;

                player3 = leadI;
                swap(swapindex);
                checkminmax(player3);
                break;

            }
            else if (temp == -1) {
                //swap places with last
                swapindex = player3;
                tempindex = board[lastI].pnumber;
                board[lastI].pnumber = pnum;
                board[player3].pnumber = tempindex;

                player3 = lastI;
                swap(swapindex);
                checkminmax(player3);
                break;

            }
            else if (temp == 0) {
                board[player3].pnumber = 0;
                board[0].pnumber = pnum;
                player3 = 0;
                checkminmax(player3);
                break;
            }
            else if (temp == -2)
                break;
            else {
                
                if (board[temp].pnumber != 3) {
                    board[0].pnumber = board[temp].pnumber;
                    board[temp].pnumber = 3;
                    player3 = temp;
                    checkminmax(player3);
                    break;
                }
            }



        }


    }
    case 4: {
        if ((player4 + rolls) > 49) {
            cout << "you must roll the exact amount to win the game" << endl;
            break;
        }
        else {
            temp = moverule(rolls, player4);

            if (temp == 1) {
                // swap places with lead
                swapindex = player4;
                tempindex = board[leadI].pnumber;
                board[leadI].pnumber = pnum;
                board[player4].pnumber = tempindex;

                player4 = leadI;
                swap(swapindex);
                checkminmax(player4);
                break;


            }
            else if (temp == -1) {
                //swap places with last
                swapindex = player4;
                tempindex = board[lastI].pnumber;
                board[lastI].pnumber = pnum;
                board[player4].pnumber = tempindex;

                player4 = lastI;
                swap(swapindex);
                checkminmax(player4);
                break;

            }
            else if (temp == 0) {
                board[player4].pnumber = 0;
                board[0].pnumber = pnum;
                player4 = 0;
                checkminmax(player4);
                break;
            }
            else if (temp == -2)
                break;
            else {

                if (board[temp].pnumber != 4) {
                    board[0].pnumber = board[temp].pnumber;
                    board[temp].pnumber = 4;
                    player4 = temp;
                    checkminmax(player4);
                    break;
                }
            }



        }


    } break;
    }
}

int main()
{  
    int totalroll, playeramount;

    //declare the board as an array
    player board [50];
    cout << "Lets play the game of sorry" << endl; 
    rules();
    cout << "How many people will be playing the game? There must be 2 to 4 players" << endl;
    cin >> playeramount;
    
    // input validation for player ammount
    while (!(playeramount >= 2 && playeramount <= 4)) {
        cout << "Error: Plese enter a number from 2 to 4" << endl;
        cin.ignore();
        cin >> playeramount;
    }

    // sets up the first round
    cout << "Lets play the first round" << endl;
    for (int i = 1; i <= playeramount; i++) {
        rollDice(i);
        while (die1 != die2) {
            rollDice(i);
        }
        
            totalroll = die1 + die2;
            firstMove(totalroll, board, i);
        
    }
    displayboard(board, playeramount);
    int count = 1;
    while (playerwon == false) {
        count++;
        cout << "roll the dice for round " << count << endl;
        for (int i = 1; i <= playeramount; i++) {
            rollDice(i);
            totalroll = die1 + die2;
            playround(totalroll, board, i);

        }
        totalroll = 0;
        displayboard(board, playeramount);
        if (player1 == 49) {
            playerwon = true;
            cout << "The game is over. Player 1 won!" << endl;
        }
        else if (player2 == 49) {
            playerwon = true;
            cout << "The game is over. Player 2 won!" << endl;
        }
        else if (player3 == 49) {
            playerwon = true;
            cout << "The game is over. Player 3 won!" << endl;
        }
        else if (player4 == 49) {
            playerwon = true;
            cout << "The game is over. Player 3 won!" << endl;
        }
        // if the game drags on, ends it and calls a tie.
        else if (count > 40) {
            playerwon = true;
            cout << "The game went on for too long. Its a Tie!" << endl;
        }
    }




    
    
    
}

