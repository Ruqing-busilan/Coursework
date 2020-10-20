#include <iostream>
#include "stdio.h"
#include "iomanip"
#include "string"
#include "algorithm"
#include "Discrete_mathematics.h"

using namespace std;

#define Maxsize 100

int Adj_matrix[Maxsize][Maxsize];

int main() 
{
	int flag;
	Input(Adj_matrix); 
	while(1)
	{ 
	Road_num(Adj_matrix);
		cout<<endl;
	} 
	return 0;
}
