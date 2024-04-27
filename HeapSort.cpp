#include "HeapSort.hpp"
using namespace std;

// 下滤操作，维护小根堆
void heapify(vector<Diary*>& heap, int n, int i) {
    int smallest = i; // 当前根节点
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 找出最小值
    if (left < n && heap[left]->compareItem < heap[smallest]->compareItem) {
        smallest = left;
    }

    if (right < n && heap[right]->compareItem < heap[smallest]->compareItem) {
        smallest = right;
    }

    // 如果最小值不是根节点，交换并递归下滤
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify(heap, n, smallest); // 递归下滤
    }
}
// 构建小根堆
void buildHeap(vector<Diary*>& heap) {
    int n = heap.size();

    // 从最后一个非叶子节点开始向前构建堆
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(heap, n, i); // 维持小根堆性质
    }
}
// 保持最大 10 个元素的小根堆
void insertToMinHeap(vector<Diary*>& heap, Diary* diary) {
    if (heap.size() < 10) {
        heap.push_back(diary);
        buildHeap(heap); // 重新构建堆
    }
    else {
        if (diary->compareItem > heap[0]->compareItem) { // 只有当值比堆的根大时才插入
            heap[0] = diary;
            heapify(heap, heap.size(), 0); // 调整堆
        }
    }
}

// 入口代码
void heapsortEnter(vector<Diary*> placeRelevant,int select) {
    if (select == 1) {//若根据热度排行，则根据浏览量排序
        for (auto& diary : placeRelevant)
        {
            diary->compareItem = diary->views;
        }
    }else if (select == 2) {//根据平均评分排序
        for (auto& diary : placeRelevant)
        {
            diary->compareItem = diary->rating;
        }
    }
    vector<Diary*> minHeap; // 小根堆
    for (auto& diary : placeRelevant) {
        insertToMinHeap(minHeap, diary); // 插入到小根堆
    }
    // 获取最大 10 个元素并按降序排序
    for (auto it = minHeap.rbegin(); it != minHeap.rend(); ++it) {
        (*it)->showDiarylog();
    }
    
}
