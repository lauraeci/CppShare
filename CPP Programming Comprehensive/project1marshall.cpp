/*
 * proj1code.cpp
 *
 *  Created on: Aug 9, 2010
 *      Author: marshalll
 *
 * Assignment#1 for C++ Programming Comprehensive.
 */
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

/* MAGIC SQUARE - An NxN matrix containing values from 1 to N*N that are
* ordered so that the sum of the rows, columns, and the major diagonals
* are all equal.  There is a particular algorithm for odd integers, and
* this program constructs that matrix, up to 13 rows and columns.  This
* program also adds the sums of the row, columns, and major diagonals.
*/
class MagicSquare {

public:
	enum InputState {
		EXIT, VALID, INVALID
	};
	MagicSquare();
	void ProcessUserInput();
	void PrintMatrix(int diagonal_total);
	void CreateMagicSquare();
	InputState GetInputState(int user_input);
	~MagicSquare();

private:
	/* User defined integer  */
	int input;

	/* NxN Array holding all input*input values.*/
	int **matrix;

	void InitMatrix();
	int PopulateMatrix();
};

MagicSquare::MagicSquare() {
}

MagicSquare::~MagicSquare() {

	for (int row = 0; row <= input; row++) {
		delete [] matrix[row];
	}

	if (matrix) delete [] matrix;
}

/*
* ProcessUserInput
*
* This function processe the user input to see if it is correct to make a magic square.
* If the input is valid, calls CreateMagicSquare to create a magic square.
* Otherwise ask the user for more input or to enter -1 to quit.
*
*/
void MagicSquare::ProcessUserInput() {

    cout << "\nMagic Squares: This program produces an NxN matrix where" << endl;
    cout << "N is some positive odd integer.  The matrix contains the" << endl;
    cout << "values 1 to N*N.  The sum of each row, each column, and " << endl;
    cout << "the two main diagonals are all equal.  Not only does this" << endl;
    cout << "program produces the matrix, it also computes the totals for" << endl;
    cout << "each row, column, and two main diagonals." << endl;

    cout << "\nBecause of display constraints, this program can work with" << endl;
    cout << "values up to 13 only." << endl;

	cout << "Enter a positive, odd integer (-1 to exit program):" << endl;
	bool done = false;
	input = 0;
	while ((!done) && (cin >> input || !cin.eof())) {

		if (cin.good()) {

			InputState state = GetInputState(input);

			if (state == VALID) {
				cout << "You have entered " << input << "." << endl;
				/* Create a Magic Square and show it to the user */
				CreateMagicSquare();
			}

			if (state == EXIT) {
				done = true;
				cout << "You entered -1 to exit.  Exiting now." << endl;
			}

		} else {

			if (!isdigit(input)) {
				cout << "Sorry, you did not enter a number." << endl;
			}
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter a positive, odd integer (-1 to exit program):" << endl;
	}
}

/*
* GetInputState
* Check the input state to see why it is invalid and print a useful
* message to the user.
* @return
*	InputState - the state of the input, invalid, valid, or exit.
*/
MagicSquare::InputState MagicSquare::GetInputState(int user_input) {

	if (user_input == -1) {
		return EXIT;
	}

	if (user_input < 0) {
		cout << "Sorry, the integer should be positive." << endl;
		return INVALID;
	}

	if (user_input > 13) {
		cout << "Sorry, the integer has to be less than 15." << endl;
		return INVALID;
	}

	if (user_input % 2 == 0) {
		cout << "Sorry, the integer has to be odd." << endl;
		return INVALID;
	}

	if ((user_input > 0) && (user_input < 15)) {
		return VALID;
	}

	return INVALID;
}

/* CreateMagicSquare
* Calls everything needed to create a magic square.
*/
void MagicSquare::CreateMagicSquare() {
	InitMatrix();
	PrintMatrix(PopulateMatrix());
}

/* InitMatrix
* Initialzes the matrix for the magic square
* @precondition - valid data for "input" from ProcessUserInput
* @postcondition - matrix is intialized with 0's and size input*input.
*
*/
void MagicSquare::InitMatrix() {
	matrix = new int*[input+1];

	for (int row = 0; row <= input; row++) {
		matrix[row] = new int[input+1];
		for (int col = 0; col <= input; col++){
			matrix[row][col]=0;
		}
	}
}

/*
* PopulateMatrix
* Populates the data inside the matrix.
* @postcondition - matrix is populated with the data for the magic square.
*/
int MagicSquare::PopulateMatrix() {

	int row = 1;
	int col = input / 2 + 1;
	int diagonal_total = 0;

      for (int value = 1; value <= input*input; value++)
      {                                     /* Loop for all values.       */
         if (matrix[row][col] > 0)          /* If some value already      */
         {                                  /*  present, then             */
            row += 2;                       /*  move down 1 row of prev.  */
            if (row > input)                /*  If exceeds side, then     */
               row -= input;                /*   go to other side.        */

            col--;                          /*  move left 1 column.       */
            if (col < 1)                    /*  If exceeds side, then     */
               col = input;                 /*   go to other side.        */
         }

         matrix[row][col] = value;             /* Assign value to location.  */

/*                                                                          */
/*       Add to totals                                                     */
/*                                                                        */
         matrix[0][col] += value;              /* Add to its column total.*/
         matrix[row][0] += value;              /* Add to its row total.   */
         if (row == col)                       /* Add to diagonal total if */
            matrix[0][0] += value;             /*  it falls on the diagonal.*/

         if (row+col == input+1)            /* Add to other diagonal if   */
            diagonal_total += value;             /*  it falls on the line.     */

/*                                                                        */
/*       Determine where new row and col are                              */
/*                                                                        */
         row--;
         if (row < 1)                       /* If row exceeds side then   */
            row = input;                    /*  goto other side.          */
         col++;
         if (col > input)                   /* If col exceeds side then   */
            col = 1;                        /*  goto other side.          */
      }                                     /* End of getting all values. */

	return diagonal_total;
}

/*
* PrintMatrix
* Print the matrix to display the magic square matrix to the user.
*/
void MagicSquare::PrintMatrix(int diagonal_total) {
	/*                                                                        */
	/*    Print out the matrix with its totals                                */
	/*                                                                        */
	cout << endl << "The number you selected was " << input;
	cout << ", and the matrix is:" << endl << endl;

	for (int row = 1; row <= input; row++) {
		/* Create column for diag.total*/
		cout << "     ";
		for (int col = 1; col <= input; col++) {
			cout << matrix[row][col] << " ";
		}
		/* Print total of row.        */
		cout << " = " << matrix[row][0] << endl;
	}

	/*                                                                        */
	/*    Print out the totals for each column, starting with diagonal total. */
	/*                                                                        */
	for (int col = 0; col <= input; col++) {
		/* Print line separating the  */
		cout << "-----"; /*  value matrix and col totals*/
	}

	cout << endl << diagonal_total; /* Print out the diagonal total*/
	cout << " ";
	for (int col = 1; col <= input; col++) {
		cout << matrix[0][col] << " ";
	}
	cout << "  " << matrix[0][0]; /* Print out the other diagonal*/
	cout << endl;

}

int main() {
	MagicSquare* magic_square = new MagicSquare();
	magic_square->ProcessUserInput();
	return 0;
}
