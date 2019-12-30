#include "Contestant.h"
#include "MinHeap.h"
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv){
  // MinHeap heap = MinHeap(5);
  //  heap.heap[1]->id = -1;
  //  heap.heap[1]->points = -1;
  //
  // heap.insertContestant(1,0);
  //
  // heap.insertContestant(2,15);
  //
  // heap.insertContestant(3,80);
  //
  // heap.insertContestant(4,20);
  //
  // heap.showContestants();
  // heap.findContestant(5);
  //
  // heap.eliminateWeakest();
  // heap.losePoints(3,40);
  // heap.earnPoints(2,10);
  // heap.showContestants();
  // heap.showHandles();
  // heap.crownWinner();
  std::ifstream commandList(argv[1]);
  std::vector<std::vector<std::string>> commands;
  int maxSize;
  if(commandList.is_open()){
    std::string heapSize;
    getline(commandList, heapSize);
    maxSize = std::stoi(heapSize);
    while(!commandList.eof()){
      std::string line;
      std::vector<std::string> command;
      getline(commandList, line);

      std::string temp = "";
      for(int i = 0; i < line.size()+1; i++){
        if(line[i] == ' ' || i == line.size()){
          command.push_back(temp);
          temp = "";
        }
        else{
          temp += line[i];
        }
      }
      commands.push_back(command);
    }
  }
  commandList.close();
  MinHeap heap = MinHeap(maxSize);
  heap.heap[1]->id = -1;
  heap.heap[1]->points = -1;

  for(int i = 1; i < heap.maxSize+1; i++){
    std::cout << heap.heap[i]->id;
    std::cout << " "<< heap.heap[i]->points << std::endl;
  }

  std::ofstream output("output.txt");
  for(int i = 0; i < commands.size(); i++){

    if(commands[i].size() == 1){
      if(commands[i][0] == "eliminateWeakest"){
        heap.eliminateWeakest();
      }
      if(commands[i][0] == "showContestants"){
        heap.showContestants();
      }
      if(commands[i][0] == "showHandles"){
        heap.showHandles();

      }
      if(commands[i][0] == "crownWinner"){
        heap.crownWinner();
      }
    }


    if(commands[i].size() == 2){
      if(commands[i][0] == "findContestant"){
        std::string temp1 = commands[i][1];
        temp1.front() = ' ';
        temp1.back() = ' ';
        int arg1 = std::stoi(temp1);
        heap.findContestant(arg1);
      }
      if(commands[i][0] == "showLocation"){
        std::string temp1 = commands[i][1];
        temp1.front() = ' ';
        temp1.back() = ' ';
        int arg1 = std::stoi(temp1);
        heap.showLocation(arg1);
      }
    }

    if(commands[i].size() == 3){

      if(commands[i][0] == "insertContestant"){
        std::string temp1 = commands[i][1];
        temp1.front() = ' ';
        temp1.back() = ' ';
        int arg1 = std::stoi(temp1);


        std::string temp2 = commands[i][2];
        temp2.front() = ' ';
        temp2.back() = ' ';
        int arg2 = std::stoi(temp2);
        heap.insertContestant(arg1, arg2);
      }
      if(commands[i][0] == "earnPoints"){
        std::string temp1 = commands[i][1];
        temp1.front() = ' ';
        temp1.back() = ' ';
        int arg1 = std::stoi(temp1);


        std::string temp2 = commands[i][2];
        temp2.front() = ' ';
        temp2.back() = ' ';
        int arg2 = std::stoi(temp2);
        heap.earnPoints(arg1, arg2);
      }
      if(commands[i][0] == "losePoints"){
        std::string temp1 = commands[i][1];
        temp1.front() = ' ';
        temp1.back() = ' ';
        int arg1 = std::stoi(temp1);


        std::string temp2 = commands[i][2];
        temp2.front() = ' ';
        temp2.back() = ' ';
        int arg2 = std::stoi(temp2);

        heap.losePoints(arg1, arg2);

      }
    }
  }
}
