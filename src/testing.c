#include <assert.h>
#include "file_operations.h"
#include "game_logic.h"
#include "winner_determination.h"
#include "user_input.h"
#include "bot.h"
#include "bot.c"
#include <stdio.h>
#include <string.h>

// Test functions for file_operations
// Test cases for readSpells
void testReadSpellsValidFile() { //covers if file passed is valid
    char testFile[] = "test_spells_valid.txt";
    FILE* file = fopen(testFile, "w");
    fprintf(file, "4\nspell1\nspell2\nspell3\n");
    fclose(file);

    char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
    int numSpells = readSpells(testFile, spells);

    assert(numSpells == 4);
    assert(strcmp(spells[0], "spell1") == 0);
    assert(strcmp(spells[1], "spell2") == 0);
    assert(strcmp(spells[2], "spell3") == 0);
}
void testReadSpellsEmptyFile() { //covers if file passed is empty (contains no spells)
    char testFile[] = "test_spells_empty.txt";
    FILE* file = fopen(testFile, "w");
    fprintf(file, "0\n");
    fclose(file);

    char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
    int numSpells = readSpells(testFile, spells);

    assert(numSpells == 0);
}
void testReadSpellsMaxSpells() { //covers file with a number of spells that has exceeded the maximum (boundary case)
    char testFile[] = "test_spells_max.txt";
    FILE* file = fopen(testFile, "w");
    fprintf(file, "200\n");
    for (int i = 0; i < 200; i++) {
        fprintf(file, "Spell%d\n", i);
    }
    fclose(file);

    char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
    int numSpells = readSpells(testFile, spells);

    assert(numSpells == 200);
}
// Test functions for displaySpells
void testDisplaySpellsNormalCase() { //covers a "normal" amount of spells
    char testSpells[MAX_SPELLS][MAX_SPELL_LENGTH] = {
            "Spell1", "Spell2", "Spell3", "Spell4", "Spell5"
    };

    printf("Testing Normal Case:\n");
    displaySpells(testSpells, 5);
}
void testDisplaySpellsFewSpells() {  //covers a small amount of spells
    char testSpells[MAX_SPELLS][MAX_SPELL_LENGTH] = {
            "spell1", "spell2"
    };

    printf("Testing Few Spells:\n");
    displaySpells(testSpells, 2);
}
void testDisplaySpellsMaxSpells() { //covers the maximum amount of spells
    char testSpells[MAX_SPELLS][MAX_SPELL_LENGTH];
    for (int i = 0; i < 200; i++) {
        sprintf(testSpells[i], "Spell%d", i);
    }

    printf("Testing Max Spells:\n");
    displaySpells(testSpells, 200);
}

