#include <stdio.h>
#include "sudoku.h"

int main()
{
    solve("test_input_1_invalid.txt", "test_output_1_invalid.txt");
    solve("test_input_2_solvable.txt", "test_output_2_solvable.txt");
    solve("test_input_3_unsolvable.txt", "test_output_3_unsolvable.txt");
    solveNextNumber("test_input_2_solvable.txt", "");
    return 0;
}