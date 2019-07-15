#include "Header.h"

/*
 * Формат файла input.txt, в котором сохраняется исходная лента:
 * a - начальное состояние
 * 10111 - Исходная лента
 */
void loadTape(turing* t, char* nameFile) {
	FILE* in;
	in = fopen(nameFile, "r");
	if (in == NULL) {
		printf("The file '%s' was not opened", nameFile);
		exit(-1);
	}
	char state, linefeed;
	fscanf(in, "%c", &state);
	t->state = stateIndex(t, state);
	printf("\nInitial state: %c\n", state);
	if (t->state == -1) {
		printf("Error in file '%s'\n", nameFile);
		printf("Initial state %c isn't contained in the set of states of your Turing machine", state);
		fclose(in);
		exit(0);
	}
	fscanf(in, "%c", &linefeed);
	if (linefeed != '\n') {
		printf("Error in file '%s'. There may only be linefeed after initial state\n", nameFile);
		fclose(in);
		exit(0);
	}

	t->tape = NULL;
	char x;
	fscanf(in, "%c ", &x);
	printf("Initial tape: %c", x);
	if (symbolIndex(t, x) == -1) {
		printf("Error in '%s' file. Symbol %c isn't contained in the alphabet of your Turing machine", nameFile, x);
		fclose(in);
		exit(0);
	}
	if (t->tape == NULL) {
		t->tape = malloc(sizeof(tapeT));
		t->tape->symbol = symbolIndex(t, x);
		t->tape->right = NULL;
		t->tape->left = NULL;
	}
	tapeT* temp_tape;
	temp_tape = t->tape;
	while (!feof(in)) {
		fscanf(in, "%c ", &x);
		printf("%c", x);
		if (symbolIndex(t, x) == -1) {
			printf("Error in '%s' file. Symbol %c isn't contained in the alphabet of your Turing machine", nameFile, x);
			fclose(in);
			exit(0);
		}
		if (temp_tape->right == NULL) {
			tapeT* tmp_tp = temp_tape;
			temp_tape->right = malloc(sizeof(tapeT));
			if (temp_tape->right == NULL)
			{
				printf("Not enough memory for tape \n");
				exit(103);
			}
			temp_tape = temp_tape->right;
			temp_tape->symbol = symbolIndex(t, x);
			temp_tape->right = NULL;
			temp_tape->left = tmp_tp;
		}
	}
	printf("\n");
	fclose(in);

}

int main(int argc, char* args[]) {
	
}