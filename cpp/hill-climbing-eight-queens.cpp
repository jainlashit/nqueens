#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// 2D Array for storing the board config
vector<vector<char> > board(8, vector<char>(8, '-'));
int high;

void print()
{
	cout << high << endl;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
}

// Check vertical threatening for the rows above so that redundant cancellations may not occur 
int check_vertical(int row, int col)
{
	int val = 0;
	for (int i = row + 1; i < 8; i++)
	{
		if(board[i][col] == 'Q')
			val--;
	}
	return val;
}

// Check cross threatening
int check_cross(int row, int col)
{
	int val = 0, inc;
	for (int i = row + 1; i < 8; i++)
	{
		inc = i - row;
		if(col + inc < 8)
		{
			if(board[i][col + inc] == 'Q')
				val--;
		}
		if(col - inc >= 0)
		{
			if(board[i][col - inc] == 'Q')
				val--;
		}	
	}
	return val;
}

// Calculates heuristics value 
int evaluate()
{
	int val = 28; // All the 8C2 combinations, I just want to keep the value positive
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(board[i][j] == 'Q')
			{
				if(i!=7)
				{
					val += check_vertical(i, j);
					val += check_cross(i, j);
				}
				break;
			}
		}
	}
	return val;
}

void copy()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			board[i][j] = board[i][j];
	}
}


void climb()
{
	int val;
	int a = -1, b, c;
	copy();
	high = evaluate();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(board[i][j] == 'Q')
			{
				board[i][j] = '-';
				if(j < 7)
				{
					board[i][j + 1] = 'Q';
					val = evaluate();
					if(val > high)
					{	
						a = i;
						b = j + 1;
						c = j;
						high = val;
					}
					board[i][j + 1] = '-';
				}
				if(j > 0)
				{
					board[i][j - 1] = 'Q';
					val = evaluate();
					if(val > high)
					{
						a = i;
						b = j - 1;
						c = j;
						high = val;
					}
					board[i][j - 1] = '-';	
				}
				board[i][j] = 'Q';
			}
		}
	}
	// If a neighbour with a high value found then proceed
	if(a != -1)
	{
		board[a][b] = 'Q';
		board[a][c] = '-';
		print();
		climb();
	}
}

void layout()
{
	for (int i = 0; i < 8; ++i)
		board[i][rand()%8] = 'Q'; 
}

void set()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = '-';
			board[i][j] = '-';
		}
	}
}


int main()
{
	int count = 0; // Counts how many iteration required to reach the solution
	while(true)
	{
		srand(time(NULL));
		set(); // Resets the whole board with '-' 
		layout();	// Randomly puts 8 queens onto the board
		print();
		climb(); // Performs climbing 
		print(); // Prints the entire board and the final heuristic value
		if(high > 20)
			break;
		count++;
	}
	cout << count << endl;
	return 0;
}
