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
		cout << "输入对应数字来选择功能:" << endl;
		cin.ignore(INT_MAX, '\n');//清空 输入缓冲区
		int select = 0;
		scanf_s("%d", &select);//改成cin读入会出问题！！！
		switch (select)
		{
		case 1://添加日记
			diarymanager.addDiary();
			system("pause");
			break;
		case 2://陈列所有日记的基础信息
			diarymanager.showDiaryLogs();
			system("pause");
			break;
		case 3://查询 并 查看日记
			while (true) {
				cout << "选择查询方式：" << endl;
				cout << "1.通过 编号" << endl;
				cout << "2.通过 名称 精准查询" << endl;
				int by;
				cin >> by;
				if (by == 1) {
					diarymanager.findDiaryById();
					break;
				}else if (by == 2) {
					diarymanager.findDiaryByName();
					break;
				}
				else {
					cout << "输入有误哦~" << endl << endl;
				}
			}
			system("pause");
			break;
		case 4://目的地 游学日记排序推荐
			diarymanager.sortDiaryOfPlace();
			system("pause");
			break;
		case 5://退出系统
			system("pause");
			return 0;
		default:
			cout << "输入错误！！" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}