#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
class Diary
{
public:
	int id;//�ռǵı��
	string name;//�ռǵ�����
	string place;//�ռ�����¼�� ��ѧĿ�ĵ�
	vector<string> content;//�ռǵ�����

	float rating;//���� ,���������ʱ�ø���������ӡʱ����С����ӡ 
	int ratedSize;//��ǰ���ж����˽��й����֣����ڼ���ƽ�����֣���ʼΪ0
	int views;//�����
	string stuName;//�ռ����ߵ�ѧ������
	string stuId;//�ռ����ߵ�ѧ��id

	double compareItem;//����ʱ�Ƚϵı�׼��Ĭ�ϸ�ֵΪ�����
	Diary(int id, string stuName,string stuId);

	void showDiary();
	void showDiarylog();
	~Diary();

private:

};
