#include "HeapSort.hpp"
using namespace std;

// ���˲�����ά��С����
void heapify(vector<Diary*>& heap, int n, int i) {
    int smallest = i; // ��ǰ���ڵ�
    int left = 2 * i + 1; // ���ӽڵ�
    int right = 2 * i + 2; // ���ӽڵ�

    // �ҳ���Сֵ
    if (left < n && heap[left]->compareItem < heap[smallest]->compareItem) {
        smallest = left;
    }

    if (right < n && heap[right]->compareItem < heap[smallest]->compareItem) {
        smallest = right;
    }

    // �����Сֵ���Ǹ��ڵ㣬�������ݹ�����
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify(heap, n, smallest); // �ݹ�����
    }
}
// ����С����
void buildHeap(vector<Diary*>& heap) {
    int n = heap.size();

    // �����һ����Ҷ�ӽڵ㿪ʼ��ǰ������
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(heap, n, i); // ά��С��������
    }
}
// ������� 10 ��Ԫ�ص�С����
void insertToMinHeap(vector<Diary*>& heap, Diary* diary) {
    if (heap.size() < 10) {
        heap.push_back(diary);
        buildHeap(heap); // ���¹�����
    }
    else {
        if (diary->compareItem > heap[0]->compareItem) { // ֻ�е�ֵ�ȶѵĸ���ʱ�Ų���
            heap[0] = diary;
            heapify(heap, heap.size(), 0); // ������
        }
    }
}

// ��ڴ���
void heapsortEnter(vector<Diary*> placeRelevant,int select) {
    if (select == 1) {//�������ȶ����У���������������
        for (auto& diary : placeRelevant)
        {
            diary->compareItem = diary->views;
        }
    }else if (select == 2) {//����ƽ����������
        for (auto& diary : placeRelevant)
        {
            diary->compareItem = diary->rating;
        }
    }
    vector<Diary*> minHeap; // С����
    for (auto& diary : placeRelevant) {
        insertToMinHeap(minHeap, diary); // ���뵽С����
    }
    // ��ȡ��� 10 ��Ԫ�ز�����������
    for (auto it = minHeap.rbegin(); it != minHeap.rend(); ++it) {
        (*it)->showDiarylog();
    }
    
}
