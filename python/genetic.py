'''
Genetic mutation program to solve N queens
Each initial list is considered as a DNA string.

1 2 3 4 5 6 7 8
2
3
4
5
6
7
8

'''
import random
from operator import itemgetter

def initialize() :
	rows = 4 #number of dnas being considered
	cols = 8 #length of each dna
	gen_list = [[1 + random.randrange(cols) for x in range(cols)] for x in range(rows)] #genetic mutation rows (4 rows with 8 columns each)
	return gen_list

def calculate_fitness(temp_stat) :
	total=0
	scorelist = []
	for index,dna_string in enumerate(temp_stat) :
		score = collision_pairs(dna_string)
		total += score
		scorelist.append((score,dna_string))

	return scorelist
		
def collision_pairs(bstat) :
	'''Counts the number of collision pairs in a given board state'''

	count = 28 # 7+6+5+4+3+2+1 Max number of queen pairs collisions possible
	for index1,one in enumerate(bstat) :
		for index2,two in enumerate(bstat) :
			if index1 < index2 : #Different columns
				if one == two or abs(index1-index2) == abs(one-two) : #same row or along same diagonals
					count -= 1

	return count

def crossover(bstat) :
	''' Exhange elements of dna string 0 and 1 , 2 and 3'''
	bstat[1][1][4] , bstat[0][1][4] = bstat[0][1][4] , bstat[1][1][4]
	bstat[1][1][5] , bstat[0][1][5] = bstat[0][1][5] , bstat[1][1][5]
	bstat[1][1][6] , bstat[0][1][6] = bstat[0][1][6] , bstat[1][1][6]
	bstat[1][1][7] , bstat[0][1][7] = bstat[0][1][7] , bstat[1][1][7]

	bstat[2][1][4] , bstat[3][1][4] = bstat[3][1][4] , bstat[2][1][4]
	bstat[2][1][5] , bstat[3][1][5] = bstat[3][1][5] , bstat[2][1][5]
	bstat[2][1][6] , bstat[3][1][6] = bstat[3][1][6] , bstat[2][1][6]
	bstat[2][1][7] , bstat[3][1][7] = bstat[3][1][7] , bstat[2][1][7]

	return bstat

def mutation() :
	
	return 
	
if __name__ == '__main__' :
	dna_lists = initialize()
	new_list = calculate_fitness(dna_lists)
	new_list = sorted(new_list,reverse=True,key=itemgetter(0)) #sort dna strings descending according to fitness score 
	new_list[3] = new_list[0] #eliminating the worst string
	
	new_list = crossover(new_list)
	mutation()
	
	print new_list
