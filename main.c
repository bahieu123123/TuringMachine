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
	if (argc != 5) {
		printf("Error: input.txt description.txt command.txt output.txt \n");
		return -1;
	}
	bool ifLoadTape = false;
	int menuNumb = 0, lastNumb = 4;
	turing* t = malloc(sizeof(turing));
	loadDes(t, args[2]);
	loadCommand(t, args[3]);
	while (menuNumb != 4) {
		menuNumb = menu(lastNumb);
		switch (menuNumb) {
		case 1:
			loadTape(t, args[1]);
			ifLoadTape = true;
			break;
		case 2:
			if (ifLoadTape == false) {
				printf("Initial tape wasn't loaded. Load tape, please!\n");
				break;
			}
			run(t, false, args[4]);
			ifLoadTape = false;
			break;
		case 3:
			if (ifLoadTape == false) {
				printf("Initial tape wasn't loaded. Load tape, please!\n");
				break;
			}
			run(t, true, args[4]);
			ifLoadTape = false;
			break;
		case 4:
			break;
		default:
			break;
		}
	}

	if (t->commands != NULL)
		free(t->commands);
	if (ifLoadTape) {
		while (t->tape->left) {
			tapeT* tmp;
			tmp = t->tape;
			t->tape = t->tape->left;
			free(tmp);
		}
		t->tape = t->tape->left;
		free(t->tape);
	}
	if (t != NULL)
		free(t);
	return 0;
}