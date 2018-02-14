/*
 * TicTacToe.cpp
 * Joe Runser - 9 November 2017
 * 
 * Tic-tac-toe game.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int BOARD_SIZE = 9;

// Function prototypes, the detailed comments are at the declarations.
int getPlayerInput(string playerName);
bool isLegalMove(int location, vector<char> board);
void placeMarkOnBoard(char playerMark, int location, vector<char>& board);
void clearBoard(vector<char>& board);
bool hasThreeInRow(char playerMark, vector<char> board);
bool isTie(vector<char> board);
void displayBoard(vector<char> board);
bool playerTurn(string& name, vector<char>& board, char token, int& wins, int& ties);

int main() {
	const char TOKEN_X = 'X';
	const char TOKEN_O = 'O';

	vector<char> board = vector<char>(BOARD_SIZE);
	clearBoard(board);

	string playerOne = "Player One";
	string playerTwo = "Player Two";

	// playerOne name
	cout << playerOne << ", please state your name: ";
	cin >> playerOne;
	cout << "Your name is " << playerOne << endl << endl;

	// playerTwo name
	cout << playerTwo << ", please state your name: ";
	cin >> playerTwo;
	cout << "Your name is " << playerTwo << endl << endl;

	char endGameInput = 'N';
	int tokenLocation = -1;
	int playerOneWins = 0;
	int playerTwoWins = 0;
	int ties = 0;

	// game loop
	while (true) {
		clearBoard(board);
		displayBoard(board);

		// playerOne is first
		while (true) {
			// playerOne turn
			if (playerTurn(playerOne, board, TOKEN_X, playerOneWins, ties))
				break;

			// playerTwo turn
			if (playerTurn(playerTwo, board, TOKEN_O, playerTwoWins, ties))
				break;
		}

		// Opportunity to end game
		cout << endl;
		cout << playerOne << " wins: " << playerOneWins << endl;
		cout << playerTwo << " wins: " << playerTwoWins << endl;
		cout << "Ties: " << ties << endl << endl;

		cout << "Would you like to play again (Y/N): ";
		cin >> endGameInput;
		if (endGameInput == 'n' || endGameInput == 'N')
			break;

		clearBoard(board);
		displayBoard(board);
		// playerTwo is first
		while (true) {
			// playerTwo turn
			if (playerTurn(playerTwo, board, TOKEN_X, playerTwoWins, ties))
				break;

			// playerOne turn
			if (playerTurn(playerOne, board, TOKEN_O, playerOneWins, ties))
				break;
		}

		// Oportunity to end game
		cout << endl;
		cout << playerOne << " wins: " << playerOneWins << endl;
		cout << playerTwo << " wins: " << playerTwoWins << endl;
		cout << "Ties: " << ties << endl << endl;

		cout << "Would you like to play again (Y/N): ";
		cin >> endGameInput;
		if (endGameInput == 'n' || endGameInput == 'N')
			break;
	}

	// halt the program
	cout << "Press any key to continue...";
	cin.ignore();
	cin.get();

	return 0;
}

/*
 * function: getPlayerInput
 * 
 * playerName: A string representing the name of the player that the input is
 *     being recived from.
 *
 * description: Outputs the players name followed by instructions, if the rules
 *     the intructions define are followed it will then give an error message
 *     and give the rules again. If the rules are followed then the a proper
 *     variance on the user input will be returned.
 *
 * return: An integer that is from 0 to BOARD_SIZE - 1 inclusive.
 */
int getPlayerInput(string playerName) {
	int retVal = -1;

	while (true) {
		cout << playerName << " please place your token (1 to 9 inclusive): ";
		cin >> retVal;

		if (retVal > 0 && retVal <= BOARD_SIZE)
			return --retVal;
		else
			cout << retVal << " is not a valid input." << endl;
	}
}

/*
* function: isLegalMove
*
* location: An integer value that is expected to be a legal input. Valid input
*     can be determined by using the function getPlayerInput.
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
*
* description: It will check if the location has already been used.
*
* return: true if the location has not yet been used and false if otherwise.
*/
bool isLegalMove(int location, vector<char> board) {
	if (board[location] != 'O' && board[location] != 'X')
		return true;

	return false;
}

/*
* function: placeMarkOnBoard
*
* playerMark: A char value that represents the mark that is being used by the
*     player wishing to place the mark.
* location: An integer value that is expected to be a legal input. Legal input
*     can be determined by using the function isLegalMove.
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
*
* description: Places the players mark on the board in the given location.
*/
void placeMarkOnBoard(char playerMark, int location, vector<char>& board) {
	board[location] = playerMark;
}

