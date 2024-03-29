#include <stdio.h>
#include "sudoku.h"

int main()
{
    solve("test_input_1_invalid.txt", "test_output_1_invalid.txt");
    solve("test_input_2_solvable.txt", "test_output_2_solvable.txt");
    solve("test_input_3_unsolvable.txt", "test_output_3_unsolvable.txt");
    solveN("test_input_4_solvable.txt", "test_output_4_solvable.txt", 81);
    solveN("test_input_5_solvable.txt", "test_output_5_solvable.txt", 81, 300);
    return 0;
}