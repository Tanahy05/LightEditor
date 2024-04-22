#include <iostream>
using namespace std;
// Define the game board and other necessary variables
int board[6][7];    // 6x7 board
int input, player = 1;  // input from players and current player
int row_index = 5;  // starting row index
bool game_end = false;  // flag to indicate if the game has ended

// Function to display the game board
void sketch() {
    cout << "___________________________________" << endl;
    for (int j = 0; j < 7; j++) {
        cout << "--" << j + 1 << "--"; // Print column numbers
    }
    cout << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 0) {
                cout << "|   |"; // Print empty cell
            } else if (board[i][j] == 1) {
                cout << "| x |"; // Print player 1's piece
            } else if (board[i][j] == 2) {
                cout << "| O |"; // Print player 2's piece
            }
        }
        cout << endl;
    }
    for (int j = 0; j < 7; j++) {
        cout << "====="; // Print bottom border
    }
    cout << endl;
}


// Function to handle player input
void handleInput(int input) {
    if (row_index >= 0) {
        if (board[row_index][input] != 0) {
            row_index -= 1; // If the selected column is full, move up
            handleInput(input); // Call the function recursively until a valid move is made
        } else {
            board[row_index][input] = player; // Place player's piece in the selected column
            row_index = 5; // Reset row index for the next move
        }
    } else {
        cout << "Wrong Input \n"; // If row index is out of bounds, it's a wrong input
        player = player == 1 ? 2 : 1; // Switch player
        row_index = 5; // Reset row index for the next move
    }
}



// Function to check if a player has won
void check_Winner() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            // Check for horizontal, vertical, and diagonal wins
            if (board[i][j] == player && board[i][j - 1] == player && board[i][j - 2] == player && board[i][j - 3] == player) {
                game_end = true; // Set game end flag
                cout << "\nPlayer" << player << " Has Won! \n"; // Print winner
            } else if (board[i][j] == player && board[i - 1][j] == player && board[i - 2][j] == player && board[i - 3][j] == player) {
                game_end = true; // Set game end flag
                cout << "\nPlayer" << player << " Has Won! \n"; // Print winner
            } else if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == player && board[i - 3][j - 3] == player) {
                game_end = true; // Set game end flag
                cout << "\nPlayer" << player << " Has Won! \n"; // Print winner
            } else if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                game_end = true; // Set game end flag
                cout << "\nPlayer" << player << " Has Won! \n"; // Print winner
            }
        }
    }
}


int main() {
    cout << "** Welcome to connect 4 game (only two players can play it). Every player should choose a number between 1 and 7 to put their symbols on the board, and the player who links 4 symbols wins **"<<endl;
    
    sketch(); // Display initial game board
    
    // Main game loop
    while (!game_end) {
        cout << "Player " << player << ": "; 
        cin >> input; // Get input from current player
        while (cin.fail() || input < 1 || input > 7) { // Input validation
            cout << "Please enter a valid number between 1 and 7: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> input;
        }
        handleInput(input - 1); // Handle player's move
        sketch(); // Display updated game board
        check_Winner(); // Check if there is a winner
        player = player == 1 ? 2 : 1; // Switch players
    }
    return 0;
}