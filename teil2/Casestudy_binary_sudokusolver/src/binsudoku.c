#include "binsudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
Use a very fast specific machine instruction inside find_empty_cell()
*/ 
#if defined(__GNUC__) || defined(__clang__)
    inline int bit_scan_forward(int x){
        return __builtin_ffs(x) - 1;
    }
#elif defined(_MSC_VER)
    #include <intrin.h>
    inline int bit_scan_forward(int x){
        unsigned long z;
        _BitScanForward(&z, x);
        return z;
    }
#else
    #error "Only gcc, clang and mvsc compiler are supported."
#endif



/**
 * @brief      Initializes heap memory for the sudoku
 *
 * @return     sudoku_t* or NULL
 */
sudoku_t* init_sudoku(){
    sudoku_t* S = malloc(sizeof(sudoku_t));
    S->puzzle = calloc(9*9, sizeof(int));
    S->binrows = calloc(9, sizeof(int));
    S->bincols = calloc(9, sizeof(int));
    S->binindx = calloc(9, sizeof(int));
    S->binboxes = calloc(9, sizeof(int));
    return S;
}


/**
 * @brief      Fills the S->puzzle with values given in puzzle
 *
 * @param      S       Pointer to the sudoku_t struct
 * @param      puzzle  Given sudoku we want to solve
 */
void fill_sudoku(sudoku_t* S, int* puzzle){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            S->puzzle[i*9+j] = puzzle[i*9+j];
        }
    }
}


/**
 * @brief      Encodes the given sudoku puzzle inside the sudoku_t struct
 *             into the binary representation
 *
 * @param[in]  S     Pointer to the sudoku_t struct
 */
void encode_to_binary(sudoku_t* S){
	for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (S->puzzle[i*9+j] > 0) {
                int k = 3 * (i / 3) + (j / 3);
                S->binindx[i] |= (1U << j);
                S->binrows[i] |= (1U << S->puzzle[i*9+j]);
                S->bincols[j] |= (1U << S->puzzle[i*9+j]);
                S->binboxes[k] |= (1U << S->puzzle[i*9+j]);
            }
        }
    }
}


/**
 * @brief      Finds the first empty cell inside the sudoku
 *
 * @param[in]  S     Pointer to the sudoku_t struct
 *
 * @return     A ctuple with the coordinates of the empty cell, (-1, -1)
 *             if there's no empty cell inside the sudoku
 */
ctuple_t find_empty_cell(sudoku_t* S){
	ctuple_t t = {.x = -1, .y = -1};
    for (int i = 0; i < 9; ++i) {
        int col = bit_scan_forward(~(S->binindx[i]));
        if (col != -1 && col != 9) {
            t.x = i;
            t.y = col;
            return t;
        }
    }
    return t;
}


/**
 * @brief      Checks whether the number num can be placed at (row, col)
 *
 * @param[in]  S     Pointer to the sudoku_t struct
 * @param[in]  num   The number
 * @param[in]  row   The row
 * @param[in]  col   The col
 *
 * @return     true or false
 */
inline bool num_valid(sudoku_t* S, int num, int row, int col){
    unsigned int shift = 1U << num;
    return !(((S->binrows[row] & shift) || (S->bincols[col] & shift)) ||
             (S->binboxes[3 * (row / 3) + (col / 3)] & shift));
}



/**
 * @brief      Sets the number num at (row, col)
 *
 * @param[in]  S     Pointer to the sudoku_t struct
 * @param[in]  num   The number
 * @param[in]  row   The row
 * @param[in]  col   The col
 */
inline void set_num(sudoku_t* S, int num, int row, int col) {
    unsigned int shift = 1U << num;
    S->binrows[row] |= shift;
    S->bincols[col] |= shift;
    S->binboxes[3 * (row / 3) + (col / 3)] |= shift;
    S->binindx[row] |= (1U << col);
    S->puzzle[row*9+col] = num;
}


/**
 * @brief      Deletes the number num at (row, col)
 *
 * @param[in]  S     Pointer to the sudoku_t struct
 * @param[in]  num   The number
 * @param[in]  row   The row
 * @param[in]  col   The col
 */
inline void del_num(sudoku_t* S, int num, int row, int col) {
    unsigned int nshift = ~(1U << num);
    S->binrows[row] &= nshift;
    S->bincols[col] &= nshift;
    S->binboxes[3 * (row / 3) + (col / 3)] &= nshift;
    S->binindx[row] &= ~(1U << col);
    S->puzzle[row*9+col] = 0U;
}



/**
 * @brief      Try to solve the given sudoku
 *
 * @param[in]  S     Pointer to the sudoku_t struct
 *
 * @return     true or false
 */
bool solver(sudoku_t* S){
    ctuple_t pos = find_empty_cell(S);
    if (pos.x == -1 || pos.y == -1) {
        return true;
    }

    for (int num = 1; num <= 9; ++num) {
        if (num_valid(S, num, pos.x, pos.y)) {
            set_num(S, num, pos.x, pos.y);
            if (solver(S)) {
                return true;
            }
            // Backtracking
            del_num(S, num, pos.x, pos.y);
        }
    }

    // Backtracking / Abort
    return false;
}



/**
 * @brief      Frees all allocated memory
 *
 * @param      S     Pointer to the sudoku_t struct.
 */
void free_sudoku(sudoku_t* S){
    free(S->puzzle);
    free(S->binrows);
    free(S->bincols);
    free(S->binindx);
    free(S->binboxes);
    free(S);
}