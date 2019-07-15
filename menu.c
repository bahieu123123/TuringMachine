#include "Header.h"

int menu(int lastNumb) {
	int number, ret;
	printf("Modes of the machine:\n"
		"1. Load tape \n"
		"2. Run\n"
		"3. Run step\n"
		"4. Exit\n");
	while (1) {
		printf("\nInput ordinal number of modes(1->%d)", lastNumb);
		ret = scanf("%d", &number);;
		if (ret == 1 && (number >= 1 && number <= lastNumb)) break;
		fflush(stdin);
		printf("Error. Number must be in the interval [1..%d]", lastNumb);
		break;
	}
	return number;
}
