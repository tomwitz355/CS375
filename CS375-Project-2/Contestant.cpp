#include "Contestant.h"

Contestant::Contestant(int id, int val){
  this->id = id;
  this->points = val;
}
Contestant::Contestant(){
  this->id = -1;
  this->points = -1;
}
