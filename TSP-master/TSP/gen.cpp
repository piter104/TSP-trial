

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>

using namespace std;

bool isin(int n, int *tab, int r) {
	if (r == 0) {
		return false;
	}
	for (int i = 0; i < r; i++) {
		if (n == tab[i]) {
			return true;
		}
	}
	return false;
}

void gen(int n, string name) {
	int *usedx, *usedy, x, y, ilex = 0, iley = 0;
	bool juz = true;
	usedx = new int[n];
	usedy = new int[n];
	ofstream plik;
	plik.open(name);
	plik << n << "\n";
	for (int i = 0; i < n; i++) {
		while (juz) {
			x = rand() % 3000;
			if (!isin(x, usedx, ilex)) {
				usedx[ilex++] = x;
				juz = false;
			}
		}
		juz = true;
		while (juz) {
			y = rand() % 3000;
			if (!isin(y, usedy, iley)) {
				usedy[iley++] = y;
				juz = false;
			}
		}
		juz = true;
		plik << ilex << " " << x << " " << y << "\n";
	}
	plik.close();
}

int main()
{
	srand(time(NULL));
	gen(11, "plik.txt");

	return 0;
}

