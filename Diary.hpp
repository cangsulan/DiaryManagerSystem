#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
using namespace std;
class Diary
{
public:
	int id;//�ռǵı��
	string name;//�ռǵ�����
	string content;//�ռǵ�����
	float rating;//���� ,���������ʱ�ø���������ӡʱ����С����ӡ 
	int ratedSize;//��ǰ���ж����˽��й����֣����ڼ���ƽ�����֣���ʼΪ0
	int views;//�����
	string stuName;//�ռ����ߵ�ѧ������
	string stuId;//�ռ����ߵ�ѧ��id
	Diary(int id, string stuName,string stuId);
	Diary(int id, string content, string stuName, string stuId);

	void showDiary();
	void showDiarylog();
	~Diary();

private:

};
