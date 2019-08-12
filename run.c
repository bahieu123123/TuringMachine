#include "Header.h"

command findCommand(turing* t, char stateCurrent, char symbolCurrent) {
	// find by state
	command* resTrans1 = malloc(t->symbolsNumb * sizeof(command));
	command resTrans;
	int j = 0;
	for (int i = 0; i < t->commandsNumb; i++) {
		if (t->states[t->commands[i].s1] == stateCurrent) {
			resTrans1[j] = t->commands[i];
			j++;
		}
	}
	// find by symbol
	for (int i = 0; i < t->symbolsNumb - 1; i++) {
		if (t->symbols[resTrans1[i].sb1] == symbolCurrent) {
			resTrans = resTrans1[i];
		}
	}
	free(resTrans1);
	return resTrans;
}

void run(turing* t, bool step, char* nameFile) {
	int key;
	char stepCommand[5];
	FILE* output;
	output = fopen(nameFile, "w");
	if (output == NULL) {
		printf("The file '%s' was not opened\n", nameFile);
		exit(-1);
	}
	if (step) printf("<Enter> - next step, stop - stop, run - run\n");
	tapeT* tempTape = t->tape;
	int idPrint = 0, i = 0;
	command currentTrans;
	while (1) {
		if (i != 0) {
			fprintf(output, "\n%d. %c %c %c %c %c\n", currentTrans.number, t->states[currentTrans.s1],
				t->symbols[currentTrans.sb1], t->symbols[currentTrans.sb2], currentTrans.dir,
				t->states[currentTrans.s2]);
			printf("%d. %c %c %c %c %c", currentTrans.number, t->states[currentTrans.s1],
				t->symbols[currentTrans.sb1], t->symbols[currentTrans.sb2], currentTrans.dir,
				t->states[currentTrans.s2]);
			printf("\nCurrent state: %c\n", t->states[currentTrans.s2]);
		}
		i++;
		tapeT* tape = t->tape;
		while (tape->left != NULL) {
			tape = tape->left;
		}
		int idPrint1 = 0;
		while (tape->right != NULL) {
			if (idPrint1 == idPrint) {
				fprintf(output, "[%c]", t->symbols[tape->symbol]);
				printf("[%c]", t->symbols[tape->symbol]);
				idPrint1++;
			}
			else {
				fprintf(output, " %c ", t->symbols[tape->symbol]);
				printf(" %c ", t->symbols[tape->symbol]);
				idPrint1++;
			}
			tape = tape->right;
		}
		if (idPrint1 == idPrint) {
			fprintf(output, " [%c] ", t->symbols[tape->symbol]);
			printf(" [%c] ", t->symbols[tape->symbol]);
		}
		else {
			fprintf(output, " %c ", t->symbols[tape->symbol]);
			printf(" %c ", t->symbols[tape->symbol]);
		}
		fprintf(output, "\n");
		printf("\n");

		if (t->states[t->state] == 'S') {
			fclose(output);
			return;
		}

		if (t->symbols[tempTape->symbol] == ' ') {
			currentTrans = findCommand(t, t->states[t->state], 'B');
			printf("1 \n");
		}
		else {
			currentTrans = findCommand(t, t->states[t->state], t->symbols[tempTape->symbol]);
		}
		if (t->symbols[currentTrans.sb2] == 'B') {
			tempTape->symbol = t->symbolsNumb - 1;
		}
		else {
			tempTape->symbol = currentTrans.sb2;
		}
		if (currentTrans.dir == 'R') {
			idPrint++;
			if (tempTape->right == NULL) {
				tempTape->right = malloc(sizeof(tapeT));


				tapeT* tt = tempTape->right;
				tt->left = tempTape;
				tt->right = NULL;
				tt->symbol = t->symbolsNumb - 1;
			}
			tempTape = tempTape->right;
		}
		else {
			idPrint--;
			if (tempTape->left == NULL) {
				tempTape->left = malloc(sizeof(tapeT));


				tapeT* tt = tempTape->left;
				tt->right = tempTape;
				tt->left = NULL;
				tt->symbol = t->symbolsNumb - 1;
				idPrint = 0;
			}
			tempTape = tempTape->left;
		}

		t->state = currentTrans.s2;

		if (step) {
			while (1) {
				key = getc(stdin);
				if (key == ENTER) break;
				ungetc(key, stdin);
				scanf(" %4s", stepCommand);
				fflush(stdin);
				if (!strcmp(stepCommand, "run")) {
					step = false;
					break;
				}
				if (!strcmp(stepCommand, "stop")) {
					fclose(output);
					return;
				}
				printf("error");
				fflush(stdin);
			}
		}

	}
}
