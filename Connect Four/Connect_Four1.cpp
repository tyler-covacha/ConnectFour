/******************************************************************************

Connect Four

*******************************************************************************/
#include <iostream>

using namespace std;
//Winner Function
class ConnectFour {
    private:
        bool winner;
    public:
        int xcounter, ocounter;
        int Player1, Player2;  
        string row[6][7] = { {"-","-","-","-","-","-","-"}, //6 rows, bottom to top. each row has 7 spots
                         {"-","-","-","-","-","-","-"},
                         {"-","-","-","-","-","-","-"},
                         {"-","-","-","-","-","-","-"},
                         {"-","-","-","-","-","-","-"},
                         {"-","-","-","-","-","-","-"} };
                     
        string col[7][6] = { {"-","-","-","-","-","-"}, //7 columns, left to right. each column has 6 spots
                         {"-","-","-","-","-","-"},
                         {"-","-","-","-","-","-"},
                         {"-","-","-","-","-","-"},
                         {"-","-","-","-","-","-"},
                         {"-","-","-","-","-","-"},
                         {"-","-","-","-","-","-"} };

        void player1Choice() {
            bool full = false;
            cin >> Player1; //player 1 chooses which column to place their chip in
            Player1 = Player1 - 1; //index

            //if column is full, tells player to choose another column
            while (full == false) {
                if (col[Player1][5] != "-") {
                    cout << "\nColumn is full. Choose another column\n";
                    printBoard();
                    cin >> Player1; //player 1 chooses which column to place their chip in
                    Player1 = Player1 - 1; //index
                    }
                else if (col[Player1][5] == "-") {
                    full = true;
                }
            }

            cout << "\n";
            bool temp = false;
            while (temp == false) { //if a chip is already placed in column, places a chip above that chip
                for (int c = 0; c < 6; c++) {
                    if (col[Player1][c] == "-") {
                        temp = true;
                        full = true;
                        col[Player1][c] = "X"; //places X in col[]
                        row[c][Player1] = "X"; //places X in row[]
                        rowWinner(); //row winner check function
                        colWinner(); //column winner chekc function
                        diagWinner(); //diagonal winner check function
                        break;            
                    }
                }
            }            
        }

        void player2Choice() {
            bool full = false;
            cin >> Player2; //player 2 chooses which column to place their chip in
            Player2 = Player2 - 1;

            //if column is full, tells player to choose another column
            while (full == false) {
                if (col[Player2][5] != "-") {
                    cout << "\nColumn is full. Choose another column\n";
                    printBoard();
                    cin >> Player2; //player 1 chooses which column to place their chip in
                    Player1 = Player2 - 1; //index
                    }
                else if (col[Player2][5] == "-") {
                    full = true;
                }
            }

            cout << "\n";
            bool temp = false;
            while (temp == false) { //if a chip is already placed in column, places a chip above that chip
                for (int c = 0; c < 6; c++) {
                    if (col[Player2][c] == "-") {
                        temp = true;
                        col[Player2][c] = "O"; //places O in col[]
                        row[c][Player2] = "O"; //places O in row[]
                        rowWinner(); //row winner check function
                        colWinner(); //column winner chekc function
                        diagWinner(); //diagonal winner check function
                        break;
                    }
                }
            }     
        }

        void printBoard() { //prints out board
            for (int i = 5; i >= 0; i--) { //row
                for (int e = 0; e < 7; e++) { //column
                    cout << row[i][e] << " "; //disc place
                }
                cout << endl;
            }
            
            cout << "1 2 3 4 5 6 7\n";
        }

        void winnerCounter(string disc) { //checks if there is an X disc, O disc, or empty
            if (disc == "X") { //if X, xcounter++
                xcounter++;
                ocounter = 0;
            }
            else if (disc == "O") { //if O, ocounter++
                ocounter++;
                xcounter = 0;
            }
            else { //if empty, x & o counter = 0
                xcounter = 0;
                ocounter = 0;
            }
            if (xcounter == 4 || ocounter == 4) { //if 4 in a row, winner
                winner = true;
            }

        }

