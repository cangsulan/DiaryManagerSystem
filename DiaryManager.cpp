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
	cout << "����һ���ռǹ���ϵͳ" << endl;

	//����չʾ�ռǴ���

	//
	cout << "1.����ռ�" << endl;
	cout << "2.�鿴�ռ�" << endl;
	cout << "3.��ѯ�ռ�" << endl;
	cout << "4.�˳�ϵͳ" << endl;
	cout << endl;
}
void DiaryManager::addDiary()
{
	Diary* newdiary = new Diary(this->manager.size() + 1,this->stu->name, this->stu->id);
	cout << "���������ռǵ�����" << endl;
	cin >> newdiary->content;
	this->manager.push_back(newdiary);
	cout << "��ӳɹ���" << endl;
}
void DiaryManager::showDiary()
{
		
}