/*
* function: clearBoard
*
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
*
* description: Sets the board to the default state as show,
*      7 | 8 | 9
*     ---+---+---
*      4 | 5 | 6
*     ---+---+---
*      1 | 2 | 3
*/
void clearBoard(vector<char>& board) {
	for (int i = 0; i < BOARD_SIZE; i++)
		board[i] = i + 49; // 49 is 1 in ASCII
}

/*
* function: hasThreeInRow
*
* playerMark: The mark that is being checked for the win.
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
*
* description: Checks for a win defined by the playerMark.
*
* return: true if there is a vertical, horizontal, or angled win as shown and
*     false if otherwise
*
*     horizontal:   vertical:     angled:
*      X | X | X     X | 8 | 9     X | 8 | 9
*     ---+---+---   ---+---+---   ---+---+---
*      4 | 5 | 6     X | 5 | 6     4 | X | 6
*     ---+---+---   ---+---+---   ---+---+---
*      1 | 2 | 3     X | 2 | 3     1 | 2 | X
*/
bool hasThreeInRow(char playerMark, vector<char> board) {
	// check horizontal
	if (board[6] == playerMark && board[7] == playerMark && board[8] == playerMark) return true;
	if (board[3] == playerMark && board[4] == playerMark && board[5] == playerMark) return true;
	if (board[0] == playerMark && board[1] == playerMark && board[2] == playerMark) return true;
	// check vertical
	if (board[6] == playerMark && board[3] == playerMark && board[0] == playerMark) return true;
	if (board[7] == playerMark && board[4] == playerMark && board[1] == playerMark) return true;
	if (board[2] == playerMark && board[5] == playerMark && board[8] == playerMark) return true;
	// check angles
	if (board[6] == playerMark && board[4] == playerMark && board[2] == playerMark) return true;
	if (board[8] == playerMark && board[4] == playerMark && board[0] == playerMark) return true;
	// not found
	return false;
}

/*
* function: isTie
*
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
*
* description: Checks to see if there is not a win and no possible way to get one.
*
* return: true if each element on the board is used by a token and false if otherwise.
*/
bool isTie(vector<char> board) {
	int tmp = 0;

	// increments tmp for each element that is used
	for (int i = 0; i < BOARD_SIZE; i++)
		if (board[i] == 'O' || board[i] == 'X')
			tmp++;

	// if tmp is the same as BOARD_SIZE, then the board is full
	if (tmp == BOARD_SIZE)
		return true;

	return false;
}

/*
* function: displayBoard
*
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
*
* description: Displays the board in a manner as shown, the default values  
*     would be replaced by tokens if there are any in the board.
*      7 | 8 | 9
*     ---+---+---
*      4 | 5 | 6
*     ---+---+---
*      1 | 2 | 3
*/
void displayBoard(vector<char> board) {
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << "-" <<      "-" << "-+-" <<      "-" << "-+-" <<     "--" << endl;
	cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "-" <<      "-" << "-+-" <<      "-" << "-+-" <<     "--" << endl;
	cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
	cout << endl;
}

/*
* function: clearBoard
*
* name: The string name of the player that is being represented during this turn.
* board: A charecter vector of size BOARD_SIZE that contains the state of the
*     current game.
* token: A char representing the toeken that the player is associated with.
* wins: An integer number of wins by the represented player.
* ties: An integer number of ties that have been recorded.
*
* description: Allows the defined player to place thier determined mark on the
*     board and then checks for wins or ties. If there are wins or ties then
*     the repective score is updated.
*
* return: true if there is a win or a tie, false if otherwise.
*/
bool playerTurn(string& name, vector<char>& board, char token, int& wins, int& ties) {
	int tokenLocation = -1;

	// get the player input until the input is valid and leagal
	do { tokenLocation = getPlayerInput(name); } 
	while (!isLegalMove(tokenLocation, board));
	
	placeMarkOnBoard(token, tokenLocation, board);
	displayBoard(board);

	// check for win
	if (hasThreeInRow(token, board)) {
		cout << name << " wins!" << endl;
		wins++;
		return true;
	}
	// check for tie
	else if (isTie(board)) {
		cout << "The game has ended in a tie." << endl;
		ties++;
		return true;
	}
	return false;
}
