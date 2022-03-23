# qmk_tictactoe
Play Tic-tac-toe on your keyboard, against your keyboard!

This is an implementation of Tic-tac-toe that can run on any qmk based keyboard.
You can play against your keyboard in any text editor of your choice.
Just enter the Tic-tac-toe layer and select your move by pressing 1 to 9.

Tested on an Ergodox.

## Demo
![tictactoe_demo](https://user-images.githubusercontent.com/6650260/159787140-e78bfc20-88a7-41c3-89d6-690883fadb16.gif)

## How to include into your keymap
1. Copy `tictactoe.c` and `tictactoe.h` into the same directory as your `keymap.c`
2. Add `SRC += tictactoe.c` to your `rules.mk`
3. Optionally add `#define USB_POLLING_INTERVAL_MS 5` to your `config.h` to speed up the keypresses

Make the following changes to your `keymap.c`:
1. Add `#include "tictactoe.h"`
2. Add a new layer that contains `KC_1` to `KC_9` and a key to switch away from this layer
3. Add a mapping to switch to the new layer. I.e. `TG(TIC_TAC_TOE_LAYER)`
4. Adjust `TIC_TAC_TOE_LAYER` in `tictactoe.h` to the new layer number
5. Add the following code at the start of `process_record_user`:
  ```c
  if (layer_state_is(TIC_TAC_TOE_LAYER) && record->event.pressed) {
    makeMoveKC(keycode);
    return false;
  }
  ```
5. Add the follwoing code at the start of `layer_state_set_user`:
  ```c
  if (IS_LAYER_ON_STATE(state, TIC_TAC_TOE_LAYER)) {
    initializeTicTacToe();
  }
  ```
  
Done! Switching to the new Tic-tac-toe layer should start the game.
