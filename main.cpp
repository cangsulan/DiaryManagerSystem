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
		cout << "�����Ӧ������ѡ����:" << endl;
		cin.ignore(INT_MAX, '\n');//��� ���뻺����
		int select = 0;
		scanf_s("%d", &select);//�ĳ�cin���������⣡����
		switch (select)
		{
		case 1://����ռ�
			diarymanager.addDiary();
			system("pause");
			break;
		case 2://���������ռǵĻ�����Ϣ
			diarymanager.showDiaryLogs();
			system("pause");
			break;
		case 3://��ѯ �� �鿴�ռ�
			while (true) {
				cout << "ѡ���ѯ��ʽ��" << endl;
				cout << "1.ͨ�� ���" << endl;
				cout << "2.ͨ�� ���� ��׼��ѯ" << endl;
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
					cout << "��������Ŷ~" << endl << endl;
				}
			}
			system("pause");
			break;
		case 4://Ŀ�ĵ� ��ѧ�ռ������Ƽ�
			diarymanager.sortDiaryOfPlace();
			system("pause");
			break;
		case 5://�˳�ϵͳ
			system("pause");
			return 0;
		default:
			cout << "������󣡣�" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}