#include "main.h"
#include "Diary.hpp"
using namespace std;
void addDiary(vector<Diary*> *manager,Student* student);
void menu();
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
	menu();
	vector<Diary*> *manager = new vector<Diary*>();

	cout << "�����Ӧ������ѡ����" << endl;
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
	cout << "����һ���ռǹ���ϵͳ" << endl;

	//����չʾ�ռǴ���
	
	//
	cout << "1.����ռ�" << endl;
	cout << "2.�鿴�ռ�" << endl;
	cout << "3.��ѯ�ռ�" << endl;
}
void addDiary(vector<Diary*>* manager, Student* student)
{
	Diary *newdiary = new Diary(student);
	cout << "���������ռǵ�����"<<endl;
	cin >> newdiary->content;
	manager->push_back(newdiary);
	cout << "��ӳɹ���" << endl;
}