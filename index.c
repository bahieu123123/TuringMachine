#include "Header.h"

int stateIndex(turing* t, char state) {

	int i;
	for (i = 0; i < t->statesNumb; i++) {
		if (t->states[i] == state) {
			return i;
		}
	}
	return -1;
}

int symbolIndex(turing* t, char symbol) {
	int i;
	for (i = 0; i < t->symbolsNumb; i++) {
		if (t->symbols[i] == symbol) {
			return i;
		}
	}
	return -1;
}