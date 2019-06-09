#pragma once
#include "excel.h"

Cell **create_sheet();

int GET(char *cell, Cell **sheet);

void SET(Command *command, Cell **sheet);

void PRINT(Cell **sheet);

void IMPORT(Command *command, Cell **sheet);

void EXPORT(char *file_name, Cell **sheet);

int detect_cycle(char *expression, Cell **sheet, int actual_row, int actual_col);

int AVG(char *col, Cell **sheet);

int TOTAL(char *row, Cell **sheet);

char *TOPPER(char *sub, Cell **sheet);
