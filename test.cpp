#pragma once
#include "main.h"
using namespace std;

void testHafuman() {
	Student* student = new Student();
	student->name = "zhangsan";
	student->id ="202221117989989";

	DiaryManager diarymanager;//�����ռǹ���ϵͳ�����
	diarymanager.stu = student;
	Diary* diary1 = new Diary(diarymanager.manager.size() + 1, diarymanager.stu->name, diarymanager.stu->id);
	diary1->name = "dkjfls";
	diary1->place = "����";
	diary1->content.push_back("jkflsjdflsdjffsdjilafjlsJFASF./SA/F,.WQF,/EQW.,F/");
	diary1->content.push_back("�յ���Ŷ�·����sjlafjslafjlsajf././.2r3534/5.t/34,6/34,t/qajflkdsa;f��������s.afasf��ʦ������");
	diary1->content.push_back("%����&&��&*������");
	diarymanager.manager.push_back(diary1);
	Diary* diary2 = new Diary(diarymanager.manager.size() + 1, diarymanager.stu->name, diarymanager.stu->id);
	diary2->name = "���ָ�����";
	diary2->place = "ƥŵ����";
	diary2->content.push_back("�����䵱����ǧ�����Ʒ���ʻ�ɽ~");
	diary2->content.push_back("ǡ��һ�׽�����һ������~");
	diary2->content.push_back("78934������4������3��5 325i32405i������ds/af.a");
	/*diary1->showDiary();
	diary1->showDiarylog();*/
	
	diarymanager.manager.push_back(diary2);

	diarymanager.CompressedStore();
	DiaryManager diarymanager2;
	diarymanager2.LoadFromCompressedFile();
	for (auto& diary : diarymanager2.manager) {
		diary->showDiary();
		diary->showDiarylog();
	}



}