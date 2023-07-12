#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib> // Para la función rand()


using namespace std;


const int ROWS = 3;
const int COLUMNS = 3;
const int MAX_PLAYERS = 10;
string playerInfo[MAX_PLAYERS][3]; // Variable global para almacenar información de los jugadores
int playerCount = 0; // Variable global para contar los jugadores registrados



// Function to reset the game board
void resetBoard(char board[][COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int column = 0; column < COLUMNS; column++)
        {
            board[row][column] = ' ';
        }
    }
}



int buscarJugador(const string playerInfo[][3], int playerCount, const string& cedula)
{
    for (int i = 0; i < playerCount; i++)
    {
        if (playerInfo[i][0] == cedula)
        {
            return i; // Jugador encontrado, retornar el índice
        }
    }
    return -1; // Jugador no encontrado
}

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

void playTicTacToeAgainstPC(string player, string symbol, string playerInfo[][3], int& playerCount)
{
    char board[ROWS][COLUMNS] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = 'X';

    int row, column;
    bool playerWins = false;

    while (true)
    {
        // Display the current board
        cout << "Game board:" << endl;
        displayBoard(board);
        cout << endl;

        // Ask the player to enter a position
        if (currentPlayer == 'X')
        {
            cout << "Player " << currentPlayer << "'s turn" << endl;
            cout << "Enter the row (0-" << ROWS - 1 << "): ";
            cin >> row;
            cout << "Enter the column (0-" << COLUMNS - 1 << "): ";
            cin >> column;
        }
        else
        {
            cout << "Computer's turn" << endl;
            // Generate random positions for the computer
            row = rand() % ROWS;
            column = rand() % COLUMNS;
        }

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
            if (currentPlayer == 'X')
            {
                playerWins = true;
            }
            cout << "Player " << currentPlayer << " has won!" << endl;
            cout << "Congratulations, player " << player << " has won the game!" << endl;

            // Increment the player's wins if they win against the computer
            int jugadorIndex = buscarJugador(playerInfo, playerCount, player);
            if (jugadorIndex != -1)
            {
                int wins = std::stoi(playerInfo[jugadorIndex][2]);
                wins++;
                playerInfo[jugadorIndex][2] = std::to_string(wins);
            }

            break;
        }

        // Check for a tie
        bool isTie = true;
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                if (board[r][c] == ' ')
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

    // Ask if the player wants to return to the main menu
    char choice;
    cout << "Press S if you want to return to the main menu (S/N): ";
    cin >> choice;

    if (toupper(choice) == 'S')
    {
        // Reset the board and return to the main menu
        resetBoard(board);
        currentPlayer = 'X';
    }
    else
    {
        // Exit the program
        cout << "Thank you for playing!" << endl;
        exit(0);
    }
}


void registrarJugadores(string playerInfo[][3], int& playerCount)
{
    if (playerCount >= MAX_PLAYERS)
    {
        cout << "Maximum number of players reached." << endl;
        return;
    }

    string cedula;
    bool cedulaValida = false;

    while (!cedulaValida)
    {
        cout << "Enter the ID number (9 digits) of Player " << playerCount + 1 << ": ";
        cin >> cedula;

        // Validar la longitud de la cédula
        if (cedula.length() != 9)
        {
            cout << "Invalid ID number. Please enter a 9-digit number without dashes." << endl;
            continue;
        }

        // Validar si la cédula contiene guiones
        if (cedula.find('-') != string::npos)
        {
            cout << "Invalid ID number. Please enter a 9-digit number without dashes." << endl;
            continue;
        }

        // Validar si la cédula contiene caracteres no numéricos
        bool caracteresValidos = true;
        for (int i = 0; i < cedula.length(); i++)
        {
            if (!isdigit(cedula[i]))
            {
                caracteresValidos = false;
                break;
            }
        }

        if (!caracteresValidos)
        {
            cout << "Invalid ID number. Please enter a 9-digit number without dashes." << endl;
            continue;
        }

        cedulaValida = true;
    }

    cout << "Enter the name of Player " << playerCount + 1 << ": ";
    string nombre;
    cin >> nombre;

    playerInfo[playerCount][0] = cedula;
    playerInfo[playerCount][1] = nombre;
    playerInfo[playerCount][2] = "0"; // Inicializar la cantidad de partidas ganadas en 0

    playerCount++;
    cout << endl;
}





