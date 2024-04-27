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
	cout << "2.查看日记" << endl;
	cout << "3.查询日记" << endl;
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
void DiaryManager::showDiary()
{
		
}