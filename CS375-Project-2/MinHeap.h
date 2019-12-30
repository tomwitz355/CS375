#ifndef MINHEAP_H
#define MINHEAP_H


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "Contestant.h"


class MinHeap{
private:
  void heapifiy();
  void siftDown(int);
  void swap(int, int);
  bool isLeaf(int);
  unsigned int left(int);
  unsigned int right(int);
  int insert;
  void arrangeIds();
public:
  int maxSize;
  Contestant **heap;
  int *ids;
  MinHeap(int);
  ~MinHeap();
  void findContestant(int);
  void insertContestant(int, int);
  void eliminateWeakest();
  void earnPoints(int, int);
  void losePoints(int, int);
  void showContestants();
  void showHandles();
  void showLocation(int);
  void crownWinner();
};

#endif
