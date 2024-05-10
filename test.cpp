#pragma once
#include "main.h"
using namespace std;

void testHafuman() {
	Student* student = new Student();
	student->name = "zhangsan";
	student->id ="202221117989989";

	DiaryManager diarymanager;//建立日记管理系统类对象
	diarymanager.stu = student;
	Diary* diary1 = new Diary(diarymanager.manager.size() + 1, diarymanager.stu->name, diarymanager.stu->id);
	diary1->name = "dkjfls";
	diary1->place = "北京";
	diary1->content.push_back("jkflsjdflsdjffsdjilafjlsJFASF./SA/F,.WQF,/EQW.,F/");
	diary1->content.push_back("收到解放东路咖啡sjlafjslafjlsajf././.2r3534/5.t/34,6/34,t/qajflkdsa;f机撒。、s.afasf艾师傅。、");
	diary1->content.push_back("%……&&（&*（（）");
	diarymanager.manager.push_back(diary1);
	Diary* diary2 = new Diary(diarymanager.manager.size() + 1, diarymanager.stu->name, diarymanager.stu->id);
	diary2->name = "家乐福撒娇";
	diary2->place = "匹诺康尼";
	diary2->content.push_back("梦中武当诀别千里孤行品剑问华山~");
	diary2->content.push_back("恰是一樽江湖还一尊少年~");
	diary2->content.push_back("78934彮节日4嫁人了3年5 325i32405i。、。ds/af.a");
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