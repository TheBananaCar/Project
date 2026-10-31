/*Minigames starting off with Minesweeper */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <windows.h>
using namespace std;

// Key reading
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    void initTerminal(){}
    void resetTerminal(){}
    char getKey(){
        return _getch();
    }

    // Windows key codes
    const int KEY_UP = 72;
    const int KEY_DOWN = 80;
    const int KEY_ENTER = 13;
#endif

//Function to clear terminal screen
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter(){
    cout << "Press ENTER to return to the main menu." << endl;
    while (getKey() != KEY_ENTER);
}

void minesweeperEasy(){
    clearScreen();
    cout << "  |  |  |  |  |  |  |  " << endl;
    cout << "  |  |  |  |  |  |  |  " << endl;
    cout << "-----------------------" << endl;

}

int main() {
    initTerminal();

    vector<string> options = {
        "          PLAY          ",
        "        SETTINGS        ",
        "          EXIT          "
    };

    int currentSelection = 0;
    int running = true;

    while (running){
        clearScreen();

        // Display menu
        cout << "============================" << endl;
        cout << "            MENU            " << endl;
        cout << "============================" << endl;

        // Render buttons
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == currentSelection) {
                cout << "> " << options[i] << " <" << endl;
            } else {
                cout << "  " << options[i] << endl;
            }
        }

        cout << "============================" << endl;
        #if defined(_WIN32) || defined(_WIN64)
            cout << endl;
            cout << " Use Arrow Keys to navigate and ENTER to select." << endl;
        #endif

        // Read user input
        int key = getKey();

        // Handle Windows Arrow Key Escape Codes
        #if defined(_WIN32) || defined(_WIN64)
            if (key == 0 || key == 224) { // Arrow keys prefix
                key = getKey(); // Get the actual arrow key code
            }
        #endif

        // Navigation logic
        if (key == KEY_UP) {
            currentSelection = (currentSelection - 1 + options.size()) % options.size();
        }
        else if (key == KEY_DOWN) {
            currentSelection = (currentSelection + 1) % options.size();
        }
        else if (key == KEY_ENTER) {
            switch (currentSelection) {
                case 0:
                    // Start Game
                    clearScreen();
                    cout << "=== STARTING MINESWEEPER ===" << endl;
                    Sleep(1000); // Simulate game loading
                    minesweeperEasy();
                    break;
                case 1:
                    // Settings
                    clearScreen();
                    cout << "=== SETTINGS ===\nAudio: [ON]" << endl;
                    waitForEnter();
                    break;
                case 2:
                    // Exit
                    running = false;
                    break;
            }
        }
    }

    clearScreen();
    cout << "Exiting Minigames. Goodbye!" << endl;
    resetTerminal();
    return 0;
}