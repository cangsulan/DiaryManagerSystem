#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class Diary
{
public:
	int id;//日记的编号
	string name;//日记的名称
	string place;//日记所记录的 游学目的地
	vector<string> content;//日记的内容

	float rating;//评分 ,计算和排序时用浮点数，打印时保留小数打印 
	int ratedSize;//当前已有多少人进行过评分，用于计算平均评分，初始为0
	int views;//浏览量
	string stuName;//日记作者的学生名字
	string stuId;//日记作者的学生id

	double compareItem;//排序时比较的标准，默认赋值为浏览量
	Diary(int id, string stuName,string stuId);
	Diary();//空参构造
	void serialize(ofstream& out)const;//以二进制方式序列化
	void deserialize(ifstream& in);//反序列化

	void searchContent();//全文检索功能
	void addRating();//对这篇日记进行评分
	void showDiary();
	void showDiarylog();
	~Diary();

private:

};
