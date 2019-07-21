#include "Header.h"

/*
 * Команды обязательно написать в следующем виде:
 1. a 1 1 R a
 2. a 0 0 R a
 3. a B B L b
 4. b 0 1 L c
 5. b 1 0 L b
 6. b B 1 L S
 ...
 */
void loadCommand(turing* t, char* nameFile) {
	FILE* in;
	in = fopen(nameFile, "r");
	if (in == NULL) {
		printf("The file '%s' was not opened", nameFile);
		exit(-1);
	}

	printf("\nCommands:\n");
	int commandNumb = 1, N = 0;
	t->commands = malloc((N + 1) * sizeof(command));
	int numb;
	while (fscanf(in, "%d. ", &numb) != EOF) {
		command tran;
		char symbol1, symbol2, dir, state1, state2;

		if (numb <= 0) {
			printf("Error in '%s' file. There may only be commands from [1...] interval \n", nameFile);
			fclose(in);
			exit(0);
		}
		if (numb != commandNumb) {
			printf("Error in '%s' file. Command numbers must be in order \n", nameFile);
			fclose(in);
			exit(0);
		}
		commandNumb++;

		fscanf(in, "%c ", &state1);
		fscanf(in, "%c ", &symbol1);
		fscanf(in, "%c ", &symbol2);
		fscanf(in, "%c ", &dir);
		fscanf(in, "%c", &state2);

		tran.number = numb;
		tran.state1 = stateIndex(t, state1);

		if (tran.state1 == -1) {
			printf("Error in '%s' file", nameFile);
			printf("\nIn the command %d, state %c isn't contained in the set of states of your Turing machine", numb,
				state1);
			fclose(in);
			exit(0);
		}
		tran.symbol1 = symbolIndex(t, symbol1);
		if (tran.symbol1 == -1) {
			printf("\nError in '%s' file", nameFile);
			printf("\nIn the commnand %d, symbol %c isn't contained in the alphabet of your Turing machine", numb,
				symbol1);
			fclose(in);
			exit(0);
		}
		tran.symbol2 = symbolIndex(t, symbol2);
		if (tran.symbol2 == -1) {
			printf("\nError in 'command.txt' file");
			printf("\nIn the commnand %d, symbol %c isn't contained in the alphabet of your Turing machine", numb,
				symbol2);
			fclose(in);
			exit(0);
		}
		tran.dir = dir;
		tran.state2 = stateIndex(t, state2);
		if (tran.state2 == -1) {
			printf("\nError in '%s' file", nameFile);
			printf("\nIn the command %d, state %c isn't contained in the set of states of your Turing machine", numb,
				state2);
			fclose(in);
			exit(0);
		}

		t->commands[N] = tran;
		printf("%d. %c %c %c %c %c\n", numb, state1, symbol1, symbol2, dir, state2);
		N++;
		t->commands = realloc(t->commands, (N + 1) * sizeof(command));
	}
	t->commandsNumb = N;
	fclose(in);
}