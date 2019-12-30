#include "MinHeap.h"
#include <vector>
#include <sstream>


MinHeap::MinHeap(int size){
  this->maxSize = size;
  std::vector<Contestant*> temp;
  temp.resize(size+1);
  this->heap = temp.data();
  for(int i = 0; i < size+1; i++){
    this->heap[i] = new Contestant(-1, -1);
  }
  int *temp2 = new int[size+1];
  this->ids = temp2;
  for(int i = 1; i < size+1; i++){
    this->ids[i] = -1;
  }
  this->insert = 1;
}

MinHeap::~MinHeap(){
  delete this->ids;
}

void MinHeap::findContestant(int id){
  int location = this->ids[id];
  if((location <= 0) || (location > this->maxSize)){
    std::cout << "Contestant <" << id << "> is not in the extended heap.";
  }
  else{
    std::cout << "Contestant <" << id << "> is in the extended heap with score " << this->heap[location]->points;

  }
}

void MinHeap::insertContestant(int id, int score){
  if(id > this->maxSize){
    std::cout << "Contestant <" << id << "> could not be inserted because the extended heap is full." << std::endl;

  }

  else if((this->ids[id] != -1) && (id < this->maxSize)){
    std::cout << "Contestant <" << id << "> is already in the extended heap: cannot insert." << std::endl;

  }
  else{
    this->heap[this->insert]->id = id;
    this->heap[this->insert]->points = score;
    heapifiy();
    std::cout << "Contestant <" << this->heap[insert]->id << "> inserted with initial score " << this->heap[insert]->points << "." << std::endl;
    this->insert++;
    arrangeIds();
  }
}

void MinHeap::eliminateWeakest(){
  if(insert == 1){
    std::cout << "No contestant can be eliminated since the extended heap is empty." << std::endl;

  }
  else{
    Contestant temp = *this->heap[1];
    swap(1, insert-1);
    heap[insert-1]->id = -1;
    heap[insert-1]->points = -1;
    insert--;
    heapifiy();
    this->ids[temp.id] = -1;
    std::cout << "Contestant <" << temp.id << "> with current lowest score <" << temp.points << "> eliminated." << std::endl;

  }
}

void MinHeap::earnPoints(int id, int points){
  int location = this->ids[id];
  if((location <= 0) || (location > this->maxSize)){
    std::cout << "Contestant <" << id << "> is not in the extended heap." << std::endl;

  }
  else{
    this->heap[this->ids[id]]->points += points;
    std::cout << "Contestant <" << id << ">’s score increased by <"  << points << "> points to <" << this->heap[this->ids[id]]->points << ">." << std::endl;
    heapifiy();
    arrangeIds();

  }
}

void MinHeap::losePoints(int id, int points){
  int location = this->ids[id];
  if((location <= 0) || (location > this->maxSize)){
    std::cout << "Contestant <" << id << "> is not in the extended heap." << std::endl;

  }
  else{
    this->heap[this->ids[id]]->points -= points;
    std::cout << "Contestant <" << id << ">’s score decreased by <"  << points << "> points to <" << this->heap[this->ids[id]]->points << ">." << std::endl;
    heapifiy();
    arrangeIds();

  }
}

void MinHeap::showContestants(){
  int i = 1;
  while(heap[i]->id != -1 && i < this->maxSize+1){
    std::cout << "Contestant <" << heap[i]->id << "> in extended heap location <" << i << "> with score <" << this->heap[i]->points << ">." << std::endl;
    i++;
  }
}

void MinHeap::showHandles(){
  for(int i = 1; i < this->maxSize+1; i++){
    if(this->ids[i] == -1){
      std::cout << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i << ">] = -1." << std::endl;
    }
    else{
      std::cout << "Contestant <" << i << "> stored in extended heap location <" << this->ids[i] << ">." << std::endl;
    }
  }
}

void MinHeap::showLocation(int id){
  int location = this->ids[id];
  if(location == -1){
    std::cout << "There is no Contestant <" << id << "> in the extended heap: handle[<" << id << ">] = -1." << std::endl;

  }
  else{
    std::cout << "Contestant <" << id << "> stored in extended heap location <" << this->ids[id] << ">." << std::endl;

  }
}

void MinHeap::crownWinner(){
  while(this->insert > 2){
    eliminateWeakest();
    std::cout << std::endl;
    this->showContestants();
    std::cout << std::endl;
  }
  std::cout << "Contestant <" << this->heap[1]->id << "> wins with score <" << this->heap[1]->points << ">!" << std::endl;

}

void MinHeap::heapifiy(){
    for(int i = ((this->insert-1)-2)/2; i >= 1; i--){
		    siftDown(i);
    }
    if((this->heap[1]->points > this->heap[2]->points) && (this->heap[2]->points != -1)){
      swap(1,2);
    }
}

void MinHeap::siftDown(int i){
  while(!isLeaf(i)){
  		int temp = left(i);
  		if(temp == -1){
        temp = right(i);
      }
  		else if(right(i) != -1 && heap[left(i)]->points > heap[right(i)]->points){
        temp = right(i);
      }
  		if(heap[i]->points < heap[temp]->points){
        return;
      }
  		swap(i, temp);
  		i = temp;
  	}
  }

void MinHeap::swap(int first, int second){
  Contestant *temp = this->heap[first];
  this->heap[first] = this->heap[second];
  this->heap[second] = temp;
}

bool MinHeap::isLeaf(int i){
  if(left(i) == -1 && right(i) == -1){
    return true;
  }
	else{
    return false;
  }
}

unsigned int MinHeap::left(int parent){
  return (((2*parent)+1 ) < this->insert-1) ? ((2*parent) +1): -1;
}

unsigned int MinHeap::right(int parent){
  return (((2*parent)+2) < this->insert-1) ? ((2*parent) +2): -1;
}

void MinHeap::arrangeIds(){
  int i = 1;
  while((this->heap[i]->id != -1) && (i <= this->maxSize)){
    ids[this->heap[i]->id] = i;
    i++;
  }

}
