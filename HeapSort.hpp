#pragma once
#include <iostream>
#include <vector>
#include <algorithm> // for std::swap and std::reverse
#include "Diary.hpp"

void heapify(vector<Diary*>& heap, int n, int i);
void buildHeap(vector<Diary*>& heap);
void insertToMinHeap(vector<Diary*>& heap, Diary* diary);

//日记堆排序前10位，select可选择排序依据，1表示热度，2表示平均评分
void heapsortEnter(vector<Diary*> placeRelevant,int select);