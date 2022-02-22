#ifndef ABET_H
#define ABET_H
#include <Arduino.h>
#include "static_texture.h"
#include "progmemVar.h" 
#include "renderer.h"

struct letter {
  letter();
  letter(const char& i_letter, const vec2& i_pos);
  letter(uint8_t* i_customLetter, const vec2& i_pos);
  ~letter();

  void operator = (const letter& i_other);
  
  static_texture characters;
  vec2 m_pos;
  char m_letter;
};

struct Word{
  Word();
  Word(const char* i_string, const unsigned int& i_stringSize, const vec2& i_pos);
  ~Word();

  void operator = (const Word& i_cpy);
  letter operator[] (const int& i_index) const;

  letter* m_letters;
  vec2 m_pos;
  const char* m_wordString;
  unsigned int m_amountOfLetters;
};

class textManager {
public:
  textManager();
  ~textManager();

  void writeLetter(renderer* i_ren, const letter& i_letter);
  void writeWord(renderer* i_ren, const Word& i_word);
  void writeList(renderer* i_ren, Word* i_list, const unsigned int& i_listSize);
};

#endif
