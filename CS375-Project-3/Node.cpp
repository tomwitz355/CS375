#include "Node.h"


Node::Node(int profit, int weight, int bound, int item){
  this->profit = profit;
  this->weight = weight;
  this->bound = bound;
  this->item = item;
}

Node::Node(){
  this->profit = 0;
  this->weight = 0;
  this->bound = 0;
  this->item = 0;
}
