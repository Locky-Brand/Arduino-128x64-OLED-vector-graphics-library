#include "Alphabet.h"

// ==============letter===================
letter::letter() : m_pos({1, 1}), m_letter('e') {
    
}
letter::letter(const char& i_letter, const vec2& i_pos) : m_letter(i_letter) {
  m_pos = (vec2){i_pos.x, i_pos.y};
  int base = i_letter - 65;
  int letterIndex = base * 5;
  for(int i = letterIndex; i < (letterIndex + 5); ++i){
    characters.getBitMap()[i - letterIndex] = pgm_read_byte(FLASHMEM::Alphabet + i);
  }
  characters.constructLetterBMP(static_texture(m_pos, 5, 8));
}
letter::letter(uint8_t* i_customLetter, const vec2& i_pos){
  for(int i = 0; i < 5; ++i){
    characters.getBitMap()[i] = i_customLetter[i];
  }
  characters.constructLetterBMP(static_texture(i_pos, 5, 8));
}
void letter::operator = (const letter& i_other) {
  m_letter = i_other.m_letter;
  m_pos = i_other.m_pos;
  characters = i_other.characters;
}
letter::~letter(){
    
}

// ===========word====================
Word::Word() : m_amountOfLetters(0), m_wordString("empty"), m_letters(nullptr), m_pos({1, 1}) {

}
Word::Word(const char* i_string, const unsigned int& i_stringSize, const vec2& i_pos) : m_amountOfLetters(i_stringSize), m_wordString(i_string), m_pos(i_pos) {
  m_letters = new letter[i_stringSize];
  for(int i = 0; i < i_stringSize; ++i){
    m_letters[i] = {i_string[i], {i_pos.x + 8 * i, i_pos.y}};
  }
}
Word::~Word(){
  if(m_letters != nullptr){
    delete[] m_letters;
  }
}

void Word::operator = (const Word& i_cpy) {
  for(int i = 0; i < i_cpy.m_amountOfLetters; ++i){
    m_letters[i] = {i_cpy.m_wordString[i], i_cpy.m_pos};
  }
  m_pos = i_cpy.m_pos;
  m_wordString = i_cpy.m_wordString;
}
letter Word::operator[] (const int& i_index) const {
  if((m_letters != nullptr) && i_index < m_amountOfLetters){
    return m_letters[i_index];
  }
  return {'e', {1, 1}};
}

// =============text manager==============
textManager::textManager(){

}
textManager::~textManager(){

}

void textManager::writeLetter(renderer* i_ren, const letter& i_letter){
  if(i_letter.m_letter == 'e'){
    return;
  }
  i_ren->renderTex(i_letter.characters);
}
void textManager::writeWord(renderer* i_ren, const Word& i_word){
  if(i_word.m_letters == nullptr){
    return;
  }
  for(int i = 0; i < i_word.m_amountOfLetters; ++i){
    i_ren->renderTex(i_word.m_letters[i].characters);
  }
}
void textManager::writeList(renderer* i_ren, Word* i_list, const unsigned int& i_listSize){
  for(int i = 0; i < i_listSize; ++i){
    writeWord(i_ren, i_list[i]);
  }
}