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
	void showMenu();//展示菜单界面
	void addDiary();//添加日记
	void findDiaryById();//查询日记 通过 编号
	void findDiaryByName();//查询日记 通过 名称 精准查询
	void showDiaryLogs();//展示所有日记基本信息
	void sortDiaryOfPlace();//目的地 游学日记排序推荐
	DiaryManager();
	~DiaryManager();
private:

};