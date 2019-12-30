#ifndef KNAPSACK
#define KNAPSACK

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Gem.h"

class Knapsack{
public:
  int capacity;
  int currentWeight;
  int profit;
  std::vector<Gem> items;
  Knapsack(int);
};


#endif
