#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "tsp1.h"

using namespace std;

struct dane;

void bestalpha(Dane* dane)
{
	double alpha, betha;
	for (int i = 0; i < 20; i++)
	{
		alpha = rand() % 4 + 1;
		betha = rand() % 8 + 1;
		cout << "Alfa i Beta: " << alpha << " " << betha << endl;
		TSP_ACO(dane, 5000, alpha, betha);

		for (int i = 0; i < dane->vnumber; i++)
		{
			for (int j = 0; j < dane->vnumber; j++)
			{
				dane -> pheromone_tab[i][j] = 2;
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	Dane *dane;
	//Otwieramy plik, rozwijamy tablice oraz zapisujemy wierzchołki z pliku
	dane =& wczytaj("plik.txt");
	//Zachlanny
	//TSP(1, dane);
	//cout << "Dystans: " << dane->dist << endl;
	//dane->dist = 0;
	bestalpha(dane);
	//Mroweczki Piotreczka
	//TSP_ACO(dane, 10, 2, 4);
	//show1(dane);
	system("PAUSE");
	return 0;
}

