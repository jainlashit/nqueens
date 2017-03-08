#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <vector>

using namespace std;

int N = 2000, heu = 0, steps = 0; // N is the board dimension
vector<int> board(N, 0);
vector<int> posCross(2*N -1 , 0);
vector<int> negCross(2*N -1 , 0);
double elapsed_secs;

void generate()
{
	for (int i = 0; i < N; i++)
		board[i] = i;
	for (int i = 0; i < (2*N) - 1; i++)
	{
		posCross[i] = 0;
		negCross[i] = 0;
	}
	random_shuffle(board.begin(), board.end());
}

void print()
{
	cout << "The heuristics value is : "<<  heu << " and the number of steps taken is " << steps << endl;
	for (int i = N - 1; i >= 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			if(board[i] == j)
				cout << "Q ";
			else
				cout << "- ";
		}
		cout << endl;
	}
}

void calculate()
{
	int row, col, temp;
	heu = 0;
	for (int i = 0; i < (2*N) - 1; i++)
	{
		posCross[i] = 0;
		negCross[i] = 0;
	}

	for (int i = 0; i < N; i++)
	{
		row = i;
		col = board[i];
		posCross[N + (row - col)]++;
		negCross[row + col]++;
	}
	for (int i = 0; i < (2*N) - 1; i++)
	{
		temp = posCross[i];
		heu -= (temp*(temp-1))/2;
		temp = negCross[i];
		heu -= (temp*(temp-1))/2;
	}
}

void opCalculate(int pos1, int pos2)
{
	int row, col;
	row = pos1;
	col = board[pos1];
	posCross[N + (row - col)]--;
	negCross[row + col]--;
	row = pos2;
	col = board[pos2];
	posCross[N + (row - col)]--;
	negCross[row + col]--;
	row = pos2;
	col = board[pos1];
	posCross[N + (row - col)]++;
	negCross[row + col]++;
	row = pos1;
	col = board[pos2];
	posCross[N + (row - col)]++;
	negCross[row + col]++;
}

int evaluate(int pos1, int pos2, int val)
{
	int row, col;
	row = pos1;
	col = board[pos1];
	val += posCross[N + (row - col)] - 1;
	val += negCross[row + col] - 1;
	row = pos2;
	col = board[pos2];
	val += posCross[N + (row - col)] - 1;
	if((row - col) == (pos1 - board[pos1]))
		val--;
	val += negCross[row + col] - 1;
	if((row + col) == (pos1 + board[pos1]))
		val--;
	// Positions Swapped
	row = pos2;
	col = board[pos1];
	val -= posCross[N + (row - col)];
	val -= negCross[row + col];
	row = pos1;
	col = board[pos2];
	val -= posCross[N + (row - col)];
	if((row - col) == (pos2 - board[pos1]))
		val--;
	val -= negCross[row + col];
	if((row + col) == (pos2 + board[pos1]))
		val--;
	return val;
}


void swap(int pos1, int pos2)
{
	int temp = board[pos1];
	board[pos1] = board[pos2];
	board[pos2] = temp;
}

void climb()
{
	int val, pos1 = -1, pos2, parent;
	parent = heu;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			val = evaluate(i, j, parent);
			if(val > heu)
			{
				pos1 = i;
				pos2 = j;
				heu = val;
			}
		}
	}
	if(pos1 >= 0)
	{
		steps++;
		opCalculate(pos1, pos2);
		swap(pos1, pos2);
		// calculate();
		climb();
	}
}

int main()
{
	srand(time(NULL));
	int obs = 1;
	double accuracy = 0;
	for (int i = 0; i < obs; i++)
	{
		generate();
		clock_t begin = clock();
		calculate();
		climb();
	  	clock_t end = clock();
	  	elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	  	if(heu == 0)
	  		accuracy++;
	}
	cout << fixed;
	cout << accuracy/obs << endl;
	cout << elapsed_secs/obs << endl;
	return 0;
}
