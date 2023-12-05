#include "createalphabet.hpp"

void piyavkin::createAlphabet(bool * const alphabet, char * line, size_t length)
{
  for (size_t i = 0; i < length; ++i)
  {
    int symbol = line[i]-'a';
    if (symbol >= 0 && symbol <= 26)
    {
      alphabet[symbol] = true;
    }
  }
}
