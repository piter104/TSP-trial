#include "tsp1.h"

using namespace std;

double suma = 0;


int Probability_ACO(int v, Dane* dane)
{
	int i, next, counter=0, random_number, actual=-1;
	double numbers, distance, alfa = 1, beta = 5, probability, licznik, mianownik = 0, probability_tab[150] = {0};

	//liczymy mianownik
	for (i = 0; i < dane->vnumber; i++)
	{
		if (dane->visited[i] == 0)
		{
			distance = 1 / dane->matrix[v][i];
			mianownik += pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
		}
	}

	//liczymy prawdopodobienstwa
	for (i = 0; i <= dane->vnumber; i++)
	{
		if (dane->visited[i] == 0)
		{
			//jak ze wzoru
			distance = 1 / dane->matrix[v][i];
			licznik = pow(dane->pheromone_tab[v][i], alfa) * pow(distance, beta);
			probability = licznik / mianownik;
			//probability = round(probability * 10000) / 10000;
			numbers = probability * 100;
			//cout <<"numbers: " << numbers << endl;
			suma += numbers;
			//cout << "suma" << suma << endl;
			while (counter < numbers)
			{
				probability_tab[actual+1+counter++] = i;
			}
			actual += counter;
			counter = 0;
		}
	}
	//losowanko ale nie wiem czy dobrze odmierzylem zeby robilo akurat 100 miejsc - do zweryfikowania
	random_number = rand() % 100;
	//cout << "random: "<< random_number<< " " <<probability_tab[random_number] << endl;
	return probability_tab[random_number];
}


void Pheromone_ACO(Dane*dane)
{
	int i;
	double reduction = 0.7, pheromone_change;
	for (i = 0; i < dane->vnumber; i++)
	{
		//jak ze wzoru
		if(i < dane->vnumber-1)
		{
			dane->pheromone_tab[dane->path[i]][dane->path[i + 1]] = reduction * dane->pheromone_tab[dane->path[i]][dane->path[i + 1]] + (dane->dist / 100);
			dane->pheromone_tab[dane->path[i + 1]][dane->path[i]] = reduction * dane->pheromone_tab[dane->path[i+1]][dane->path[i]] + (dane->dist / 100);
			//cout << "path: " << dane->path[i+1] << endl;
			//cout << "wierzcholek: " << i << endl;
		}
		else
		{

			//tutaj laczymy ostatni z pierwszym ale nie wiem czy to dobrze
			dane->pheromone_tab[dane->path[i]][dane->path[0]] = reduction * dane->pheromone_tab[dane->path[i]][dane->path[0]] + (dane->dist / 100);
			dane->pheromone_tab[dane->path[0]][dane->path[i]] = reduction * dane->pheromone_tab[dane->path[0]][dane->path[i]] + (dane->dist / 100);
		}
	}
}

void find_path_ACO(int v, int counter, Dane* dane)
{
	int next;
	//cout << "Wierzcholek: "<< v << endl;
	dane->visited[v] = 1;
	dane->path[counter++] = v;

	//next = (funkcja na wybor nastepnego wierzcholka - prawdopodobienstwo)
	next = Probability_ACO(v, dane);



	if (counter < dane->vnumber) 
	{
		dane->dist += dane->matrix[v][next];
		find_path_ACO(next, counter, dane);
	}
	else
		return;
}


void TSP_ACO(Dane* dane)
{
	int j, i, v;

	//robimy to dla kilku mrowek, stad petla
	for (j = 0; j < 1000; j++)
	{
		for (i = 0; i < dane->vnumber; i++)
			dane->visited[i] = 0;
		//v = rand() % (dane->vnumber) - 1;
		v = 0;
		//cout << v << endl;
		find_path_ACO(v, 0, dane);
		dane->dist += dane->matrix[v][dane->path[dane->vnumber - 1]];

		//(funcja na dodanie feromonow na podstawie path)
		Pheromone_ACO(dane);
		if(j<999)
		dane->dist = 0;

	}

	for (j = 0; j < dane->vnumber; j++)
	{
		cout << dane->path[j] + 1 << " ";
	}
	cout << dane->path[0] + 1 << endl;
	cout << dane->dist << endl;
}