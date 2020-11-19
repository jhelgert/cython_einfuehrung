#ifndef BINSUDOKU_H
#define BINSUDOKU_H

#include <stdbool.h>

typedef struct sudoku_t{
    int* puzzle;
    int* binrows;
    int* bincols;
    int* binboxes;
    int* binindx;
} sudoku_t;

typedef struct ctuple_t{
    int x;
    int y;
} ctuple_t;

sudoku_t* init_sudoku();
void fill_sudoku(sudoku_t* S, int* puzzle);
void encode_to_binary(sudoku_t* S);
ctuple_t find_empty_cell(sudoku_t* S);
inline bool num_valid(sudoku_t* S, int num, int row, int col);
inline void set_num(sudoku_t* S, int num, int row, int col);
inline void del_num(sudoku_t* S, int num, int row, int col);
bool solver(sudoku_t* S);
void free_sudoku(sudoku_t* S);

#endif // BINSUDOKU_H