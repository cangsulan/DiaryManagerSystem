#include "main.h"
#include "Diary.hpp"
#include "Student.hpp"
#include "DiaryManager.hpp"
using namespace std;

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

	DiaryManager diarymanager;//建立日记管理系统类对象
	diarymanager.stu = student;//将学生对象的指针赋给管理系统
	while (true) {
		diarymanager.showMenu();
		cout << "输入对应数字来选择功能" << endl;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1://添加日记
			diarymanager.addDiary();
			system("pause");
			break;
		case 2://查看日记
			
			system("pause");
			break;
		case 3://查询日记
			system("pause");
			break;
		case 4://退出系统
			system("pause");
			return 0;
		default:
			break;
		}
	}
	return 0;
}