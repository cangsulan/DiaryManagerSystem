#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include "Student.hpp"
using namespace std;
class Diary
{
public:

	string content;//评论的内容
	int rating;//评分
	int views;//浏览量
	Student* stu;//日记的作者
	Diary(Student* stu);
	Diary(string content, Student* stu);
	~Diary();

private:

};
Diary::Diary(Student* stu) {
	this->views = 0;
	this->rating = 5;//创建时默认评分为5分
	this->stu = stu;
	this->content = "";
}
Diary::Diary(string content, Student* stu) {
	this->views = 0;
	this->content = content;
	this->rating = 5;
	this->stu = stu;
}
Diary::~Diary() {

}