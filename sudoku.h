#define N 9
// Sudoku validation functions

// Function to check if the number exists in the row
int is_exist_row(int grid[N][N], int row, int num) 
{
     for (int col = 0; col < N; col++) 
     {
         if (grid[row][col] == num)
             return 1; // Number found in the row
     }
     return 0; // Number not found in the row
}

// Function to check if the number exists in the column
int is_exist_col(int grid[N][N], int col, int num)
 {
     for (int row = 0; row < N; row++) 
     {
         if (grid[row][col] == num)
             return 1; // Number found in the column
     }
    return 0; // Number not found in the column
}

// Function to check if the number exists in the 3x3 box
int is_exist_box(int grid[N][N], int startRow, int startCol, int num) 
{
     for (int row = 0; row < 3; row++) 
     {
         for (int col = 0; col < 3; col++)
          {
             if (grid[row + startRow][col + startCol] == num)
                 return 1; // Number found in the 3x3 box
          }
     }
     return 0; // Number not found in the box
}

// Function to check if placing a number is valid
int is_safe_num(int grid[N][N], int row, int col, int num) 
{
     return !is_exist_row(grid, row, num) &&
            !is_exist_col(grid, col, num) &&
            !is_exist_box(grid, row - row % 3, col - col % 3, num);
}

// Function to check if the Sudoku puzzle is valid
int is_valid_sudoku(int grid[N][N]) 
{
     for (int row = 0; row < N; row++) 
     {
         for (int col = 0; col < N; col++) 
         {
             int num = grid[row][col];
             if (num != 0) 
             {
                 grid[row][col] = 0;
                 if (!is_safe_num(grid, row, col, num)) 
                 {
                     grid[row][col] = num;
                     return 0;
                 }
                 grid[row][col] = num;
             }
         }
     }
    return 1;
}
