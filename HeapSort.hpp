#pragma once
#include <iostream>
#include <vector>
#include <algorithm> // for std::swap and std::reverse
#include "Diary.hpp"

void heapify(vector<Diary*>& heap, int n, int i);
void buildHeap(vector<Diary*>& heap);
void insertToMinHeap(vector<Diary*>& heap, Diary* diary);

//�ռǶ�����ǰ10λ��select��ѡ���������ݣ�1��ʾ�ȶȣ�2��ʾƽ������
void heapsortEnter(vector<Diary*> placeRelevant,int select);