#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@       @                     @         @     @             @         @
@ @@@ @ @ @@@@@@@ @@@@@ @@@@@ @ @@@@@@@@@ @ @@@ @ @@@ @@@@@@@ @@@@@ @@@
@   @ @ @ @     @ @   @     @   @         @     @   @ @       @   @   @
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@ @@@@@@@@@@@@@@@ @ @ @ @@@@@@@@@ @@@ @
@ @   @     @   @ @ @       @             @     @ @ @ @   @     @   @ @
@@@ @@@@@@@@@ @@@@@ @@@@@@@@@ @@@@@@@@@@@@@ @@@ @ @ @@@@@ @@@ @ @ @ @ @
@ @       @ @ @     @       @   @   @       @ @ @ @           @   @ @ @
@ @@@@@@@ @ @ @@@ @@@ @@@@@ @@@ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@@@@@ @
@       @ @ @   @         @     @ @   @   @     @     @ @     @   @   @
@@@@@@@ @ @ @@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@ @@@@@ @@@ @@@ @@@ @ @ @ @ @
@         @                       @               @       @     @   @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/


void SolveMaze(int row, int col, char maze[][100], int rowSz, int colSz, bool& foundEnd, string& finaldir, string currDir) {
	if (foundEnd){ // if found the end
		return;
	}
	if (row < 0 || col < 0 || row > rowSz || col > colSz){
		return; // if out of bounds
	}
	if (maze[row][col] == 'F'){
		foundEnd = true;
		finaldir = currDir; // found the end, the current set of directions is the final set of directions
		return; // maze is finished
	}
	if (maze[row][col] == '.'){ // if already visited
		return; // bread crums
	}
	if (maze[row][col] == '@'){
		return; // walls
	}

	maze[row][col] = '.'; // leave bread crums

	SolveMaze(row - 1, col, maze, rowSz, colSz, foundEnd, finaldir, currDir+"U"); // Up
	SolveMaze(row + 1, col, maze, rowSz, colSz, foundEnd, finaldir, currDir+"D"); // Down
	SolveMaze(row, col - 1, maze, rowSz, colSz, foundEnd, finaldir, currDir+"L"); // Left
	SolveMaze(row, col + 1, maze, rowSz, colSz, foundEnd, finaldir, currDir+"R"); // Right

	if (!foundEnd) {
		maze[row][col] = ' ';
	}
}

int main()
{
	ifstream mazeFile("C:/Users/rohan/OneDrive/Desktop/CS-301_Maze/maze.txt"); // absolute path is needed for debugging.
	char maze[100][100]; // make larger than required

	// Initialize the maze
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			maze[i][j] = ' ';
		}

	int row = 0;
	int startRow, startCol;

	// Read the file line by line an initialize the maze
	string line;
	while (getline(mazeFile, line)) {
		cout << line << endl;
		for (int i = 0; i < (int) line.length(); i++) {
			maze[row][i] = line[i];
			if (maze[row][i] == 'S') {
				startRow = row;
				startCol = i;
				maze[row][i] = ' ';
			}
		}
		row++;
	}

	cout << "Start Position: (" << startRow << "," << startCol << ")" << endl;

	// figure out the number of rows and columns
	int rowSz = row;
	int colSz = line.length();
	
	bool foundEnd = false;

	string finaldir = "";
	string currDir = "";
	SolveMaze(startRow, startCol, maze, rowSz, colSz, foundEnd, finaldir, currDir);
	
	cout << "Directions: " << finaldir << endl;

	// Print out the maze with the path shown
	for (int i = 0; i < rowSz; i++) {
		for (int j = 0; j < colSz; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	
    return 0;
}
