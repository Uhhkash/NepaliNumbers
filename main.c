#include "raylib.h"
#include <stdio.h>

int main(void) {
    
    InitWindow(800, 600, "Nepali Number Typing Game");

    SetTargetFPS(60);
                        
    // Tell Raylib which characters you want the font to support 
    // (including standard English text, numbers, and Nepali Devanagari numerals)
    const char *supportedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789१२३४५६७८९० ";
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(supportedChars, &codepointCount);

    if (codepoints == NULL) {
        printf("Failed to generate codepoints for the font.\n");
        CloseWindow();
        return 1;
    }

    // Load the font with our custom list of characters
    // file name, size 64 bits, codepoints, codepointCount
    const char *fontFile = "NotoSansDevanagari-VariableFont_wdth,wght.ttf";
    Font nepaliFont = LoadFontEx(fontFile, 64, codepoints, codepointCount);

    if (nepaliFont.texture.id == 0) {
        printf("Failed to load font: %s\n", fontFile);
        UnloadCodepoints(codepoints);
        CloseWindow();
        return 1;
    }

    // Main game loop, runs until user closes the window
    // Free the temporary codepoints array from memory now that the font is loaded
    UnloadCodepoints(codepoints);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Your First Nepali Numeral:", 50, 100, 20, LIGHTGRAY);

            // Draw the Nepali numeral using DrawTextEx
            Vector2 textPosition = { 350, 250 };
            // Added the u8 prefix here so Windows/GCC reads the Devanagari UTF-8 bytes properly:
            DrawTextEx(nepaliFont, u8"१", textPosition, 80, 2, WHITE);

        EndDrawing();
    }

    // Clean up
    UnloadFont(nepaliFont);
    CloseWindow();

    return 0;
}