#include <stdio.h>
#include "raylib.h"

#define N 9
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELL_SIZE (SCREEN_WIDTH / N)

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

// Function to draw the grid
void DrawSudokuGrid(int grid[N][N], int selectedRow, int selectedCol) 
{
    // Draw the grid lines
     for (int i = 0; i <= N; i++) 
     {
         float thickness = (i % 3 == 0) ? 3 : 1;  // Thicker lines for 3x3 grid blocks
         DrawLineEx((Vector2) {i * CELL_SIZE, 0}, (Vector2) {i * CELL_SIZE, SCREEN_HEIGHT}, thickness, BLACK);
         DrawLineEx((Vector2){0, i * CELL_SIZE}, (Vector2){SCREEN_WIDTH, i * CELL_SIZE}, thickness, BLACK);
     }

    // Draw the numbers in the grid
     for (int row = 0; row < N; row++)
      {
         for (int col = 0; col < N; col++) 
         {
             if (grid[row][col] != 0) 
             {
                 DrawText(TextFormat("%d", grid[row][col]), col * CELL_SIZE + CELL_SIZE / 2 - 10, row * CELL_SIZE + CELL_SIZE / 2 - 10, 20, DARKBLUE);
             }
         }
     }

    // Highlight the selected cell
     if (selectedRow >= 0 && selectedCol >= 0) 
     {
         DrawRectangleLines(selectedCol * CELL_SIZE, selectedRow * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
     }
}

int main() {
    // Example of a Sudoku puzzle (0 represents empty spaces)
     int grid[N][N] = 
         {{5, 3, 0, 0, 7, 0, 0, 0, 0},
         {6, 0, 0, 1, 9, 5, 0, 0, 0},
         {0, 9, 8, 0, 0, 0, 0, 6, 0},
         {8, 0, 0, 0, 6, 0, 0, 0, 3},
         {4, 0, 0, 8, 0, 3, 0, 0, 1},
         {7, 0, 0, 0, 2, 0, 0, 0, 6},
         {1, 6, 0, 0, 0, 0, 2, 8, 0},
         {0, 0, 0, 4, 1, 9, 0, 0, 5},
         {0, 0, 0, 0, 8, 0, 0, 7, 9}};

     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku Input");
     SetTargetFPS(60);

     int selectedRow = -1, selectedCol = -1;  // No cell selected initially
     char validationMessage[20] = "";         // Message to show if Sudoku is valid or not

     while (!WindowShouldClose()) 
     {
        // Handle input
         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
         {
            // Detect clicked cell
             Vector2 mousePosition = GetMousePosition();
             selectedCol = mousePosition.x / CELL_SIZE;
             selectedRow = mousePosition.y / CELL_SIZE;
         }

        // Handle number input when a cell is selected
         if (selectedRow >= 0 && selectedCol >= 0) 
         {
             for (int i = KEY_ONE; i <= KEY_NINE; i++) 
             {
                 if (IsKeyPressed(i)) 
                 {
                     grid[selectedRow][selectedCol] = i - KEY_ONE + 1;  // Assign number 1-9
                 }
             }

            // Clear the cell with '0'
             if (IsKeyPressed(KEY_ZERO)) 
             {
                 grid[selectedRow][selectedCol] = 0;  // Clear the cell
             }
         }

        // Validate Sudoku when ENTER is pressed
         if (IsKeyPressed(KEY_ENTER)) 
         {
             if (is_valid_sudoku(grid)) 
             {
                 sprintf(validationMessage, "Sudoku is valid!");
             } 
             else 
             {
                 sprintf(validationMessage, "Sudoku is invalid!");
             }
         }

         BeginDrawing();
         ClearBackground(RAYWHITE);

         // Draw the Sudoku grid with the current state
         DrawSudokuGrid(grid, selectedRow, selectedCol);

         // Display validation message
         if (validationMessage[0] != '\0') 
         {
             DrawText(validationMessage, 10, SCREEN_HEIGHT - 40, 20, (validationMessage[9] == 'v') ? GREEN : RED);
         }

         EndDrawing();
     }

     CloseWindow();
    
     return 0;
}