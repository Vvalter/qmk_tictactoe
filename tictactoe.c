#include "tictactoe.h"

static char board[] = {
  '1', '2', '3',
  '4', '5', '6',
  '7', '8', '9'
};
static const char* line_separator = "+-+-+-+\n";
static const char* prompt = "Your turn: ";

static void startOver(void) {
  for (int i = 0; i < 9; i++) {
    board[i] = '1' + i;
  }
};

static void printBoard(void) {
  send_string(line_separator);
  for (int i = 0; i < 9; i++)
  {
    if (i % 3 == 0 && i > 0)
    {
      send_string("|\n");
      send_string(line_separator);
    }
    send_string("|");
    const char buf[] = {board[i], '\0'};
    send_string(buf);
  }
  send_string("|\n");
  send_string(line_separator);
}

static void clearScreen(void) {
  const int charsToDelete = 7 /* lines */ * 8 /* line length */ + strlen(prompt);

  for (int i = 0; i < charsToDelete; ++i) {
      send_string(SS_TAP(X_BSPACE));
  }
}

static bool won(char c)
{
  for (int i = 0; i < 3; i++) {
    bool row = true;
    bool col = true;
    for (int j = 0; j < 3; j++) {
      if (board[i*3 + j] != c) {
        row = false;
      }
      if (board[i + j * 3] != c) {
        col = false;
      }
    }
    if (row || col) {
      return true;
    }
  }

  if (board[0] == c && board[4] == c && board[8] == c)
  {
    return true;
  }

  if (board[2] == c && board[4] == c && board[6] == c)
  {
    return true;
  }

  return false;
}

bool makeMoveKC(uint16_t keycode) {
    switch (keycode) {
      case KC_1:
        return makeMove(1);
      case KC_2:
        return makeMove(2);
      case KC_3:
        return makeMove(3);
      case KC_4:
        return makeMove(4);
      case KC_5:
        return makeMove(5);
      case KC_6:
        return makeMove(6);
      case KC_7:
        return makeMove(7);
      case KC_8:
        return makeMove(8);
      case KC_9:
        return makeMove(9);
    }
    return false;
}

bool makeMove(int field) {
  if (field < 1 || field > 9) {
    return false;
  }

  if (board[field - 1] == 'X' || board[field - 1] == 'O') {
    return false;
  }

  board[field - 1] = 'X';
  if (won('X'))
  {
    clearScreen();
    printBoard();
    SEND_STRING("You won!\n");
    startOver();
    layer_off(TIC_TAC_TOE_LAYER);
    return true;
  }

  int free_field = -1;
  bool played = false;
  for (int i = 0; i < 9; i++)
  {
    if (board[i] != 'X' && board[i] != 'O')
    {
      free_field = i;
      char save = board[i];
      board[i] = 'O';
      if (won('O'))
      {
        board[i] = 'O';
        played = true;
        break;
      }
      board[i] = save;
    }
  }
  if (!played) {
    for (int i = 0; i < 9; i++)
    {
      if (board[i] != 'X' && board[i] != 'O')
      {
        char save = board[i];
        board[i] = 'X';
        if (won('X'))
        {
          board[i] = 'O';
          played = true;
          break;
        }
        board[i] = save;
      }
    }
  }

  if (!played && free_field != -1) {
    board[free_field] = 'O';
  }

  if (won('O'))
  {
    clearScreen();
    printBoard();
    SEND_STRING("You lost!\n");
    startOver();
    layer_off(TIC_TAC_TOE_LAYER);
    return true;
  }

  if (free_field == -1) {
    clearScreen();
    printBoard();
    SEND_STRING("It's a tie...\n");
    startOver();
    layer_off(TIC_TAC_TOE_LAYER);
    return true;
  }

  clearScreen();
  printBoard();

  send_string(prompt);
  return true;
}

void initializeTicTacToe(void) {
  SEND_STRING("Welcome to TicTacToe!\n");
  printBoard();
  send_string(prompt);
}
