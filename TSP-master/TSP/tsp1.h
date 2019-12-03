#ifndef TSP1_H 
#define TSP1_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <string.h>

using namespace std;

struct Dane {
	int** verticals, * path, vnumber;
	double** matrix, **pheromone_tab, dist = 0;
	bool* visited;
};
bool isin(int n, int* tab, int r);
void gen(int n, string name);

void distance(Dane* dane);
void find_path(int v, Dane* dane, int counter);
void TSP(int v, Dane* dane);
void show(Dane dane);
Dane wczytaj(string nazwa);

void TSP_ACO(Dane* dane, int ile, double alpha, double betha);
void find_path_ACO(int v, int counter, Dane* dane, double alpha, double betha);
void Pheromone_ACO(Dane* dane);
int Probability_ACO(int v, Dane* dane, double alpha, double betha);
void show1(Dane* dane);

#endif
