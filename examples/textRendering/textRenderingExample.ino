#include "128X64_renderer.h"

void setup() {
  renderer ren;
  ren.begin(0x3c);

  pinMode(42, INPUT);

  textManager screenText;

  /*
  The Alphabet.h include contains everything needed for text rendering.
  A character sprites/bitmaps are stored in PROGMEM and are read into RAM upon letter or Word creation.
  Only capital letters and dashes are supported, all sprites/bitmaps are an array of 5 uint8_t, you can create a letter with a custom sprite.
  The textManager class controls all text rendering
  */
  Word title("HELLO-WORLD", 11, {1.0f, 1.0f}); // create the word HELLO-WORLD which is 11 characters in size and render it at 1, 1

  letter dash('-', {1.0f, 8.0f}); // create a letter at 1, 8

  Word list[3] = { // create a list of words
    Word("-ITEM-A", 7, {1.0f, 15.0f}),
    Word("-ITEM-B", 7, {1.0f, 21.0f}),
    Word("-ITEM-C", 7, {1.0f, 28.0f})
  };

  letter A('A', {50.0f, 50.0f});

  while(1){
    ren.frameBegin();

    ren.preRender();
    screenText.writeLetter(&ren, dash);
    screenText.writeWord(&ren, title);
    screenText.writeList(&ren, list, 3);
    if(digitalRead(42)){
      screenText.writeLetter(&ren, A);
    }
    ren.render();

    ren.frameEnd();
  }

}

void loop() {
  

}