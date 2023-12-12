#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <sstream>

#define MAX_WORD_LENGTH 100
#define MAX_WRONG_GUESSES 5
#define NUMBER_OF_STAGES 5
#define WORDS_PER_STAGE 10
void outtextxy_int(int x, int y, int value) 
{
    char num_str[10];
    sprintf(num_str, "%d", value);
    outtextxy(x, y, num_str);
}
void drawHangman(int wrongGuesses) 
{
    int headX = 200, headY = 100, headRadius = 30;
    int bodyStartY = headY + headRadius, bodyEndY = bodyStartY + 100;
    int armStartY = bodyStartY + 30, armEndY = armStartY + 50;
    int legStartY = bodyEndY, legEndY = legStartY + 50;

    line(150, 50, 150, 300); 
    line(150, 50, 200, 50); 
    line(200, 50, 200, 70); 

    if (wrongGuesses >= 1) {

        circle(headX, headY, headRadius);
    }
    if (wrongGuesses >= 2) {
        line(headX, bodyStartY, headX, bodyEndY);
    }
    if (wrongGuesses >= 3) {
        line(headX, armStartY, headX - 30, armEndY); 
        line(headX, armStartY, headX + 30, armEndY); 
    }
    if (wrongGuesses >= 4) {
        line(headX, legStartY, headX - 30, legEndY);
        line(headX, legStartY, headX + 30, legEndY); 
    }
    if (wrongGuesses >= 5) {
        line(188, 90, 192, 86);
        line(192, 90, 188, 86);

        line(208, 90, 212, 86);
        line(212, 90, 208, 86);
    }
}

void initializeWord(const char *word, char *hiddenWord) 
{
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        hiddenWord[i] = '_';
    }
    hiddenWord[len] = '\0';
}
void getInputFromGraphicsWindow(char *input, int maxLen) 
{
    int index = 0;
    char str[2] = "\0"; 
    while (index < maxLen - 1) {
        char ch = getch();
        if (ch == 13) { 
            break; 
        } else if (ch == 8) { 
            if (index > 0) 
            { 
                index--; 
                input[index] = '\0'; 
                outtextxy(10 + textwidth(input), 100, "  ");
            }
        } else 
            { 
            input[index++] = ch; 
            input[index] = '\0'; 
            str[0] = ch; 
            outtextxy(10 + textwidth(input) - textwidth(str), 100, str); 
            }
    }
    input[index] = '\0'; 
}
void updateHiddenWord(const char *word, char *hiddenWord, char guess) 
{
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (word[i] == guess) {
            hiddenWord[i] = guess;
        }
    }
}

char toLowercase(char c) 
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}


void displayMenuAndGetChoice(int &choice) 
{
    char menuText[10][1000] = {
        "Menu:",
        "1. Multiplayer",
        "2. Single Player",
        "3. Rules",
        "4. Quit"
    };
    
    cleardevice();
    for (int i = 0; i < 5; i++) {
        outtextxy(10, 10 + i * 15, menuText[i]);
    }

    char strChoice[3] = {0};
    outtextxy(10, 85, menuText[5]);


    do {
        char ch = getch(); 
        if (ch >= '1' && ch <= '4') { 
            strChoice[0] = ch;
            strChoice[1] = '\0'; 
            outtextxy(220, 85, strChoice); 
            choice = ch - '0'; 
            break; 
        }
    } while (true);
}

