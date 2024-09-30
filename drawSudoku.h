#include "raylib.h"

#define N 9
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define GRID_WIDTH 540
#define GRID_HEIGHT 540
#define CELL_SIZE (GRID_WIDTH / N)
#define offsetX (SCREEN_WIDTH - GRID_WIDTH) / 2
#define offsetY (SCREEN_HEIGHT - GRID_HEIGHT) / 2
#define LIGHTBEIGE (Color){ 255, 239, 210, 255 } // Light Beige
#define INNERGRIDCOLOR (Color){ 250, 245, 235, 255  }  // Inner Grid Color
#define FONTCOLOR (Color){ 100, 80, 50, 255 }  // Font color

// Function to draw the grid
void DrawSudokuGrid(int grid[N][N], int selectedRow, int selectedCol) 
{

     // Draw the black rectangle (outer border)
     float outerThickness = 6;
     DrawRectangle(offsetX - outerThickness, offsetY - outerThickness, GRID_WIDTH + 2 * outerThickness, GRID_HEIGHT + 2 * outerThickness, BLACK);

     // Draw the grey rectangle (inside grid)
     DrawRectangle(offsetX, offsetY, GRID_WIDTH, GRID_HEIGHT, INNERGRIDCOLOR);
    
    // Draw the grid lines
     for (int i = 0; i <= N; i++) 
     {
         float thickness = (i % 3 == 0) ? 3 : 1;  // Thicker lines for 3x3 grid blocks
         DrawLineEx((Vector2) {offsetX + i * CELL_SIZE, offsetY}, (Vector2) {offsetX + i * CELL_SIZE, offsetY + GRID_HEIGHT}, thickness, BLACK); //Vertical
         DrawLineEx((Vector2){offsetX, offsetY + i * CELL_SIZE}, (Vector2) {offsetY + GRID_HEIGHT, offsetY + i * CELL_SIZE}, thickness, BLACK); //Horizontal
     }

    // Draw the numbers in the grid
     for (int row = 0; row < N; row++)
      {
         for (int col = 0; col < N; col++) 
         {
             if (grid[row][col] != 0) 
             {
                 DrawText(TextFormat("%d", grid[row][col]), offsetX + col * CELL_SIZE + CELL_SIZE / 2 - 10, offsetY + row * CELL_SIZE + CELL_SIZE / 2 - 10, 20, FONTCOLOR);
             }
         }
     }

    // Highlight the selected cell
     if (selectedRow >= 0 && selectedCol >= 0) 
     {
         DrawRectangleLines(offsetX + selectedCol * CELL_SIZE, offsetY + selectedRow * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
     }
}