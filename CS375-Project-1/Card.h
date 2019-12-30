#ifndef CARD_H
#define CARD_H


#include <cstdlib>
#include <iostream>
#include <string>

class Card{
public:
  int value;
  std::string name;
  int sell;
  Card(int, std::string, int);
};

#endif
