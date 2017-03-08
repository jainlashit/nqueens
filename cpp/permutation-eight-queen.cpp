#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <bitset>

using namespace std;

vector<bitset<8> > position(8);
vector<int> board(8);

void generate()
{
	for (int i = 0; i < 8; i++)
		position[i] = pow(2, i);
}

bool check(int index, int pos)
{
	int diff;
	for (int i = 0; i < index; i++)
	{
		diff = index - i;
		if(board[i] + diff == pos)
			return false;
		else if(board[i] - diff == pos)
			return false;
		else if(board[i] == pos)
			return false; 
	}
	return true;
}

bool place(int index)
{
	for (int pos = 0; pos < 8; pos++)
	{
		if(check(index, pos))
		{
			board[index] = pos;
			if(index == 7)
				return true;
			if(place(index + 1))
				return true;
		}
	}
	return false;
}

void print()
{
	for (int i = 0; i < 8; i++)
		cout << position[board[i]] << endl;
}

int main()
{
	generate();
	place(0);
	print();
	return 0;
}