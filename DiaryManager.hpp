#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include "Student.hpp"
#include "Diary.hpp"
#include "HeapSort.hpp"
#include "Hafuman.hpp"

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

	void CompressedStore();//��ϵͳ�ر�֮ǰ�������ռǽ���ѹ���洢��ʹ�����л��͹���������ķ�ʽ
	void LoadFromCompressedFile();//��ϵͳʱ������ѹ���洢���ռǶ�ȡ����
	DiaryManager();
	~DiaryManager();
private:

};