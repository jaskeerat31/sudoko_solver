This C++ program solves sudoko puzzles for you. By default i have made a 9x9 sudoko solver which uses backtracking and recursion.
You can input the sudoko in two ways:
 1. Manually entering the values.
 2. Saving the values in a file in typing the fie name in the prompt.
 
How it works?
The most common method of solving sudoko is backtracking and i have implemented the same concept.
 ->We start with the first empty cell.
 ->We generate a list of possible valid values that can be filled in that cell.
 ->We iterate over this list and start with the first value. This value is placed in the required cell.
 ->We move on to the next cell. We again generate a list of possibilities. However, if no list can be generated, then this means that        there is something wrong with the value of the previous cell. We then move back to the previous cell and place the next value on the      generated list in the cell now. We repeat this step until the current cell has a valid value placed inside it.
 ->We stop when we reach the 81st cell (the last cell in a Sudoku puzzle) and have placed a valid value.
 ->The puzzle has now been solved.
 
