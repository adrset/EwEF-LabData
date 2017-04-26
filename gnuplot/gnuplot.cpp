#include<stdio.h>
#include<stdlib.h>
#include<math.h>


FILE * otworzPotokGnuplota() {
	FILE * g_potok = _popen("gnuplot", "w"); /* otwarcie potoku do zapisu */
	return g_potok;
}

void funkcja(FILE * potok, char * jaka, char * a, char * b) {
	fprintf(potok, "plot %s(%s*x+%s)\n", jaka, a, b); // y=f(a*x+b)
}

int main() {
	FILE * gnupotok = otworzPotokGnuplota();
	double i;
	char buf[5];

	for (i = 0; i < 10; i += 0.1) {
		sprintf(buf, "%f", i); /* konwersja double ->char* */
		funkcja(gnupotok, "sin", buf, "3"); /** nasza funkcja f(a*x+b) */
		fflush(gnupotok); /* czyszczenie bufora zapisu */
	
	}
	_pclose(gnupotok);
	return 0;
} /* gcc p.c && ./a.out */