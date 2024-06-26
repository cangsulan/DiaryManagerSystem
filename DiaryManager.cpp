#include "DiaryManager.hpp"
using namespace std;

DiaryManager::DiaryManager()
{
	
}

DiaryManager::~DiaryManager()
{
	
	delete this->stu;
	for (auto& diaryPtr : this->manager) {
		delete diaryPtr;
	}
}

void DiaryManager::showMenu() 
{
	system("cls");
	
	cout << "------------------------------------------------" << endl;
	//排序展示日记代码
	heapsortEnter(this->manager, 1);
	//
	cout << "这是一个日记管理系统" << endl;
	cout << "以上为当前热度排行榜前10的日记~~~~~~" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1.添加日记" << endl;
	cout << "2.陈列所有日记信息" << endl;
	cout << "3.查询 并 查看日记" << endl;
	cout << "4.目的地 游学日记排序推荐" << endl;
	cout << "5.退出系统" << endl;
	cout << endl;
}

void DiaryManager::addDiary()
{
	Diary* newdiary = new Diary(this->manager.size() + 1,this->stu->name, this->stu->id);
	cout << "请输入日记的 名称：" << endl;
	cin >> newdiary->name;
	cout << "请输入日记所属的 游学地点：" << endl;
	cin >> newdiary->place;
	cout << "请输入您日记的内容：(多行，请输入完后回车，并在新的一行输入 \"eof\" 来结束)" << endl;
	string diaryLine;
	for (cin >> diaryLine; diaryLine != "eof"; cin >> diaryLine) {
		newdiary->content.push_back(diaryLine);
	}
	this->manager.push_back(newdiary);
	cout << "添加成功！" << endl;
}

void DiaryManager::findDiaryById()
{
	cout << "当前共收录有 " << this->manager.size() << " 篇日记，日记编号从1开始" << endl;
	cout << "根据日记编号来查看相应日记，" << endl;
	cout << "请输入要浏览的日记的 编号：" << endl;
	int wanted_id;
	cin >> wanted_id;
	//就是按照编号排，没有乱的话，可以直接根据id找
	if (wanted_id >= 1 && wanted_id <= this->manager.size()) {
		this->manager.at(wanted_id - 1)->showDiary();
	}
	else {
		cout << "对不起，未能找到该 编号 的日记。。。" << endl;
	}
	
	//顺序查找
	/*for (auto diaryPtr : this->manager) {
		if (diaryPtr->id == wanted_id) {
			diaryPtr->showDiary();
			return;
		}
	}*/
	//cout << "对不起，未能找到该 编号 的日记。。。" << endl;
}

void DiaryManager::findDiaryByName()
{
	cout << "当前共收录有 " << this->manager.size() << " 篇日记" << endl;
	cout << "请输入要浏览的日记的 名称：" << endl;
	string wanted_name;
	cin >> wanted_name;
	for (auto diaryPtr : this->manager) {
		if (diaryPtr->name == wanted_name) {
			diaryPtr->showDiary();
			return;
		}
	}
	cout << "对不起，未能找到该日记。。。" << endl;
}

void DiaryManager::showDiaryLogs()
{
	for (auto diaryPtr : this->manager) {
		diaryPtr->showDiarylog();
	}
}

void DiaryManager::sortDiaryOfPlace()
{
	cout << "请输入感兴趣的游学地点：" << endl;
	string wanted_place;
	cin >> wanted_place;
	vector<Diary*> placeRelevant;//把游学地点的日记找出来 放到这个vector里
	int size=0;
	for (auto& diaryPtr : this->manager) {
		if (diaryPtr->place == wanted_place) {
			placeRelevant.push_back(diaryPtr);
		}
	}
	size = placeRelevant.size();
	cout << "已找到 " << size<< " 篇日记！" << endl;
	
	if (size == 0) {
		cout << "没有相关日记，无法推荐。。。" << endl;
		return;
	}
	while (true) {
		cout << "可选择推荐方式：" << endl; //都是用 大根堆 堆排序，排出前10个即可！
		cout << "1.热度 排行" << endl;
		cout << "2.平均评分 排行" << endl;
		cout << "3.行了，返回吧。" << endl;
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
			cout << "输入有误哦~" << endl;
			break;
		}
	}
}

void DiaryManager::CompressedStore()
{
	//先把所有日记进行序列化
	ofstream tempOut("temp.dat", ios::binary);
	for (const auto& diary : this->manager) {
		diary->serialize(tempOut);
	}
	tempOut.close();
	compressAndStore("temp.dat", "CompressedDiaries.dat");
	//生成了压缩后的文件和哈夫曼编码文件，可以删除temp.dat文件了
	remove("temp.dat");
}

void DiaryManager::LoadFromCompressedFile() {
	decompressAndLoad("CompressedDiaries.dat","HafumanCodes.dat", "loadTemp.dat");

	ifstream inStream("loadTemp.dat", ios::binary);
	if (!inStream) {
		cerr << "无法打开文件: " << "loadTemp.dat" << endl;
		return;
	}

	while (inStream.peek() != EOF) {
		Diary* diary = new Diary();
		diary->deserialize(inStream);
		this->manager.push_back(diary);
	}

	inStream.close();
	//已经把所有数据都读取完了，现在可以删除所有有关的文件
	remove("CompressedDiaries.dat");
	remove("HafumanCodes.dat");
	remove("loadTemp.dat");

}