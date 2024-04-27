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

	string content;//���۵�����
	int rating;//����
	int views;//�����
	Student* stu;//�ռǵ�����
	Diary(Student* stu);
	Diary(string content, Student* stu);
	~Diary();

private:

};
Diary::Diary(Student* stu) {
	this->views = 0;
	this->rating = 5;//����ʱĬ������Ϊ5��
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