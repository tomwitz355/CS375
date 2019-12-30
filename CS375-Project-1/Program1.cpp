#include "Card.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <fstream>

int sum(std::vector<Card> set){
  int temp = 0;
  for(int i = 0; i < set.size(); i++){
    temp += set[i].value;
  }
  return temp;
}

int sumSell(std::vector<Card> set){
  int temp = 0;
  for(int i = 0; i < set.size(); i++){
    temp += set[i].sell;
  }
  return temp;
}

std::vector<Card> findMax(std::vector<Card> set, int max){
  int maxProfit = 0;
  std::vector<Card> current;
  std::vector<Card> retval;
  int power_size = pow(2, set.size());
  std::vector<int> countUp; //used to create binary powerset
  if(sum(set) <= max){
    return set;
  }
  for(int i = 0; i < power_size; i++){
    for(int j = 0; j < set.size(); j++){
      if(i & (1 << j)){
        countUp.push_back(1);
      }
      else{
        countUp.push_back(0);
      }
    }
      for(int k = 0; k < countUp.size(); k++){
        if(countUp[k] == 1){
          current.push_back(set[k]);
        }
      }
      int temp = sumSell(current);
      int weights = sum(current);
      if(weights <= max){
        if(temp > maxProfit){
          maxProfit = temp;
          retval = current;
        }
      }
      current.clear();
      countUp.clear();
  }
  return retval;
}


int main(int argc, char** argv){

  clock_t start1 = clock();


  std::vector<std::pair<std::string, int>> market;
  std::ifstream marketList(argv[1]);
  if(marketList.is_open()){
    int num_cards;
    marketList >> num_cards;
    for(int i = 0; i < num_cards; i++){
      std::string name;
      int value;
      marketList >> name >> value;
      market.push_back(std::pair<std::string, int>(name, value));
    }
  }
  marketList.close();
  std::ifstream priceList(argv[2]);
  std::ofstream output("output.txt");


  clock_t end1 = clock();

  clock_t time1 = end1 - start1;

  if(priceList.is_open()){
    while(!priceList.eof()){


      clock_t start2 = clock();



      int num_cards;
      int money;
      int price;
      std::string name;
      std::vector<Card> problem;
      priceList >> num_cards >> money;
      for(int i = 0; i < num_cards; i++){
        priceList >> name >> price;
        Card temp = Card(price, name, -1);
        for(int j = 0; j < market.size(); j++){
          if(temp.name == market[j].first){
            temp.sell = market[j].second;
          }
        }
        problem.push_back(temp);
      }
      for(int i = 0; i < problem.size(); i++){
        if(problem[i].sell == -1){
          std::cout << "There was an error, the card: " << problem[i].name << "was not found on the market list.  The program is now exiting..." << std::endl;
          return 0;
        }
      }
      std::vector<Card> result = findMax(problem, money);


      clock_t end2 = clock();

      clock_t time2 = end2 - start2;

      output << num_cards << " " << sumSell(result) << " " << result.size() << " " << (((float)time1) + ((float)time2))/CLOCKS_PER_SEC << std::endl;
    }
  }
  priceList.close();

}
