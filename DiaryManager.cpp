#include "DiaryManager.hpp"
using namespace std;

DiaryManager::DiaryManager()
{

}
DiaryManager::~DiaryManager()
{

}
void DiaryManager::showMenu() 
{
	system("cls");
	cout << "这是一个日记管理系统" << endl;

	//排序展示日记代码

	//
	cout << "1.添加日记" << endl;
	cout << "2.陈列所有日记信息" << endl;
	cout << "3.查询 并 查看日记" << endl;
	cout << "4.退出系统" << endl;
	cout << endl;
}
void DiaryManager::addDiary()
{
	Diary* newdiary = new Diary(this->manager.size() + 1,this->stu->name, this->stu->id);
	cout << "请输入您日记的内容" << endl;
	cin >> newdiary->content;
	this->manager.push_back(newdiary);
	cout << "添加成功！" << endl;
}
void DiaryManager::findDiary()
{
	cout << "当前共收录有 " << this->manager.size() << " 篇日记，日记编号从1开始" << endl;
	cout << "根据日记编号来查看相应日记，" << endl;
	cout << "请输入要浏览的日记的 编号：" << endl;
	int wanted_id;
	cin >> wanted_id;
	for (auto diaryPtr : this->manager) {
		if (diaryPtr->id == wanted_id) {
			diaryPtr->showDiary();
			return;
		}
	}
	cout << "对不起，未能找到该 编号 的日记。。。" << endl;
}
void DiaryManager::showDiaryLogs()
{
	for (auto diaryPtr : this->manager) {
		diaryPtr->showDiarylog();
	}
}