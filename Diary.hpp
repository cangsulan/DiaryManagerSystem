#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
using namespace std;
class Diary
{
public:
	int id;//日记的编号
	string name;//日记的名称
	string content;//日记的内容
	float rating;//评分 ,计算和排序时用浮点数，打印时保留小数打印 
	int ratedSize;//当前已有多少人进行过评分，用于计算平均评分，初始为0
	int views;//浏览量
	string stuName;//日记作者的学生名字
	string stuId;//日记作者的学生id
	Diary(int id, string stuName,string stuId);
	Diary(int id, string content, string stuName, string stuId);

	void showDiary();
	void showDiarylog();
	~Diary();

private:

};
