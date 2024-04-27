#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include "Student.hpp"
#include "Diary.hpp"

class DiaryManager {
public:
	vector<Diary*> manager;
	Student *stu;
	void showMenu();//展示菜单界面
	void addDiary();//添加日记
	void findDiaryById();//查询日记 通过 编号
	void findDiaryByName();//查询日记 通过 名称 精准查询
	void showDiaryLogs();//展示所有日记基本信息

	DiaryManager();
	~DiaryManager();
private:

};