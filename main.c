#include <stdio.h>
#include <string.h>
#include "sudoku.h"
#include "drawSudoku.h"
#include "raylib.h"

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
     char validationMessage[20] = ""; 
            

     while (!WindowShouldClose()) 
     {
        // Handle input
         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
         {
            // Detect clicked cell
             Vector2 mousePosition = GetMousePosition();

             if(mousePosition.x >= offsetX && mousePosition.x < offsetX + GRID_WIDTH && mousePosition.y >= offsetY && mousePosition.y < offsetY + GRID_HEIGHT)
             {
                 selectedCol = (mousePosition.x - offsetX) / CELL_SIZE;
                 selectedRow = (mousePosition.y - offsetY)/ CELL_SIZE;
             }
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
         ClearBackground(LIGHTBEIGE);

         // Draw the Sudoku grid with the current state
         DrawSudokuGrid(grid, selectedRow, selectedCol);

         // Display validation message
         DrawText(validationMessage, 10, SCREEN_HEIGHT - 40, 20, (validationMessage[10] == 'v') ? GREEN : RED);
         

         EndDrawing();
     }

     CloseWindow();
    
     return 0;
}