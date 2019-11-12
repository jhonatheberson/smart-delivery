#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
ofstream grid, completo;

//função responsavel por gerar um grafo completo
//cada arquivo gerado se encontra na pasta completo
void GrafoCompleto(int n)
{
	string name = "../completo/" + to_string(n) + "completo.in";
	completo.open(name);
	completo << n << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			completo << i << " " << j << " " << (rand() % 100) + 1 << endl;
		}
	}
	completo.close();
}

//função responsavel por gerar um grafo Grid
//cada arquivo gerado se encontra na pasta Grid
void GrafoGrid(int n)
{

	string name = "../grid/" + to_string(n) + "grid.in";
	grid.open(name);
	grid << n << endl;

	int meio = n / 2;
	for (int i = 0; i < meio; i++)
	{
		grid << i << " " << i + 1 << " " << (rand() % 100) + 1 << endl;
	}
	for (int i = meio + 1; i < n; i++)
	{
		grid << i << " " << i + 1 << " " << (rand() % 100) + 1 << endl;
	}
	for (int i = 0, meio2 = meio; i < meio; i++, meio2++)
	{
		grid << i + 1 << " " << meio2 << " " << (rand() % 100) + 1 << endl;
	}
	grid.close();
}

int main()
{

	for (int i = 0; i < 5; i++)
	{
		//gera um numero aleatorio entre 1 e 35 que sera o numero de vertices do grafo
		int num = (rand() % 35) + 1;
		//chamada para agreação do grafo completo
		GrafoCompleto(num);
	}

	for (int i = 0; i < 10; i++)
	{
		//gera um numero aleatorio entre 1 e 35 que sera o numero de vertices do grafo
		int num = (rand() % 35) + 1;
		//chamada para agreação do grafo grid
		GrafoGrid(num);
	}
	return 0;
}