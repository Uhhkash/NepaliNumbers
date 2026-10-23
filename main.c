#include "raylib.h"
#include <string.h>
#include <stdbool.h>

int main(void) {
    
    InitWindow(800, 600, "Nepali Number Typing Game");

    SetTargetFPS(60);

    // Main game loop, runs until user closes the window
    while(!WindowShouldClose()) {
        // Drawing phase
        BeginDrawing();
        // Clear the screen to black 
         ClearBackground(BLACK);     
        //Draw text on the screen
         // Parameters: Text, X coordinate, Y coordinate, Font Size, Color
         DrawText("१", 350, 250, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
}