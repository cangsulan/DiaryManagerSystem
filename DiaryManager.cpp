#include "DiaryManager.hpp"
using namespace std;

DiaryManager::DiaryManager()
{

}

DiaryManager::~DiaryManager()
{
	delete this->stu;
	for (auto diaryPtr : this->manager) {
		delete diaryPtr;
	}
}

void DiaryManager::showMenu() 
{
	system("cls");
	
	cout << "------------------------------------------------" << endl;
	//����չʾ�ռǴ���
	heapsortEnter(this->manager, 1);
	//
	cout << "����һ���ռǹ���ϵͳ" << endl;
	cout << "����Ϊ��ǰ�ȶ����а�ǰ10���ռ�~~~~~~" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1.����ռ�" << endl;
	cout << "2.���������ռ���Ϣ" << endl;
	cout << "3.��ѯ �� �鿴�ռ�" << endl;
	cout << "4.Ŀ�ĵ� ��ѧ�ռ������Ƽ�" << endl;
	cout << "5.�˳�ϵͳ" << endl;
	cout << endl;
}

void DiaryManager::addDiary()
{
	Diary* newdiary = new Diary(this->manager.size() + 1,this->stu->name, this->stu->id);
	cout << "�������ռǵ� ���ƣ�" << endl;
	cin >> newdiary->name;
	cout << "�������ռ������� ��ѧ�ص㣺" << endl;
	cin >> newdiary->place;
	cout << "���������ռǵ����ݣ�(���У����������س��������µ�һ������ \"eof\" ������)" << endl;
	string diaryLine;
	for (cin >> diaryLine; diaryLine != "eof"; cin >> diaryLine) {
		newdiary->content.push_back(diaryLine);
	}
	this->manager.push_back(newdiary);
	cout << "��ӳɹ���" << endl;
}

void DiaryManager::findDiaryById()
{
	cout << "��ǰ����¼�� " << this->manager.size() << " ƪ�ռǣ��ռǱ�Ŵ�1��ʼ" << endl;
	cout << "�����ռǱ�����鿴��Ӧ�ռǣ�" << endl;
	cout << "������Ҫ������ռǵ� ��ţ�" << endl;
	int wanted_id;
	cin >> wanted_id;
	//���ǰ��ձ���ţ�û���ҵĻ�������ֱ�Ӹ���id��
	if (wanted_id >= 1 && wanted_id <= this->manager.size()) {
		this->manager.at(wanted_id - 1)->showDiary();
	}
	else {
		cout << "�Բ���δ���ҵ��� ��� ���ռǡ�����" << endl;
	}
	
	//˳�����
	/*for (auto diaryPtr : this->manager) {
		if (diaryPtr->id == wanted_id) {
			diaryPtr->showDiary();
			return;
		}
	}*/
	//cout << "�Բ���δ���ҵ��� ��� ���ռǡ�����" << endl;
}

void DiaryManager::findDiaryByName()
{
	cout << "��ǰ����¼�� " << this->manager.size() << " ƪ�ռ�" << endl;
	cout << "������Ҫ������ռǵ� ���ƣ�" << endl;
	string wanted_name;
	cin >> wanted_name;
	for (auto diaryPtr : this->manager) {
		if (diaryPtr->name == wanted_name) {
			diaryPtr->showDiary();
			return;
		}
	}
	cout << "�Բ���δ���ҵ����ռǡ�����" << endl;
}

void DiaryManager::showDiaryLogs()
{
	for (auto diaryPtr : this->manager) {
		diaryPtr->showDiarylog();
	}
}

void DiaryManager::sortDiaryOfPlace()
{
	cout << "���������Ȥ����ѧ�ص㣺" << endl;
	string wanted_place;
	cin >> wanted_place;
	vector<Diary*> placeRelevant;//����ѧ�ص���ռ��ҳ��� �ŵ����vector��
	int size=0;
	for (auto& diaryPtr : this->manager) {
		if (diaryPtr->place == wanted_place) {
			placeRelevant.push_back(diaryPtr);
		}
	}
	size = placeRelevant.size();
	cout << "���ҵ� " << size<< " ƪ�ռǣ�" << endl;
	
	if (size == 0) {
		cout << "û������ռǣ��޷��Ƽ�������" << endl;
		return;
	}
	while (true) {
		cout << "��ѡ���Ƽ���ʽ��" << endl; //������ ����� �������ų�ǰ10�����ɣ�
		cout << "1.�ȶ� ����" << endl;
		cout << "2.ƽ������ ����" << endl;
		cout << "3.���ˣ����ذɡ�" << endl;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			heapsortEnter(placeRelevant,select);
			break;
		case 2:
			heapsortEnter(placeRelevant, select);
			break;
		case 3:
			return;
		default:
			cout << "��������Ŷ~" << endl;
			break;
		}
	}
}