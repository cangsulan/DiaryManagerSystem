#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include "Student.hpp"
#include "Diary.hpp"
#include "HeapSort.hpp"
class DiaryManager {
public:
	vector<Diary*> manager;
	Student *stu;
	void showMenu();//չʾ�˵�����
	void addDiary();//����ռ�
	void findDiaryById();//��ѯ�ռ� ͨ�� ���
	void findDiaryByName();//��ѯ�ռ� ͨ�� ���� ��׼��ѯ
	void showDiaryLogs();//չʾ�����ռǻ�����Ϣ
	void sortDiaryOfPlace();//Ŀ�ĵ� ��ѧ�ռ������Ƽ�
	DiaryManager();
	~DiaryManager();
private:

};