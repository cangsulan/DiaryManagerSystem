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
	void showMenu();//展示菜单界面
	void addDiary();//添加日记
	void findDiaryById();//查询日记 通过 编号
	void findDiaryByName();//查询日记 通过 名称 精准查询
	void showDiaryLogs();//展示所有日记基本信息
	void sortDiaryOfPlace();//目的地 游学日记排序推荐

	void CompressedStore();//在系统关闭之前对所有日记进行压缩存储，使用序列化和哈夫曼编码的方式
	void LoadFromCompressedFile();//打开系统时把所有压缩存储的日记读取出来
	DiaryManager();
	~DiaryManager();
private:

};