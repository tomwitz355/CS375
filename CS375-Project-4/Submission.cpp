#include "Gem.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>

//sorting function
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

//This is the algorithm from class with only two row stored
int algorithmFour(std::vector<Gem> array, int capacity){
  int result [2][capacity+1];
  for(int i = 0; i <= capacity; i++){
    result[0][i] = 0;
  }
  for(int i = 0; i < 2; i++){
    result[i][0] = 0;
  }


  for(int i = 1; i <= array.size(); i++){
    for(int j = 1; j <= capacity; j++){
      if(array[i-1].weight <= j){
        result[1][j] = std::max(result[0][j-array[i-1].weight]+array[i-1].profit, result[0][j]);
//        std::cout << "i: "<< i << " "<< "j: "<< j << " " << "result: " <<result[1][j] <<std::endl;
      }
      else{
        result[1][j] = result[0][j];
//        std::cout << "i: "<< i << " "<< "j: "<< j << " " << "result: " <<result[1][j] <<std::endl;
      }
    }
    for(int j = 0; j <= capacity; j++){
      result[0][j] = result[1][j];
    }
  }
  return result[1][capacity];
}

//This is the exact algorithm from in class
/*
int algorithmFour(std::vector<Gem> array, int capacity){
  int result [array.size()+1][capacity+1];
  for(int i = 0; i <= capacity; i++){
    result[0][i] = 0;
  }
  for(int i = 0; i <= array.size(); i++){
    result[i][0] = 0;
  }
  for(int i = 1; i <= array.size(); i++){
    for(int j = 1; j <= capacity; j++){
      if(array[i-1].weight <= j){
        result[i][j] = std::max(result[i-1][j-array[i-1].weight]+array[i-1].profit, result[i-1][j]);
//        std::cout << "i: "<< i << " "<< "j: "<< j << " " << "result: " <<result[i][j] <<std::endl;
      }
      else{
        result[i][j] = result[i-1][j];
//        std::cout << "i: "<< i << " "<< "j: "<< j << " " << "result: " <<result[i][j] <<std::endl;
      }
    }
  }
  return result[array.size()][capacity];
}
*/

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
      if(alg == 3){
        int retval = algorithmFour(gems, capacity);
        auto finish = clock();
        std::cout << "Second clock tick: "<< finish << std::endl;
        std::cout << "Ticks per second: " << CLOCKS_PER_SEC << std::endl;
        duration = ( finish - start) / (float)CLOCKS_PER_SEC;
        std::string dp = "Dynamic Programming: ";
        output << dp << size << " "<< retval << " "<< duration << std::endl;
      }
      gems.clear();

    }
  }

/*
  Gem gem1 = Gem(2,40);
  Gem gem2 = Gem(5,30);
  Gem gem3 = Gem(10,50);
  Gem gem4 = Gem(5,10);
  std::vector<Gem> input;
  input.push_back(gem1);
  input.push_back(gem2);
  input.push_back(gem3);
  input.push_back(gem4);
  sort(&input);
  int result = algorithmFourTest(input,16);
  std::cout << result << std::endl;
*/
}
