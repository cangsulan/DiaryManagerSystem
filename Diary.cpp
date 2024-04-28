#include "Diary.hpp"

using namespace std;
Diary::Diary(int id,string stuName, string stuId) {
	this->id = id;
	this->views = 0;
	this->rating = 5;//����ʱĬ������Ϊ5��
	this->ratedSize = 0;
	this->stuName = stuName;
	this->stuId = stuId;
	
	//�ռ�Ϊ��
	
	this->compareItem = this->views;
}

Diary::~Diary() {

}

void Diary::showDiary() {
	this->views++;
	cout << "�ռǱ�ţ�" << this->id;
	cout << "\t\t�ռ����ƣ�" << this->name << endl;
	cout << "��������" << this->stuName;
	cout << "\t\t����ѧ��id��" << this->stuId << endl;
	cout << "��ѧ�ص㣺" << this->place << endl;
	cout << "�������" << this->views;
	printf("\t\tƽ�����֣�%.2f\n", this->rating);//����2λС����ӡ��
	cout << "����Ϊ �ռ����ݣ�" << endl;
	for (auto& diaryline : this->content){
		cout << diaryline << endl;
	}
	cout << endl;
	while (true) {
		cout << "�Ƿ�Ը��ռǽ������֣�" << endl;
		cout << "1.�ǵ�" << endl;
		cout << "2.�����ˣ���Ҫ����" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "������ 0-10 �ڵ�һ�������� ��֣�" << endl;
			int r=5;//ͬ��ʼĬ������
			while (true) {
				cin >> r;
				if (r >= 0 && r <= 10) {
					break;
				}else {
					cout << "��������Ŷ~" << endl;
				}
			}
			this->rating = this->rating * this->ratedSize + r;
			this->ratedSize++;
			this->rating = this->rating / this->ratedSize;//�õ���ƽ������
			return;
		}else if (select == 2) {
			return;
		}
	}
}

void Diary::showDiarylog() 
{
	cout << endl;
	cout << "�ռǱ�ţ�" << this->id;
	cout << "\t\t�ռ����ƣ�" << this->name << endl;
	cout << "��������" << this->stuName;
	cout << "\t\t����ѧ��id��" << this->stuId << endl;
	cout << "��ѧ�ص㣺" << this->place << endl;
	cout << "�������" << this->views;
	printf("\t\tƽ�����֣�%.2f\n", this->rating);//����2λС����ӡ��
	cout << "---------------------------------" << endl;
}