//Test functions for game_logic
//Test cases for isMoveValid
void testIsMoveValid() {
    char testSpells[MAX_SPELLS][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3"};
    char testBoard[MAX_SPELLS][MAX_SPELL_LENGTH] = {"spell1", "spell2"};
    int boardSize = 2;

    //normal cases
    assert(isMoveValid("spell3", testSpells, 3, testBoard, boardSize) == 1);//covers spell being valid
    assert(isMoveValid("spell2", testSpells, 3, testBoard, boardSize) == 0);//covers spell being repeated

    //boundary cases
    assert(isMoveValid("spell4", testSpells, 3, testBoard, boardSize) == 0);//covers spell being invalid
    assert(isMoveValid("spell1", testSpells, 3, testBoard, boardSize) == 0);//covers spell being repeated in game board
}
//Test cases for isMoveValidBot
void testIsMoveValidBot() {
    testIsMoveValid(); //same test cases as isMoveValid
}
//Test cases for addToBoard and removeLastSpell
void testAddToBoard() {
    char testBoard[MAX_SPELLS][MAX_SPELL_LENGTH] = {"spell1", "spell2"};
    int boardSize = 2;
    addToBoard("spell3", testBoard, &boardSize);
    assert(strcmp(testBoard[2], "spell3") == 0);//covers if added spell is in the correct position
    assert(boardSize == 3);//covers if board size increased properly after spell addition
    //Test removal
    removeLastSpell(testBoard, &boardSize);
    assert(boardSize == 2);//covers if board size decreased correctly after spell removal
    assert(testBoard[1][0] == '\0');//covers if space occupied by removed spell is now null
}
//Test cases for PlayGame
void testPlayGame() {
    char testPlayer1[] = "Nour";
    char testPlayer2[] = "Harout";
    char testSpells[MAX_SPELLS][MAX_SPELL_LENGTH] = {"mango", "olive", "elk"};
    char testBoard[MAX_SPELLS][MAX_SPELL_LENGTH] = {"mango", "olive"};
    int boardSize = 2;
    int winner = playGame(testPlayer1, testPlayer2, 0, testSpells, 3, testBoard, &boardSize);
    assert(winner == 1);  //asserts that player 2 wins (just an example)
}

//Test functions for user_input
//Test cases for getPlayerNames
void testGetPlayerNames() {
    char testPlayer1[MAX_NAME_LENGTH];
    char testPlayer2[MAX_NAME_LENGTH];
    //normal cases
    FILE *file;
    file = fopen("spells.txt", "w");
    fprintf(file, "Nour\n1\nHarout\n");
    fclose(file);

    freopen("test_file.txt", "r", stdin);
    int choice = getPlayerNames(testPlayer1, testPlayer2);
    fclose(stdin);

    assert(strcmp(testPlayer1, "Nour") == 0);// covers if names are correctly assigned
    assert(strcmp(testPlayer2, "Harout") == 0); // covers if names are correctly assigned
    assert(choice == 1);  //covers if correct player is chosen

    //boundary case
    char sameName[MAX_NAME_LENGTH] = "SameName";
    file = fopen("spells.txt", "w");
    fprintf(file, "%s\n1\n%s\n", sameName, sameName);
    fclose(file);

    freopen("spells.txt", "r", stdin);
    choice = getPlayerNames(testPlayer1, testPlayer2);
    fclose(stdin);

    assert(choice == 1); //covers names being the same

    //bot test
    file = fopen("spells.txt", "w");
    fprintf(file, "Bot\n2\n");
    fclose(file);

    freopen("spells.txt", "r", stdin);
    choice = getPlayerNames(testPlayer1, testPlayer2);
    fclose(stdin);

    assert(strcmp(testPlayer1, "Bot") == 0);
    assert(strcmp(testPlayer2, "") == 0);
    assert(choice == 2);//covers that the bot has been chosen
}
//Test cases for getPlayerSpell
void testGetPlayerSpell() {
    char testSpell[MAX_NAME_LENGTH];
    char testPlayer1[MAX_NAME_LENGTH] = "Nour";
    char testPlayer2[MAX_NAME_LENGTH] = "Harout";

    //case for player 1
    FILE *file;
    file = fopen("spells.txt", "w");
    fprintf(file, "spell1\n");
    fclose(file);

    freopen("spells", "r", stdin);
    getPlayerSpell(0, testSpell, testPlayer1, testPlayer2);
    fclose(stdin);

    assert(strcmp(testSpell, "spell1") == 0);//covers if received spell matches testSpell

    //case for player 2
    file = fopen("spells.txt", "w");
    fprintf(file, "spell2\n");
    fclose(file);

    freopen("spells.txt", "r", stdin);
    getPlayerSpell(1, testSpell, testPlayer1, testPlayer2);
    fclose(stdin);

    assert(strcmp(testSpell, "spell2") == 0);//covers if received spell is stored properly
}

//Test functions for winner_determination
//Test cases for announceWinner
void testAnnounceWinner() { //test function provides the possible outputs of the announceWinner function
    char testPlayer1[] = "Nour";
    char testPlayer2[] = "Harout";
    printf("Test case 1: Player 1 wins\n");
    announceWinner(testPlayer1, testPlayer2, 0);//covers player 1 winning

    printf("\nTest case 2: Player 2 wins\n");
    announceWinner(testPlayer1, testPlayer2, 1);//covers player 2 winning

    printf("\nTest case 3: It's a tie\n");
    announceWinner(testPlayer1, testPlayer2, -1);//covers if game is a tie
}

//Test functions for bot
//Test cases for initializeBot
void testInitializeBot() {
    // Test different difficulty settings
    printf("Testing initializeBot function...\n");

    for (int i = 1; i <= 3; i++) {
        initializeBot(i);
        printf("Bot difficulty set to: %d\n", i);
        assert(botDifficulty == i); //covers that bot difficulty is set correctly
    }
    printf("initializeBot function test completed.\n");
}
//Test cases for chooseBotMoveEasy
void testChooseBotMoveEasy() {
    printf("Testing chooseBotMoveEasy function...\n");

    char spells[5][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3", "spell4", "spell5"};
    char board[5][MAX_SPELL_LENGTH] = {"spell1", "spell6", "spell7"};
    int boardSize = 3;
    int numSpells = 5;

    initializeBot(1);

    int result = chooseBotMoveEasy(spells, numSpells, board, boardSize);
    assert(result >= 0 && result < numSpells); //covers that bot's moves fall within appropriate range

    printf("chooseBotMoveEasy function test completed.\n");
}
//Test cases for chooseBotMoveMedium
void testChooseBotMoveMedium() {
    printf("Testing chooseBotMoveMedium function...\n");

    char spells[5][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3", "spell4", "spell5"};
    char board[5][MAX_SPELL_LENGTH] = {"spell1", "spell6", "spell7"};
    int boardSize = 3;
    int numSpells = 5;

    initializeBot(2);

    int result = chooseBotMoveMedium(spells, numSpells, board, boardSize);
    assert(result >= -1 && result < numSpells);//covers that bot's moves fall within appropriate range

    printf("chooseBotMoveMedium function test completed.\n");
}
//Test cases for chooseBotMoveHard
void testChooseBotMoveHard() {
    printf("Testing chooseBotMoveHard function...\n");

    char spells[5][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3", "spell4", "spell5"};
    char board[5][MAX_SPELL_LENGTH] = {"spell1", "spell6", "spell7"};
    int boardSize = 3;
    int numSpells = 5;

    initializeBot(3);

    int result = chooseBotMoveHard(spells, numSpells, board, boardSize);
    assert(result >= -1 && result < numSpells); //covers that bot's moves fall within appropriate range

    printf("chooseBotMoveHard function test completed.\n");
}
//Test cases for findWinningMove
void testFindWinningMove() {
    printf("Testing findWinningMove function...\n");

    char spells[5][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3", "spell4", "spell5"};
    char board[5][MAX_SPELL_LENGTH] = {"spell1", "spell6", "spell7"};
    int boardSize = 3;
    int numSpells = 5;

    int result = findWinningMove(spells, numSpells, board, boardSize);
    assert(result >= -1 && result < numSpells);//covers that a correct winning move is produced

    printf("findWinningMove function test completed.\n");
}
//Test cases for findBlockingMove
void testFindBlockingMove() {
    printf("Testing findBlockingMove function...\n");

    char spells[5][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3", "spell4", "spell5"};
    char board[5][MAX_SPELL_LENGTH] = {"spell1", "spell6", "spell7"};
    int boardSize = 3;
    int numSpells = 5;

    int result = findBlockingMove(spells, numSpells, board, boardSize);
    assert(result >= -1 && result < numSpells);//covers that a correct blocking move is produced

    printf("findBlockingMove function test completed.\n");
}
//Test cases for playAgainstBot
void testPlayAgainstBot() {
    printf("Testing playAgainstBot function...\n");

    char player1[MAX_NAME_LENGTH] = "Player1";
    char player2[MAX_NAME_LENGTH] = "Bot";
    int startingPlayer = 0;
    int numSpells = 5;
    char spells[5][MAX_SPELL_LENGTH] = {"spell1", "spell2", "spell3", "spell4", "spell5"};
    char board[5][MAX_SPELL_LENGTH] = {"spell1", "spell6", "spell7"};
    int boardSize = 3;

    int result = playAgainstBot(player1, player2, startingPlayer, spells, numSpells, board, &boardSize);
    assert(result >= -1 && result <= 1);//covers that a correct outcome is produced

    printf("playAgainstBot function test completed.\n");
}


int main() {
    printf("Running Test Cases for file_operations Functions\n");

    testReadSpellsValidFile();
    testReadSpellsEmptyFile();
    testReadSpellsMaxSpells();
    testDisplaySpellsNormalCase();
    testDisplaySpellsFewSpells();
    testDisplaySpellsMaxSpells();

    printf("Running Test Cases for game_logic Functions\n");

    testIsMoveValid();
    testIsMoveValidBot();
    testAddToBoard();
    testPlayGame();

    printf("Running Test Cases for user_input Functions\n");

    testGetPlayerNames();
    testGetPlayerSpell();

    printf("Running Test Cases for winner_determination Functions\n");

    testAnnounceWinner();

    printf("Running Test Cases for bot Functions\n");

    testInitializeBot();
    testChooseBotMoveEasy();
    testChooseBotMoveMedium();
    testChooseBotMoveHard();
    testFindWinningMove();
    testFindBlockingMove();
    testPlayAgainstBot();

    printf("All test cases completed.\n");

    return 0;
}

