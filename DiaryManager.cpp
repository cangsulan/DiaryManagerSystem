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
	cout << "2.���������ռ���Ϣ" << endl;
	cout << "3.��ѯ �� �鿴�ռ�" << endl;
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
void DiaryManager::findDiary()
{
	cout << "��ǰ����¼�� " << this->manager.size() << " ƪ�ռǣ��ռǱ�Ŵ�1��ʼ" << endl;
	cout << "�����ռǱ�����鿴��Ӧ�ռǣ�" << endl;
	cout << "������Ҫ������ռǵ� ��ţ�" << endl;
	int wanted_id;
	cin >> wanted_id;
	for (auto diaryPtr : this->manager) {
		if (diaryPtr->id == wanted_id) {
			diaryPtr->showDiary();
			return;
		}
	}
	cout << "�Բ���δ���ҵ��� ��� ���ռǡ�����" << endl;
}
void DiaryManager::showDiaryLogs()
{
	for (auto diaryPtr : this->manager) {
		diaryPtr->showDiarylog();
	}
}