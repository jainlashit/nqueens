#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <vector>

// Well it's dependent on us, what's the definition of our neighbours, so this time we define neighbour as configs that can be rached in just one swap

using namespace std;

int N = 70, heu, steps = 0; // N is the board dimension
vector<int> board(N, 0);
double elapsed_secs;

void generate()
{
	for (int i = 0; i < N; i++)
		board[i] = i;
	random_shuffle(board.begin(), board.end());
}

void print()
{
	cout << "The heuristics value is(0 is perfect) : "<<  heu << " and the number of steps taken is " << steps << endl;
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
int evaluate()
{
	int val = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			int inc = j - i;
			if(board[i] == board[j] + inc)
				val--;
			if(board[i] == board[j] - inc)
				val--;
		}
	}
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
	int val, pos1 = -1, pos2;
	heu = evaluate();
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			swap(i, j);
			val = evaluate();
			if(val > heu)
			{
				pos1 = i;
				pos2 = j;
				heu = val;
			}
			swap(i, j);
		}
	}
	if(pos1 >= 0)
	{
		steps++;
		swap(pos1, pos2);
		climb();
	}
	return;
}

int main()
{
	srand(time(NULL));
	int obs = 1;
	double accuracy = 0;
	for (int i = 0; i < obs; ++i)
	{
		generate();
		clock_t begin = clock();
		climb();
	  	clock_t end = clock();
	  	elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	  	if(heu == 0)
	  		accuracy++;
		// print();
	}
	cout << accuracy/obs << endl;
	cout << elapsed_secs/obs << endl;
	return 0;
}
