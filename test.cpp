#pragma once
#include "main.h"
using namespace std;

void testHafuman() {
	Student* student = new Student();
	student->name = "zhangsan";
	student->id = 20;

	DiaryManager diarymanager;//建立日记管理系统类对象
	diarymanager.stu = student;
	Diary* diary1 = new Diary(diarymanager.manager.size() + 1, diarymanager.stu->name, diarymanager.stu->id);
	diary1->name = "dkjfls";
	diary1->place = "北京";
	diary1->content.push_back("jkflsjdflsdjf");
	diary1->content.push_back("收到解放东路咖啡机撒。、s.afasf艾师傅。、");
	diary1->content.push_back("%……&&（&*（（）");
	diary1->showDiary();
	diary1->showDiarylog();
	diarymanager.manager.push_back(diary1);
	diarymanager.CompressedStore();
	DiaryManager diarymanager2;
	diarymanager2.LoadFromCompressedFile();
	diarymanager2.manager.at(0)->showDiary();



}