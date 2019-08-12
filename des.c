#include "Header.h"

/*
 * Формат файла description.txt:
  abcS - это множество состояний
  01B - это алфавит
 */

void loadDes(turing* t, char* nameFile) {
	FILE* in;
	in = fopen(nameFile, "r");
	if (in == NULL) {
		printf("The file '%s' was not opened", nameFile);
		exit(-1);
	}
	bool testForS = false, testForBlank = false;

	printf("States: ");
	int N = 0;
	char c;
	t->states = malloc((N + 1) * sizeof(char));
	fscanf(in, "%c", &c);
	while (c != '\n') {
		t->states[N] = c;
		if (t->states[N] == 'S') {
			testForS = true;
		}
		printf("%c ", t->states[N]);
		fscanf(in, "%c", &c);
		N++;
		t->states = realloc(t->states, (N + 1) * sizeof(char));
	}
	t->statesNumb = N;

	if (!testForS) {
		printf("\nError in file '%s'", nameFile);
		printf("\nThe set of states doesn't contain state STOP(S). Add S to it, please!");
		fclose(in);
		exit(0);
	}

	printf("\nAlphabet: ");
	N = 0;
	t->symbols = malloc((N + 1) * sizeof(char));
	while (fscanf(in, "%c", &c) != EOF) {
		t->symbols[N] = c;
		if (t->symbols[N] == 'B') testForBlank = true;
		printf("%c ", t->symbols[N]);
		N++;
		t->symbols = realloc(t->symbols, (N + 1) * sizeof(char));
	}
	t->symbolsNumb = N;

	if (!testForBlank) {
		printf("\nError in file '%s'", nameFile);
		printf("\nThe alphabet doesn't contain symbol Blank(B). Add B to it, please!");
		fclose(in);
		exit(0);
	}

	t->symbolsNumb++;
	t->symbols[t->symbolsNumb - 1] = ' ';
	printf("%c ", t->symbols[t->symbolsNumb - 1]);

	fclose(in);
}