#include "main.h"
#include "Diary.hpp"
#include "Student.hpp"
#include "DiaryManager.hpp"
using namespace std;

int main() {
	Student* student=new Student();
	cout << "������������������" << endl;
	string name;
	cin >> name;
	cout << "������������ѧ��id��" << endl;
	string id;
	cin >> id;
	student->name = name;
	student->id = id;

	DiaryManager diarymanager;//�����ռǹ���ϵͳ�����
	diarymanager.stu = student;//��ѧ�������ָ�븳������ϵͳ
	while (true) {
		diarymanager.showMenu();
		cout << "�����Ӧ������ѡ����" << endl;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1://����ռ�
			diarymanager.addDiary();
			system("pause");
			break;
		case 2://�鿴�ռ�
			
			system("pause");
			break;
		case 3://��ѯ�ռ�
			system("pause");
			break;
		case 4://�˳�ϵͳ
			system("pause");
			return 0;
		default:
			break;
		}
	}
	return 0;
}