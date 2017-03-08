void calculate()
{
	int row, col, temp;
	heu = 0;
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
	if((row + col) == (pos1 + board[pos2]))
		val--;
	return val;
}
