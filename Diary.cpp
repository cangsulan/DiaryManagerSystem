#include "Diary.hpp"

using namespace std;
Diary::Diary(int id,string stuName, string stuId) {
	this->views = 0;
	this->rating = 5;//����ʱĬ������Ϊ5��
	this->ratedSize = 0;
	this->stuName = stuName;
	this->stuId = stuId;
	this->content = "";//�ռ�Ϊ��
}
Diary::Diary(int id, string content, string stuName,string stuId) {
	this->views = 0;
	this->content = content;//�ռǲ�Ϊ��ʱ
	this->rating = 5;
	this->ratedSize = 0;
	this->stuName = stuName;
	this->stuId = stuId;
}
Diary::~Diary() {

}
void Diary::showDiary() {
	this->views++;
	cout << "�ռǱ�ţ�" << this->id << endl;
	cout << "��������" << this->stuName << endl;
	cout << "����ѧ��id��" << this->stuId << endl;
	cout << "�������" << this->views;
	cout << "\t\tƽ�����֣�" << this->rating << endl;
	cout << "����Ϊ �ռ����ݣ�" << endl;
	cout << this->content << endl<<endl;
	while (true) {
		cout << "�Ƿ�Ը��ռǽ������֣�" << endl;
		cout << "1.�ǵ�" << endl;
		cout << "2.�����ˣ���Ҫ����" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "������ 0-10 �ڵ�һ�������� ��֣�" << endl;
			int r;
			cin >> r;
			this->rating = this->rating * this->ratedSize + r;
			this->ratedSize++;
			this->rating = this->rating / this->ratedSize;//�õ���ƽ������
			return;
		}else if (select == 2) {
			return;
		}
	}
}