// Function to play a game of Tic Tac Toe between two players
void playTicTacToe(string player1, string player2, string symbol1, string symbol2)
{
    char board[ROWS][COLUMNS] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = symbol1[0];
    int row, column;

    while (true)
    {
        // Display the current board
        cout << "Game board:" << endl;
        displayBoard(board);
        cout << endl;

        // Ask the player to enter a position
        cout << "Turno del jugador " << currentPlayer << endl;
        cout << "Indique la fila y columna donde jugará: ";
        cin >> row >> column;

        // Validate the entered position
        if (row < 0 || row >= ROWS || column < 0 || column >= COLUMNS || board[row][column] != ' ')
        {
            cout << "Posición inválida. Por favor, intente nuevamente." << endl;
            continue;
        }

        // Update the board with the player's move
        board[row][column] = currentPlayer;

        // Check if the player has won
        if (isWinner(board, currentPlayer))
        {
            cout << "Player " << currentPlayer << " has won!" << endl;
            // Obtener la cédula del jugador ganador
            string cedulaGanador;
            if (currentPlayer == symbol1[0])
            {
                cedulaGanador = player1;
            }
            else if (currentPlayer == symbol2[0])
            {
                cedulaGanador = player2;
            }
            cout << "Felicidades jugador " << cedulaGanador << " ha ganado la partida!" << endl;

            // Solicitar si desea regresar al menú principal
            char regresar;
            cout << "Presione S si desea regresar al menú principal (S/N): ";
            cin >> regresar;
            if (toupper(regresar) == 'S')
            {
                exit(0); // Salir del bucle y regresar al menú principal
            }
            else if (toupper(regresar) == 'N')
            {
                cout << "Gracias por jugar" << endl;
                exit(0); // Finalizar el programa
            }
            else
            {
                cout << "Opción no válida. El programa se cerrará por seguridad." << endl;
                exit(0); // Finalizar el programa
            }
        }

        // Check for a tie
        bool isTie = true;
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                if (board[r][c] == ' ')
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
            cout << "¡Empate!" << endl;

            // Solicitar si desea regresar al menú principal
            char regresar;
            cout << "Presione S si desea regresar al menú principal (S/N): ";
            cin >> regresar;
            if (toupper(regresar) == 'S')
            {
                break; // Salir del bucle y regresar al menú principal
            }
            else if (toupper(regresar) == 'N')
            {
                cout << "Gracias por jugar" << endl;
                exit(0); // Finalizar el programa
            }
            else
            {
                cout << "Opción no válida. El programa se cerrará por seguridad." << endl;
                exit(0); // Finalizar el programa
            }
        }

        // Switch to the next player
        currentPlayer = (currentPlayer == symbol1[0]) ? symbol2[0] : symbol1[0];
    }
}


// Function to display the players' results
void displayResults(string playerInfo[][3], int playerCount)
{
    cout << "Resultados tic tac toe" << endl;
    cout << "Cédula\t\tNombre\t\tCantidad de partidas ganadas" << endl;

    for (int i = 0; i < playerCount; i++)
    {
        cout << playerInfo[i][0] << "\t" << playerInfo[i][1] << "\t\t" << playerInfo[i][2] << endl;
    }

    cout << "Desea regresar al menú principal (S/N): ";
    char choice;
    cin >> choice;

    if (toupper(choice) == 'S')
    {
        // Reiniciar el tablero y el contador de jugadores
        // resetBoard(board);
        playerCount = 0;
    }

    else if (toupper(choice) == 'N')
    {
        cout << "Gracias por jugar" << endl;
        exit(0); // Finalizar el programa
    }
    else
    {
        cout << "Opción no válida. El programa se cerrará por seguridad." << endl;
        exit(0); // Finalizar el programa
    }

    cout << endl;
}


