#include "Diary.hpp"

using namespace std;
Diary::Diary(int id,string stuName, string stuId) {
	this->id = id;
	this->views = 0;
	this->rating = 5;//创建时默认评分为5分
	this->ratedSize = 0;
	this->stuName = stuName;
	this->stuId = stuId;
	
	//日记为空
	
	this->compareItem = this->views;
}

Diary::~Diary() {

}

void Diary::showDiary() {
	this->views++;
	cout << "日记编号：" << this->id;
	cout << "\t\t日记名称：" << this->name << endl;
	cout << "作者名：" << this->stuName;
	cout << "\t\t作者学生id：" << this->stuId << endl;
	cout << "游学地点：" << this->place << endl;
	cout << "浏览量：" << this->views;
	printf("\t\t平均评分：%.2f\n", this->rating);//保留2位小数打印！
	cout << "以下为 日记内容：" << endl;
	for (auto& diaryline : this->content){
		cout << diaryline << endl;
	}
	cout << endl;
	while (true) {
		cout << "是否对该日记进行评分？" << endl;
		cout << "1.是的" << endl;
		cout << "2.不必了，我要返回" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "请输入 0-10 内的一个整数来 打分：" << endl;
			int r=5;//同初始默认评分
			while (true) {
				cin >> r;
				if (r >= 0 && r <= 10) {
					break;
				}else {
					cout << "输入有误哦~" << endl;
				}
			}
			this->rating = this->rating * this->ratedSize + r;
			this->ratedSize++;
			this->rating = this->rating / this->ratedSize;//得到了平均评分
			return;
		}else if (select == 2) {
			return;
		}
	}
}

void Diary::showDiarylog() 
{
	cout << endl;
	cout << "日记编号：" << this->id;
	cout << "\t\t日记名称：" << this->name << endl;
	cout << "作者名：" << this->stuName;
	cout << "\t\t作者学生id：" << this->stuId << endl;
	cout << "游学地点：" << this->place << endl;
	cout << "浏览量：" << this->views;
	printf("\t\t平均评分：%.2f\n", this->rating);//保留2位小数打印！
	cout << "---------------------------------" << endl;
}
