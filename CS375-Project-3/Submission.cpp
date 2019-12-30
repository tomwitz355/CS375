#include "Gem.h"
#include "Knapsack.h"
#include "Node.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <ctime>
#include <sstream>

void sort(std::vector<Gem> *array){
  for(int i = 0; i < (*array).size()-1; i++){
    for(int j = 0; j < (*array).size()-i-1; j++){
      if((*array)[j].ratio < (*array)[j+1].ratio){
        Gem val = (*array)[j];
        (*array)[j] = (*array)[j+1];
        (*array)[j+1] = val;
      }
    }
  }
}

Knapsack algorithmOne(std::vector<Gem> *input, int capacity){
  Knapsack retval = Knapsack(capacity);
  for(int i = 0; i < (*input).size(); i++){
    if((*input)[i].weight + retval.currentWeight <= retval.capacity){
      retval.items.push_back((*input)[i]);
      retval.currentWeight += (*input)[i].weight;
      retval.profit += (*input)[i].profit;
    }
  }
  return retval;
}

Knapsack algorithmTwo(std::vector<Gem> *input, int capacity){
  Knapsack solution1 = algorithmOne(input, capacity);
  Gem maxVal = Gem(1,0);
  for(int i = 0; i < (*input).size(); i++){
    if(((*input)[i].profit > maxVal.profit) && ((*input)[i].weight <= capacity)){
      maxVal = (*input)[i];
    }
  }
  Knapsack solution2 = Knapsack(capacity);
  solution2.items.push_back(maxVal);
  solution2.currentWeight += maxVal.weight;
  solution2.profit += maxVal.profit;
  if(solution1.profit > solution2.profit){
    return solution1;
  }
  return solution2;
}

/*
int getBound(int item, int weight, int profit, std::vector<Gem> *input, int capacity){
  int i = item;
  while((weight < capacity) && (item <= (*input).size()-1)){
    if((*input)[i].weight + weight <= capacity){
      profit += (*input)[i].profit;
      weight += (*input)[i].weight;
    }
    else{
      float fraction = (float)(capacity-weight)/(float)(*input)[i].weight;
      float result;
      result = (fraction * (*input)[i].profit) + (float)profit;
      weight = capacity;
      profit = (int)result;
    }
    i++;
  }
  return profit;
}
*/

int getBound(Node node, int capacity, std::vector<Gem> *input){
  if(node.weight >= capacity){
    return 0;
  }
  int bound = node.profit;
  int item = node.item+1;
  int weight = node.weight;
  while((item < (*input).size()) && (weight+(*input)[item].weight <= capacity)){
    weight += (*input)[item].weight;
    bound += (*input)[item].profit;
    item++;
  }
  if(item < (*input).size()){
    float frac = (float)(capacity-weight)/(float)(*input)[item].weight;
    float result = (frac * (*input)[item].profit) + (float)bound;
    bound = result;
  }
  return bound;
}
/*
bool promising(Node n, int item, int capacity, std::vector<Gem> *input, int maxProfit){
  if(n.weight >= capacity){
    return false;
  }
  int bound = getBound(item+1, n.weight, n.profit, input, capacity);
  return (bound > maxProfit);
}
*/
/*
int algorithmThree(std::vector<Gem> *input, int capacity){
   std::stack<Node> nodes;
   std::vector<Node> test;
   Node current = Node(0, 0, getBound(0, 0, 0, input, capacity), -1);
   Node next = current;
   std::cout << current.profit << " " << current.weight << " " << current.bound << " " << current.item << std::endl;
   std::cout << next.profit << " " << next.weight << " " << next.bound << " " << next.item << std::endl;

   Knapsack bestSet = algorithmTwo(input, capacity);
   int maxProfit = bestSet.profit;


   nodes.push(current);
   while(!nodes.empty()){

     current = nodes.top();
     nodes.pop();

     // if(current.item == -1){
     //   next.item = 0;
     // }
     std::cout << current.profit << " "<< current.weight << " " << current.bound << " " << current.item << std::endl;
     if(current.item == (*input).size()-1){
       continue;
     }

     next.item = current.item + 1;
     std::cout << next.item << std::endl;
     int bound;
     if(next.item == 3){
       bound = current.weight + (*input)[next.item].weight;
     }
     else{
       bound = getBound(next.item+1, current.weight + (*input)[next.item].weight, current.profit + (*input)[next.item].profit, input, capacity);
     }

     std::cout << "left child: "<< bound << std::endl;
     next.profit = current.profit + (*input)[next.item].profit;
     next.weight = current.weight + (*input)[next.item].weight;
     next.bound = bound;

     if ((next.weight <= capacity) && next.profit > maxProfit){
       maxProfit = next.profit;
     }

     if(next.bound > maxProfit && next.weight <= capacity){
       nodes.push(next);
       test.push_back(next);
     }
     next.profit = current.profit;
     next.weight = current.weight;

     int bound2 = getBound(current.item+1, current.weight, current.profit, input, capacity);

     if(bound2 > maxProfit && next.weight <= capacity){
       std::cout << "right child: "<< bound2 << std::endl;
       next.bound = bound2;
       nodes.push(next);
       test.push_back(next);
     }
   }
//   for(int i = 0; i < test.size(); i++){
//     std::cout << test[i].profit << " "<< test[i].weight << " " << test[i].bound << std::endl;
//   }
   return maxProfit;
}
*/

