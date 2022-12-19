#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<locale.h>

struct obraz
{
	int wysokosc;
	int dlugosc;
	char typ[2];
	int szarosc;
	int** pixele;
};

void  dynamicznaalokacjap2(struct obraz* p2)
{
	int i;
	p2->pixele = malloc((p2->wysokosc) * sizeof(int*));
	for (i = 0; i < p2->wysokosc; i++)
	{
		p2[0].pixele[i] = malloc(p2->dlugosc * sizeof(int));

		if ((p2->pixele)[i] == NULL)
		{
			printf("Nie udalo sie zaalokowac pamieci\n");

			for (int i = 0; i < p2->wysokosc; i++)//zwalnianie pamieci
			{
				free((p2->pixele)[i]);
			}
			free(p2->pixele);

			exit(0);
		}
	}

}

void dodaj(struct obraz* p2)
{
	FILE* obrazek1;
	char nazwa[100];
	int i;
	int j;
	printf("Podaj nazwe pliku nazwa.pgm \n");//strcut
	scanf("%s", &nazwa);
	obrazek1 = fopen(nazwa, "r");
	if (obrazek1 == NULL)
	{
		printf("Podany plik nie istnieje\n");
	}
	else
	{
		printf("Znaleziono plik\n");
	}

	fscanf(obrazek1, "%s", &(p2->typ));
	printf("%s\n", p2->typ);
	fscanf(obrazek1, "%d %d", &(p2->wysokosc), &(p2->dlugosc));
	printf("%d %d\n", p2->wysokosc, p2->dlugosc);
	fscanf(obrazek1, "%d", &(p2->szarosc));
	printf("%d\n", p2->szarosc);

	for (i = 0; i < p2->wysokosc; i++)
	{
		for (j = 0; j < p2->dlugosc; j++)
		{
			fscanf(obrazek1, "%d", &((p2->pixele)[i][j]));
		}
	}

	/*
	for (i = 0; i < p2->wysokosc; i++)
	{
		for (j = 0; j < p2->dlugosc; j++)
		{
			printf("%d ", p2->pixele[i][j]);
		}
		printf("\n");
	}*/

	fclose(obrazek1);
}

int main()
{
	setlocale(LC_ALL, "polish_poland");
	struct obraz p2;
	struct obraz* wskp2;
	wskp2 = NULL;
	wskp2 = &p2;
	char* nazwa;

	dynamicznaalokacjap2(wskp2);
	dodaj(wskp2);



	for (int i = 0; i < p2.wysokosc; i++)
	{
		free(p2.pixele[i]);
	}
	free(p2.pixele);
}