#pragma once
#include "main.h"
using namespace std;

void testHafuman() {
	Student* student = new Student();
	student->name = "zhangsan";
	student->id = 20;

	DiaryManager diarymanager;//�����ռǹ���ϵͳ�����
	diarymanager.stu = student;
	Diary* diary1 = new Diary(diarymanager.manager.size() + 1, diarymanager.stu->name, diarymanager.stu->id);
	diary1->name = "dkjfls";
	diary1->place = "����";
	diary1->content.push_back("jkflsjdflsdjf");
	diary1->content.push_back("�յ���Ŷ�·���Ȼ�������s.afasf��ʦ������");
	diary1->content.push_back("%����&&��&*������");
	diary1->showDiary();
	diary1->showDiarylog();
	diarymanager.manager.push_back(diary1);
	diarymanager.CompressedStore();
	DiaryManager diarymanager2;
	diarymanager2.LoadFromCompressedFile();
	diarymanager2.manager.at(0)->showDiary();



}