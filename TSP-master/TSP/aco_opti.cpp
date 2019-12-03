#include "tsp1.h"
#include<chrono>
#include <random>
using namespace std;



int Probability_ACO(int v, Dane* dane, double alpha, double betha)
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	int i;
	double numbers, distance, alfa = alpha, beta = betha, licznik, pr[29];
	default_random_engine generator(seed);
	//liczymy mianownik
	/*for (i = 0; i < dane->vnumber; i++)
	{
		if (dane->visited[i] == 0)
		{

			distance = 1 / dane->matrix[v][i];
			mianownik += pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
		}
	}*/

	//liczymy prawdopodobienstwa
	for (i = 0; i < dane->vnumber; i++){

		if (dane->visited[i] == 0)
		{
			//jak ze wzoru
			distance = 1 / dane->matrix[v][i];
			licznik = pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
			pr[i] = licznik;
			//cout << pr[i] << endl;
			//cout << "prawdopodobienstwo: " << probability << endl;
			//cout << "zaokgralone: "<< probability << endl;
			//out <<"numbers: " << numbers << endl;

		}
		else { pr[i] = 0.0; }
	}
	discrete_distribution<int> distribution({ pr[0], pr[1] });
	int zzz = distribution(generator);
	return zzz;
}


void Pheromone_ACO(Dane* dane)
{
	int i, j;
	double reduction = 0.94, pheromone_change = 10000 / dane->dist;
	
	for (i = 0; i < dane->vnumber - 1; i++)
	{
		for (j = i+1; j < dane->vnumber; j++)
		{
			dane->pheromone_tab[i][j] = reduction * dane->pheromone_tab[i][j];
			dane->pheromone_tab[j][i] = reduction * dane->pheromone_tab[j][i];
		}
	}


	for (i = 0; i < dane->vnumber; i++)
	{
		//jak ze wzoru
		if (i < dane->vnumber - 1)
		{
			dane->pheromone_tab[dane->path[i]][dane->path[i + 1]] += pheromone_change;
			dane->pheromone_tab[dane->path[i + 1]][dane->path[i]] += pheromone_change;
			//cout << "dystans: " << dist << endl;
			//cout << "wierzcholek: " << i << endl;
		}
		else
		{

			//tutaj laczymy ostatni z pierwszym ale nie wiem czy to dobrze
			dane->pheromone_tab[dane->path[i]][dane->path[0]] +=  pheromone_change;
			dane->pheromone_tab[dane->path[0]][dane->path[i]] +=  pheromone_change;
			//cout << "dystans: " << dane->dist << endl;
		}
	}
}

void find_path_ACO(int v, int counter, Dane* dane, double alpha, double betha)
{
	int next;
	//cout << "Wierzcholek: "<< v << endl;
	dane->visited[v] = 1;
	dane->path[counter++] = v;

	//next = (funkcja na wybor nastepnego wierzcholka - prawdopodobienstwo)
	next = Probability_ACO(v, dane, alpha, betha);



	if (counter < dane->vnumber)
	{
		dane->dist += dane->matrix[v][next];
		find_path_ACO(next, counter, dane, alpha, betha);
	}
	else
		return;
}


void show1(Dane* dane)
{
	int i, j;
	for (i = 0; i < dane->vnumber; i++)
	{
		for (j = 0; j < dane->vnumber; j++)
		{
			cout << dane->pheromone_tab[i][j] << " ";
		}
		cout << endl;
	}
}

void TSP_ACO(Dane* dane, int ile, double alpha, double betha)
{
	int j, i, v, * minitab = new int[dane->vnumber];
	double mini = 999999999;
	

	//robimy to dla kilku mrowek, stad petla
	for (j = 0; j <ile; j++)
	{
		//zerowanie odwiedzonych
		for (i = 0; i < dane->vnumber; i++)
			dane->visited[i] = 0;

		//v = rand() % (dane->vnumber) ;
		v = 0;
		//cout << v << endl;
		find_path_ACO(v, 0, dane, alpha, betha);
		dane->dist += dane->matrix[v][dane->path[dane->vnumber-1]];

		if (dane->dist < mini) {
			mini = dane->dist;
			for (int q = 0; q < dane->vnumber; q++) {
				minitab[q] = dane->path[q];
			}
		}
		//(funcja na dodanie feromonow na podstawie path)
		Pheromone_ACO(dane);
		//Sprawdzanie poprawnosci
		/*
		for (int m = 0; m < dane->vnumber; m++) {
			if (!(isin(m, dane->path, dane->vnumber))) {
				cout << "blad" << j << endl;
				for (int z = 0; z < dane->vnumber; z++) {
					cout << dane->path[z] << " ";

				}
				cout << endl;
			}
		}*/
		//show1(dane);

		if (j < ile-1)
			dane->dist = 0;
		
	}

	for (int z = 0; z < dane->vnumber; z++) {
		cout << minitab[z] << " ";

	}
	cout << endl << mini << endl;

	/*
	double suma = 0;
	double min = 0;
	int current = 0;
	double dystans=0;
	
	// zerowanie odwiedzonych
	for (i = 0; i < dane->vnumber; i++)
		dane->visited[i] = 0;

	// WYbieramy najkrotsza scie¿ke tylko wed³ug feromonow

	dane->path[0] = 0;
	dane->visited[0] = 1;

	for (i = 1; i < dane->vnumber; i++)
	{
		
		for (j = 0; j < dane->vnumber; j++)
		{
			if (dane->visited[j]==0)
			{
				if (dane->pheromone_tab[current][j] > min)
				{
					min = dane->pheromone_tab[current][j];
					dane->path[i] = j;

				}
			}
		}

		dane->visited[dane->path[i]] = 1;
		dystans += dane->matrix[current][dane->path[i]];
		current = dane->path[i];
		min = 0;
	}
	
	dystans += dane->matrix[0][dane->path[dane->vnumber-1]];

	// tutaj printujemy odleglosc ostatniej wykonanej sciezki na podstawie feromonow i odleglosci

	for (j = 0; j < dane->vnumber-1; j++)
	{
		//cout << dane->path[j] + 1 << " - "<< dane->path[j+1] +1 << " dystans:    "<< dane->matrix[j][j+1] << " ";
		//suma += dane->matrix[dane->path[j]][dane->path[j + 1]];

		//cout << "wierzcholek: " << dane->path[j] + 1 << endl;
	}

	//cout <<"wierzcholek: "<< dane->path[0] + 1 << endl;
	//cout << dystans<< " "<< dane->dist << endl;
	//show1(dane);
	*/
}