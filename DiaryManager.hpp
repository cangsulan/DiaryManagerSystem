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
	void showMenu();
	void addDiary();
	void findDiary();
	void showDiaryLogs();
	DiaryManager();
	~DiaryManager();
private:

};