int main() 
{
    const char *stageWords[NUMBER_OF_STAGES][WORDS_PER_STAGE] = {
        {"Glock", "Iarna", "Mandarine"},
        {"AK", "Draco", "AR"},
        {"Slaughter", "NLE", "Ice"},
        {"Gang", "Rap", "Sea", "music", "Savage", "Baby", "Snow"},
        {"Brixton", "Boston", "New-York", "Atlanta"}
    };
    int choice;
    char  word[MAX_WORD_LENGTH],hiddenWord[MAX_WORD_LENGTH],hiddenWordDisplay[100];
    int stage = 0;
    char guess;
    int wrongGuesses;
int gd = DETECT, gm;
initgraph(&gd, &gm, "path to the BGI folder");
    srand(time(NULL));

    do {
        displayMenuAndGetChoice(choice);
        switch (choice) {
            case 1:
                { cleardevice(); 
        outtextxy(10, 10, "Enter a word: ");

        getInputFromGraphicsWindow(word, MAX_WORD_LENGTH);

        initializeWord(word, hiddenWord);
        wrongGuesses = 0;

        while (wrongGuesses < MAX_WRONG_GUESSES) {
            cleardevice();

            strcpy(hiddenWordDisplay, "Hidden word: ");
            strcat(hiddenWordDisplay, hiddenWord);
            outtextxy(10, 30, hiddenWordDisplay);

            drawHangman(wrongGuesses);

            outtextxy(10, 50, "Enter your guess: ");
            guess = getch();
            guess = toLowercase(guess);

            if (strchr(word, guess) != NULL) {
                updateHiddenWord(word, hiddenWord, guess);
                if (strcmp(word, hiddenWord) == 0) 
                {
                    strcpy(hiddenWordDisplay, "Hidden word: ");
                    strcat(hiddenWordDisplay, hiddenWord);
                    outtextxy(10, 30, hiddenWordDisplay);
                    outtextxy(10, 70, "Congratulations!");
                    getch();
                    break;
                }
            } else {
                wrongGuesses++;
            }
        }

        if (wrongGuesses == MAX_WRONG_GUESSES) {
            drawHangman(wrongGuesses);
            outtextxy(10, 70, "Game over!");
            getch();

            wrongGuesses = 0;
        }
        break;}

                      

            case 2:
{
srand(time(NULL));
stage=0;
while (stage < NUMBER_OF_STAGES) {
    cleardevice();
    const char *word = stageWords[stage][rand() % WORDS_PER_STAGE];
    initializeWord(word, hiddenWord);
    wrongGuesses = 0;

    while (wrongGuesses < MAX_WRONG_GUESSES) {
        cleardevice();


        char stageDisplay[MAX_WORD_LENGTH];
        sprintf(stageDisplay, "Stage: %d", stage + 1);
        outtextxy(10, 10, stageDisplay);


        char hiddenWordDisplay[MAX_WORD_LENGTH * 2];
        strcpy(hiddenWordDisplay, "Hidden word: ");
        strcat(hiddenWordDisplay, hiddenWord);
        outtextxy(10, 30, hiddenWordDisplay);

        drawHangman(wrongGuesses);

        outtextxy(10, 50, "Enter your guess: ");
        guess = getch();
        guess = toLowercase(guess);

        if (strchr(word, guess) != NULL) {
            updateHiddenWord(word, hiddenWord, guess);
            if (strcmp(word, hiddenWord) == 0) {
            	strcpy(hiddenWordDisplay, "Hidden word: ");
            strcat(hiddenWordDisplay, hiddenWord);
                	outtextxy(10, 30, hiddenWordDisplay);
                outtextxy(10, 70, "Correct!");
                getch();
                break;
            }
        } else {
            wrongGuesses++;
        }
    }

    if (wrongGuesses == MAX_WRONG_GUESSES) {
        drawHangman(wrongGuesses);
        char gameOverMsg[MAX_WORD_LENGTH * 2];
        strcpy(gameOverMsg, "Game over! ");
     
        outtextxy(10, 70, gameOverMsg);
        getch();
        break;
    } else {
        stage++;
    }

    if (stage == NUMBER_OF_STAGES) {
        outtextxy(10, 90, "Congratulations!");
        outtextxy(10, 110, "You won!");
        getch();
        stage = 0;
    }
} break;}



            case 3:
            {
			
               cleardevice(); 

outtextxy(10, 10, "Rules of the Game:");

outtextxy(10, 30, "1. Objective: Guess the hidden word by suggesting letters within a limited number of guesses.");
outtextxy(10, 50, "2. Game Modes:");
outtextxy(30, 90, "- Single Player: Guess a word randomly chosen from a list.");
outtextxy(30, 70, "- Multiplayer: One player enters a word, another guesses it.");
outtextxy(10, 110, "3. Gameplay:");
outtextxy(30, 130, "- The hidden word is represented by underscores.");
outtextxy(30, 150, "- Each turn, suggest a letter.");
outtextxy(30, 170, "- Correct guesses reveal the letter(s) in the word.");
outtextxy(30, 190, "- Incorrect guesses count against your guess limit.");
outtextxy(10, 210, "4. Guesses:");
outtextxy(30, 230, "- Maximum of 5 wrong guesses allowed per word.");
outtextxy(10, 250, "5. Winning and Losing:");
outtextxy(30, 270, "- Correctly guess the word to win or advance to the next stage (Single Player).");
outtextxy(30, 290, "- Exceeding the wrong guess limit means a loss. In Single Player, you restart from stage 1.");
outtextxy(10, 310, "6. Letter Case: The game is not case-sensitive.");
outtextxy(10, 330, "7. Exiting: Select 'Quit' from the main menu to exit the game.");

getch();}

            case 4:
               {
				 printf("Exiting the game.\n");
                break;
}
            default:
                printf("Invalid choice. Enter a number between 1 and 4.\n");
        }
    } while (choice != 4); 
 closegraph();
    return 0;
}
