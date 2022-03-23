#include <stdbool.h>

#include "quantum.h"

#define TIC_TAC_TOE_LAYER 3

// Starts a new game
void initializeTicTacToe(void);

// Call this if the user selected the given field (1-9)
// Returns false if the move is not valid
bool makeMove(int field);

// Call this if the user selected the given field (KC_1 - KC_9)
// Returns false if the move is not valid
bool makeMoveKC(uint16_t keycode);