int main()
{
    string playerInfo[MAX_PLAYERS][3]; // Matriz para almacenar información de los jugadores
    int playerCount = 0; // Contador de jugadores registrados
    int player1Wins = 0;
    int player2Wins = 0;

    while (true)
    {
        cout << "Options:" << endl;
        cout << "1. Registrar jugadores" << endl;
        cout << "2. Play a game" << endl;
        cout << "3. View results" << endl;
        cout << "5. Vs.Pc" << endl;
        cout << "4. Quit" << endl;

        cout << "Select an option (1-4): ";
        int option;
        cin >> option;
        cout << endl;

        if (option == 1)
        {
            registrarJugadores(playerInfo, playerCount);
            cout << endl;
        }
        else if (option == 2)
        {
            if (playerCount < 2)
            {
                cout << "Insufficient number of players. Please register at least two players." << endl;
                cout << endl;
                continue;
            }

            // Obtener los números de cédula de los jugadores
            string cedula1, cedula2;
            cout << "Enter the ID number of Player 1: ";
            cin >> cedula1;
            cout << "Enter the ID number of Player 2: ";
            cin >> cedula2;
            cout << endl;

            // Buscar a los jugadores por su número de cédula
            int jugador1Index = buscarJugador(playerInfo, playerCount, cedula1);
            int jugador2Index = buscarJugador(playerInfo, playerCount, cedula2);

            // Validar si los jugadores existen
            if (jugador1Index == -1 || jugador2Index == -1)
            {
                cout << "One or both players are not registered." << endl;
                cout << endl;
                continue; // Volver al menú principal
            }

            // Asignar los símbolos a los jugadores
            string jugador1Simbolo = "X";
            string jugador2Simbolo = "O";


            // Obtener los nombres de los jugadores
            string jugador1Nombre = playerInfo[jugador1Index][1];
            string jugador2Nombre = playerInfo[jugador2Index][1];

            // Jugar a Tic Tac Toe con los jugadores y símbolos correspondientes
            playTicTacToe(cedula1, cedula2, jugador1Simbolo, jugador2Simbolo);

            cout << endl;

            // Incrementar el contador de victorias del jugador ganador
            int winningPlayer = 1; // Se asume que el jugador 1 ganó

            // Incrementar el contador de victorias del jugador ganador
            int wins = std::stoi(playerInfo[jugador1Index][2]);
            wins++;
            playerInfo[jugador1Index][2] = std::to_string(wins);

            cout << endl;
        }



        else if (option == 3)
        {
            displayResults(playerInfo, playerCount);
            cout << endl;
        }


        else if (option == 4)
        {
            break;
        }
        else if (option == 5)
        {
            if (playerCount < 1)
            {
                cout << "Insufficient number of players. Please register at least one player." << endl;
                cout << endl;
                continue;
            }

            // Obtener el número de cédula del jugador
            string cedula;
            cout << "Enter the ID number of Player: ";
            cin >> cedula;
            cout << endl;

            // Buscar al jugador por su número de cédula
            int jugadorIndex = buscarJugador(playerInfo, playerCount, cedula);

            // Validar si el jugador existe
            if (jugadorIndex == -1)
            {
                cout << "Player is not registered." << endl;
                cout << endl;
                continue; // Volver al menú principal
            }

            // Asignar el símbolo al jugador
            string jugadorSimbolo = "X";

            // Jugar a Tic Tac Toe contra la computadora con el jugador y el símbolo correspondientes
            playTicTacToeAgainstPC(playerInfo[jugadorIndex][0], playerInfo[jugadorIndex][1], playerInfo, playerCount);


            cout << endl;
        }
    }

    return 0;
}

