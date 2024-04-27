#include "Diary.hpp"

using namespace std;
Diary::Diary(int id,string stuName, string stuId) {
	this->views = 0;
	this->rating = 5;//创建时默认评分为5分
	this->ratedSize = 0;
	this->stuName = stuName;
	this->stuId = stuId;
	this->content = "";//日记为空
}
Diary::Diary(int id, string content, string stuName,string stuId) {
	this->views = 0;
	this->content = content;//日记不为空时
	this->rating = 5;
	this->ratedSize = 0;
	this->stuName = stuName;
	this->stuId = stuId;
}
Diary::~Diary() {

}
void Diary::showDiary() {
	this->views++;
	cout << "日记编号：" << this->id << endl;
	cout << "作者名：" << this->stuName << endl;
	cout << "作者学生id：" << this->stuId << endl;
	cout << "浏览量：" << this->views;
	cout << "\t\t平均评分：" << this->rating << endl;
	cout << "以下为 日记内容：" << endl;
	cout << this->content << endl<<endl;
	while (true) {
		cout << "是否对该日记进行评分？" << endl;
		cout << "1.是的" << endl;
		cout << "2.不必了，我要返回" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "请输入 0-10 内的一个整数来 打分：" << endl;
			int r;
			cin >> r;
			this->rating = this->rating * this->ratedSize + r;
			this->ratedSize++;
			this->rating = this->rating / this->ratedSize;//得到了平均评分
			return;
		}else if (select == 2) {
			return;
		}
	}
}