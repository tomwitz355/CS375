#include "Gem.h"

Gem::Gem(int weight, int profit){
  this->weight = weight;
  this->profit = profit;
  this->ratio = profit/weight;
}
