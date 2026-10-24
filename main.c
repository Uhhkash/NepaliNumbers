#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


    void generateRandomNepaliNumber(char *buffer, size_t bufferSize) {
       // Array of Devanagari digits (each is a multi-byte UTF-8 string)
       // Because devanagari numbers cost 3 bytes of memory. We do an array of strings to iterate through safely. 
       //array of pointers meaning it points to a string literal. b
        const char *nepaliDigits[] = {"०", "१", "२", "३", "४", "५", "६", "७", "८", "९"};
        int numDigits = 1 + (rand() % 9);   // 1 to 9, will represent digit count of number

        buffer[0] = '\0';

        for(int i = 0; i  < numDigits; i++) {
            int randomDigit = (1 + rand() % 9);
            strcat(buffer, nepaliDigits[randomDigit]);
        }

    }

int main(void) {
    
    InitWindow(800, 600, "Nepali Number Typing Game");

    SetTargetFPS(60);
    

    // Tell Raylib which characters you want the font to support 
    // (including standard English text, numbers, and Nepali Devanagari numerals)
    const char *supportedChars = "०१२३४५६७८९abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int codepointCount = 0;
    //codepoints are the official integer number assigned to every unique character in Unicode
    //Raylib looks at the string of text and strips out all unique character and coverts them into an array of integer ID numbers
    // called codepoints
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

    srand(time(NULL)); // seed the randonm number generator


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