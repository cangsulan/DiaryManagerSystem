#include "main.h"
#include "Diary.hpp"
using namespace std;
void addDiary(vector<Diary*> *manager,Student* student);
void menu();
int main() {
	Student* student=new Student();
	cout << "请先输入您的姓名：" << endl;
	string name;
	cin >> name;
	cout << "请先输入您的学生id：" << endl;
	string id;
	cin >> id;
	student->name = name;
	student->id = id;
	menu();
	vector<Diary*> *manager = new vector<Diary*>();

	cout << "输入对应数字来选择功能" << endl;
	int select = 0;
	cin >> select;
	switch (select)
	{
	case 1:
		addDiary(manager,student);
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
	return 0;
}
void menu()
{
	cout << "这是一个日记管理系统" << endl;

	//排序展示日记代码
	
	//
	cout << "1.添加日记" << endl;
	cout << "2.查看日记" << endl;
	cout << "3.查询日记" << endl;
}
void addDiary(vector<Diary*>* manager, Student* student)
{
	Diary *newdiary = new Diary(student);
	cout << "请输入您日记的内容"<<endl;
	cin >> newdiary->content;
	manager->push_back(newdiary);
	cout << "添加成功！" << endl;
}