int algorithmThree(std::vector<Gem> *input, int capacity){
  std::queue<Node> nodes;
  Node current, next;
  current.item = -1;
  current.profit = 0;
  current.weight = 0;
  nodes.push(current);

  int maxprofit = algorithmTwo(input, capacity).profit;

  while(!nodes.empty()){
    current = nodes.front();
    nodes.pop();

    if(current.item == -1){
      next.item =0;
    }
    if(current.item == (*input).size()-1){
      continue;
    }

    next.item = current.item +1;


    next.weight = current.weight + (*input)[next.item].weight;
    next.profit = current.profit + (*input)[next.item].profit;

    if((next.weight <= capacity) && (next.profit > maxprofit)){
      maxprofit = next.profit;
    }

    next.bound = getBound(next, capacity, input);

    if(next.bound > maxprofit){
      nodes.push(next);
    }

    next.weight = current.weight;
    next.profit = current.profit;
    next.bound = getBound(next, capacity, input);
    if(next.bound > maxprofit){
      nodes.push(next);
    }
  }
  return maxprofit;
}


int main(int argc, char ** argv){
  std::ofstream output(argv[2]);
  std::ifstream input(argv[1]);
  if(input.is_open()){
    while(!input.eof() && (input.peek() != -1) && (input.peek() != 10)){
      int size;
      int capacity;
      std::string line;
      std::vector<Gem> gems;
      getline(input, line);
      std::stringstream linestream(line);
      linestream >> size >> capacity;
      for(int i = 0; i < size; i++){
        int weight;
        int profit;
        getline(input, line);
        std::stringstream linestream2(line);
        linestream2 >> weight >> profit;
        Gem temp = Gem(weight, profit);
        gems.push_back(temp);
      }

      auto start = clock();
      std::cout << "First clock tick: "<< start << std::endl;
      float duration;
      sort(&gems);
      int alg = std::atoi(argv[3]);
      if(alg == 0){
        Knapsack retval = algorithmOne(&gems, capacity);
        auto finish = clock();
        std::cout << "Second clock tick: "<< finish << std::endl;
        std::cout << "Ticks per second: " << CLOCKS_PER_SEC << std::endl;
        duration = ( finish - start) / (float)CLOCKS_PER_SEC;
        output << size << " "<< retval.profit << " "<< duration *1000<< std::endl;
      }
      if(alg == 1){
        Knapsack retval = algorithmTwo(&gems, capacity);
        auto finish = clock();
        std::cout << "Second clock tick: "<< finish << std::endl;
        std::cout << "Ticks per second: " << CLOCKS_PER_SEC << std::endl;
        duration = ( finish - start) / (float)CLOCKS_PER_SEC;
        output << size << " "<< retval.profit << " "<< duration *1000<< std::endl;


      }
      if(alg == 2){
        int retval = algorithmThree(&gems, capacity);
        auto finish = clock();
        std::cout << "Second clock tick: "<< finish << std::endl;
        std::cout << "Ticks per second: " << CLOCKS_PER_SEC << std::endl;
        duration = ( finish - start) / (float)CLOCKS_PER_SEC;
        output << size << " "<< retval << " "<< duration *1000<< std::endl;
      }
      gems.clear();

    }
  }



}
