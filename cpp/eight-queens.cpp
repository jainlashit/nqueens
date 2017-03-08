#include <iostream>
#include <vector>

using namespace std;

vector< vector<char> > board(8, vector<char>(8, '-'));

bool print(vector< vector<bool> >& stat)
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
			cout << board[row][col] << " ";
		cout << endl;
	}
}

void markStat(int row, int col, vector< vector<bool> >& stat)
{
	stat[row][col] = false;
	for (int i = 0; i < 8; i++)
	{
		// Queen Straight Moves
		stat[row][i] = false;
		stat[i][col] = false;
	}
	for (int i = 0; i < 8; i++)
	{
		// Queen Cross Direction Moves 
		if(row >= i and col >= i) 
			stat[row - i][col -i] = false;
		if(row >= i and col + i < 8)
			stat[row -i][col + i] = false;
		if(row + i < 8 and col >= i)
			stat[row + i][col - i] = false;
		if(row + i < 8 and col + i < 8)
			stat[row + i][col + i] = false;
	}
}

bool place(int row, vector< vector<bool> >& stat)
{
	bool val;
	for (int col = 0; col < 8; col++)
	{
		vector< vector<bool> > temp = stat;
		if(stat[row][col] == true)
		{
			// cout << "Row is " << row << " and column is " << col << endl;
			board[row][col] = 'Q';
			markStat(row, col, temp);
			// print(temp);
			if(row < 7)
			{
				val = place(row + 1, temp);
				if(val)
					return val;
			}
			else
				return true;
			board[row][col] = '-';
		}
	}
	return false;
}

int main()
{
	vector< vector<bool> > stat(8, vector<bool>(8, true));
	place(0, stat);
	print(stat);
	return 0;
}