        //Row-Winner-Checker Function
        void rowWinner() {
            for (int r = 5; r >= 0; r--) { //row
                for (int d = 0; d < 7; d++) { //disc place
                    string disc = row[r][d]; 
                    winnerCounter(disc); //checks if there is an x, o, or empty
                    if (winner) {
                        break;
                    }
                }
            xcounter = 0; //moves onto next row, resets x & o counter
            ocounter = 0;
            }
        }

        //Column-Winner-Checker Function
        void colWinner() {
            for (int c = 0; c < 6; c++) { //col
                for (int d = 0; d < 6; d++) { //disc place
                    string disc = col[c][d];
                    winnerCounter(disc); //checks if there is an x, o, or empty
                    if (winner) {
                        break;
                    }
                }
            xcounter = 0; //moves onto next col, resets x & o counter
            ocounter = 0;
            }
        }

        void diagWinner() { //columns 1-4 check for 4 in a row diagonally to the right, 4-7 checks diagonally to the left
            for (int r = 0; r < 3; r++) { //for rows 1-3
                for (int d = 0; d < 4; d++) { //for columns 1-4 -> disc spaces from 1-4
                    string disc = row[r][d];
                    int temp;

                    winnerCounter(disc);

                    while (disc == "X") { //if disc = X
                        temp++;
                        disc = row[r+temp][d+temp]; //disc becomes the space above by 1, right by 1
                        winnerCounter(disc); //adds to x counter
                        if (winner) {
                            break;
                        }
                    }

                    temp = 0;
                    xcounter = 0; //reset counter
                    ocounter = 0;
                    if (winner) {
                        break;
                    }

                    while (disc == "O") { //if disc = O
                        temp++;
                        disc = row[r+temp][d+temp]; //disc becomes the space above by 1, right by 1
                        winnerCounter(disc); //adds to o counter
                        if (winner) {
                            break;
                        }
                    }

                    temp = 0;
                    xcounter = 0; //reset counter
                    ocounter = 0;
                    if (winner) {
                        break;
                    }                    
                }

                for (int d = 3; d < 7; d++) { //for columns 4-7 -> disc spaces from 4-7
                    string disc = row[r][d];
                    int temp;

                    winnerCounter(disc);

                    while (disc == "X") { //if disc = X
                        temp++;
                        disc = row[r+temp][d-temp]; //disc becomes the space above by 1, left by 1
                        winnerCounter(disc); //adds to x counter
                        if (winner) {
                            break;
                        }
                    }

                    xcounter = 0; //reset counters
                    ocounter = 0;
                    temp = 0;
                    if (winner) {
                        break;
                    }

                    while (disc == "O") { //if disc = O
                        temp++;
                        disc = row[r+temp][d-temp]; //disc becomes the space above by 1, left by 1
                        winnerCounter(disc); //adds to o counter
                        if (winner) {
                            break;
                        }
                    }

                    xcounter = 0; //reset counter
                    ocounter = 0;
                    temp = 0; 
                    if (winner) {
                        break;
                    }            
                }

                if (winner) {
                    break;
                }
            xcounter = 0; //reset counter
            ocounter = 0;
            }
        }

        bool getWinner() {
            return winner;
        }
};

int main()
{
    ConnectFour cf;

    cout << "Player 1 will be X, Player 2 will be O\n";
    cout << "Type in the column (1-7, left to right) you want to place you chip in" << endl;
    cf.printBoard();
    while(!cf.getWinner()) { //Replace with while (winner == false) //Keep in main
        cout << "Player 1's Turn \n";
        cf.player1Choice();
        cf.printBoard();
        if(cf.getWinner()) { 
            break;
        }
        cout << "Player 2's Turn \n";
        cf.player2Choice();
        cf.printBoard();
    }
    cout << "Winner!\n";
    return 0;
}