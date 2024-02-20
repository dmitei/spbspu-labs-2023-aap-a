#include <iostream>
#include "InputString.hpp"
#include "DeleteAllNumbers.hpp"
#include "CountUniqueLetters.hpp"

int main()
{
  char* string = nullptr;
  char* newString = nullptr;
  try
  {
    string = vyzhanov::inputString(std::cin);
    if (string[0] == '\0')
    {
      delete[] string;
      std::cerr << "Empty string!" << "\n";
      return 1;
    }
    size_t stringLength = 0;
    while (string[stringLength])
    {
      stringLength++;
    }
    newString = new char[stringLength];
    std::cout << vyzhanov::deleteAllNumbers(string, newString, stringLength) << "\n";
    std::cout << vyzhanov::countUniqueLetters(string) << "\n";
  }
  catch (const std::bad_alloc& e)
  {
    delete[] string;
    delete[] newString;
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  catch (const std::logic_error & e)
  {
    delete[] string;
    delete[] newString;
    std::cerr << "Error: " << e.what() << '\n';
    return 2;
  }
    delete[] string;
    delete[] newString;
}
