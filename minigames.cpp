/*Minigames starting off with Minesweeper */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <windows.h>
using std::cout;
using std::endl;
using std::string;
using std::vector;

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
    const int KEY_LEFT = 75;
    const int KEY_RIGHT = 77;
#endif

//Color codes for terminal for Linux, MacOS, and modern Windows
#define RESET "\033[0m"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

bool gameIsRunning = false;

//Function to clear terminal screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    cout << "Press ENTER to return to the main menu." << endl;
    while (getKey() != KEY_ENTER);
}

void minesweeperEasy() {
    srand(time(0));
    clearScreen();
    Sleep(10);

    //10x10 board
    vector<string> board = {
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O",
        "O", "O", "O", "O", "O", "O", "O", "O", "O", "O"
    };

    // Default bomb values
    vector<int> spaceValues = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    //Assigns bombs to 10 random indexes
    for (int i = 0; i < 10; i++) {
        int bomb = rand() % 100;
        spaceValues[bomb] = 100;

        // Surrounding spaces gain 1 value
        if(bomb % 10 != 9) {
            spaceValues[bomb + 1] += 1;
            spaceValues[bomb + 11] += 1;
            spaceValues[bomb - 9] += 1;

        }
        if(bomb % 10 != 0) {
            spaceValues[bomb - 1] += 1;
            spaceValues[bomb - 11] += 1;
            spaceValues[bomb + 9] += 1;
        }
        spaceValues[bomb + 10] += 1;
        spaceValues[bomb - 10] += 1;
        
    }
    
    bool playingMinesweeper = true;
    int currentSpace = 0;
    string message = "";
    board.at(0) = YELLOW + board.at(0) + RESET;

    while(playingMinesweeper == true) {
        Sleep(10);
        clearScreen();

        int spacesInRow = 0;
        cout << currentSpace << endl;
        
        for (int i = 0; i < 100; i++) {
            // Displays the board with 10 spaces in a row
            if (spacesInRow != 9) {
                cout << board[i] << " ";
                spacesInRow += 1;
            }
            else if (spacesInRow == 9) {
                cout << board[i] << endl;
                spacesInRow = 0;
            }
        }
        cout << message << endl;

        int key = getKey();
    
        // Handle Windows Arrow Key Escape Codes
        #if defined(_WIN32) || defined(_WIN64)
        if (key == 0 || key == 224) { // Arrow keys prefix
        key = getKey(); // Get the actual arrow key code
        }
        #endif

        if (message != "Illegal Move") {
            board.at(currentSpace) = WHITE + board.at(currentSpace) + RESET;
        }
        if (key == KEY_UP){
            if (currentSpace > 9) {
                currentSpace -= 10;
                board.at(currentSpace) = YELLOW + board.at(currentSpace) + RESET;
                message = "";
            }
            else {
                message = "Illegal Move";
            }
        }
        else if (key == KEY_DOWN) {
            if (currentSpace < 89) {
                currentSpace += 10;
                board.at(currentSpace) = YELLOW + board.at(currentSpace) + RESET;
                message = "";
            }
            else {
                message = "Illegal Move";
            }
        }
        else if (key == KEY_LEFT) {
            if (currentSpace % 10 != 0) {
                currentSpace -= 1;
                board.at(currentSpace) = YELLOW + board.at(currentSpace) + RESET;                
                message = "";
            }
            else {
                message = "Illegal Move";
            }
        }
        else if (key == KEY_RIGHT) {
            if (currentSpace % 10 != 9) {
                board.at(currentSpace) = YELLOW + board.at(currentSpace) + RESET;
                currentSpace += 1;
                message = "";
            }
            else {
                message = "Illegal Move";
            }
        }
        else if (key == KEY_ENTER) {
            string revealedSpace = std::to_string(spaceValues[currentSpace]);
            int surroundingSpace = spaceValues[currentSpace + surroundingSpace];
            board.at(currentSpace) = revealedSpace;
            board.at(currentSpace) = GREEN + board.at(currentSpace) + RESET;

            if (spaceValues[currentSpace] == 0) {
                // Reveal surrounding spaces
                if(currentSpace % 10 != 9) {
                    board.at(currentSpace + 1) = std::to_string(spaceValues[currentSpace + 1]);
                    if (spaceValues[currentSpace + 1] == 0)
                    board.at(currentSpace + 1) = GREEN + board.at(currentSpace + 1) + RESET;
                    board.at(currentSpace + 11) = std::to_string(spaceValues[currentSpace + 11]);
                    board.at(currentSpace + 11) = GREEN + board.at(currentSpace + 11) + RESET;
                    board.at(currentSpace - 9) = std::to_string(spaceValues[currentSpace - 9]);
                    board.at(currentSpace - 9) = GREEN + board.at(currentSpace - 9) + RESET;
                }
                if(currentSpace % 10 != 0) {
                    board.at(currentSpace - 1) = std::to_string(spaceValues[currentSpace - 1]);
                    board.at(currentSpace - 1) = GREEN + board.at(currentSpace - 1) + RESET;
                    board.at(currentSpace - 11) = std::to_string(spaceValues[currentSpace - 11]);
                    board.at(currentSpace - 11) = GREEN + board.at(currentSpace - 11) + RESET;
                    board.at(currentSpace + 9) = std::to_string(spaceValues[currentSpace + 9]);
                    board.at(currentSpace + 9) = GREEN + board.at(currentSpace + 9) + RESET;
                }
                board.at(currentSpace + 10) = std::to_string(spaceValues[currentSpace + 10]);
                board.at(currentSpace + 10) = GREEN + board.at(currentSpace + 10) + RESET;
                board.at(currentSpace - 10) = std::to_string(spaceValues[currentSpace - 10]);
                board.at(currentSpace - 10) = GREEN + board.at(currentSpace - 10) + RESET;
            }
            else if (spaceValues[currentSpace] == 100){
                clearScreen();
                playingMinesweeper = false;
                spacesInRow = 0;
                for (int i = 0; i < 100; i++) {
                    if (spacesInRow != 9) {
                        cout << spaceValues[i] << " ";
                        spacesInRow += 1;
                    }
                    else if (spacesInRow == 9) {
                        cout << spaceValues[i] << endl;
                    }
                }
            gameIsRunning = false;
            waitForEnter();
            }
        }
    }
}

int main() {
    initTerminal();

    vector<string> options = {
        "          PLAY          ",
        "        SETTINGS        ",
        "          EXIT          "
    };

    int currentSelection = 0;
    bool running = true;

    while (running){
        if (gameIsRunning == false){
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
                if (currentSelection == 0) {
                        // Start Game
                        clearScreen();
                        cout << "=== STARTING MINESWEEPER ===" << endl;
                        Sleep(1000); // Simulate game loading
                        gameIsRunning = true;
                        minesweeperEasy();
                }
                else if (currentSelection == 1) {
                        // Settings
                        clearScreen();
                        cout << "=== SETTINGS ===\nAudio: [ON]" << endl;
                        waitForEnter();
                }
                else if (currentSelection == 2) {
                        // Exit
                        running = false;
                }
            }
        }
    }

        clearScreen();
        cout << "Exiting Minigames. Goodbye!" << endl;
        resetTerminal();
        return 0;
}