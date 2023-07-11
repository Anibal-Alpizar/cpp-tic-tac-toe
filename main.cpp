
#include <iostream>
#include <string>

using namespace std;

const int ROWS = 3;
const int COLUMNS = 3;

// Function to display the game board
void displayBoard(char board[][COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int column = 0; column < COLUMNS; column++)
        {
            cout << " " << board[row][column] << " ";
            if (column < COLUMNS - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
        if (row < ROWS - 1)
        {
            cout << "---+---+---" << endl;
        }
    }
}

// Function to check for a winner
bool isWinner(char board[][COLUMNS], char player)
{
// Check rows
    for (int row = 0; row < ROWS; row++)
    {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player)
        {
            return true;
        }
    }

// Check columns
    for (int column = 0; column < COLUMNS; column++)
    {
        if (board[0][column] == player && board[1][column] == player && board[2][column] == player)
        {
            return true;
        }
    }

// Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }

    return false;

}

// Function to play a game of Tic Tac Toe between two players
void playTicTacToe(string player1, string player2)
{
    char board[ROWS][COLUMNS] = {{' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };


    char currentPlayer = 'X';
    int row, column;

    while (true)
    {
        // Display the current board
        cout << "Game board:" << endl;
        displayBoard(board);
        cout << endl;

        // Ask the player to enter a position
        cout << "Player " << currentPlayer << "'s turn" << endl;
        cout << "Enter the row (0-" << ROWS - 1 << "): ";
        cin >> row;
        cout << "Enter the column (0-" << COLUMNS - 1 << "): ";
        cin >> column;

        // Validate the entered position
        if (row < 0 || row >= ROWS || column < 0 || column >= COLUMNS || board[row][column] != ' ')
        {
            cout << "Invalid position. Please try again." << endl;
            continue;
        }

        // Update the board with the player's move
        board[row][column] = currentPlayer;

        // Check if the player has won
        if (isWinner(board, currentPlayer))
        {
            cout << "Player " << currentPlayer << " has won!" << endl;
            break;
        }

        // Check for a tie
        bool isTie = true;
        for (int row = 0; row < ROWS; row++)
        {
            for (int column = 0; column < COLUMNS; column++)
            {
                if (board[row][column] == ' ')
                {
                    isTie = false;
                    break;
                }
            }
            if (!isTie)
            {
                break;
            }
        }
        if (isTie)
        {
            cout << "It's a tie!" << endl;
            break;
        }

        // Switch to the next player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }


}

// Function to display the players' results
void displayResults(int player1Wins, int player2Wins)
{
    cout << "Results:" << endl;
    cout << "Player 1: " << player1Wins << " wins." << endl;
    cout << "Player 2: " << player2Wins << " wins." << endl;
}

int main()
{
    string player1, player2;
    cout << "Enter the name of Player 1: ";
    cin >> player1;
    cout << "Enter the name of Player 2: ";
    cin >> player2;
    cout << endl;



    int player1Wins = 0;
    int player2Wins = 0;

    while (true)
    {
        cout << "Options:" << endl;
        cout << "1. Play a game" << endl;
        cout << "2. View results" << endl;
        cout << "3. Quit" << endl;
        cout << "Select an option (1-3): ";
        int option;
        cin >> option;
        cout << endl;

        if (option == 1)
        {
            playTicTacToe(player1, player2);
            cout << endl;

            // Increase the wins count for the corresponding player
            cout << "Enter the number of the winning player (1 or 2): ";
            int winningPlayer;
            cin >> winningPlayer;
            if (winningPlayer == 1)
            {
                player1Wins++;
            }
            else if (winningPlayer == 2)
            {
                player2Wins++;
            }
            cout << endl;
        }
        else if (option == 2)
        {
            displayResults(player1Wins, player2Wins);
            cout << endl;
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
            cout << endl;
        }
    }

    return 0;
}
