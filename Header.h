#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ENTER 10

typedef struct {
	int number;
	int state1; //Тут сохраняется индекс состояния, при котором выплоняется команд, в массиве states
	int symbol1; //Тут сохраняется индекс символа, при котором выплоняется команд, в массиве symbols
	int symbol2; //Тут сохраняется индекс символа, который нужен записать в ячейку, в массиве symbols
	char dir; //просто направление сдвига головки
	int state2; //Тут сохраняется индекс состояния, в которое нужно перейти, в массиве states
} command;

typedef struct tapeT tapeT;
struct tapeT {
	int symbol;
	tapeT* left;
	tapeT* right;
};

typedef struct {
	int statesNumb;    // кол-во используемых состояний
	char* states;//множество состояний
	int symbolsNumb;// кол-во используемых символов
	char* symbols;//альфавит
	int state;// состояние в головке
	int commandsNumb;//число команд
	command* commands;//команды
	tapeT* tape;// лента
} turing;

int menu(int lastNumb);

int stateIndex(turing* t, char state); //нахождение номер индекса состояния state в states
int symbolIndex(turing* t, char symbol); //нахождение номер индекса symbol в symbols
void loadCommand(turing* t, char* nameFile); //загрузка команд из текстового файла

command findCommand(turing* t, char stateCurrent, char symbolCurrent);//нахождение нужной команды из список всех команд

void run(turing* t, bool step, char* nameFile);

void loadDescription(turing* t, char* nameFile); //загрузка описание машины из текстового файла#pragma once
