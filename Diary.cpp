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

Diary::Diary(){}

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

void Diary::serialize(ofstream& out)const
{
	out.write(reinterpret_cast<const char*>(&id), sizeof(id));

	size_t nameLen = name.size();
	out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	out.write(name.c_str(), nameLen);

	size_t placeLen = place.size();
	out.write(reinterpret_cast<const char*>(&placeLen), sizeof(placeLen));
	out.write(place.c_str(), placeLen);

	out.write(reinterpret_cast<const char*>(&rating), sizeof(rating));
	out.write(reinterpret_cast<const char*>(&ratedSize), sizeof(ratedSize));
	out.write(reinterpret_cast<const char*>(&views), sizeof(views));

	size_t stuNameLen = stuName.size();
	out.write(reinterpret_cast<const char*>(&stuNameLen), sizeof(stuNameLen));
	out.write(stuName.c_str(), stuNameLen);

	size_t stuIdLen = stuId.size();
	out.write(reinterpret_cast<const char*>(&stuIdLen), sizeof(stuIdLen));
	out.write(stuId.c_str(), stuIdLen);

	size_t contentSize = content.size();
	out.write(reinterpret_cast<const char*>(&contentSize), sizeof(contentSize));
	for (const auto& entry : content) {
		size_t entryLen = entry.size();
		out.write(reinterpret_cast<const char*>(&entryLen), sizeof(entryLen));
		out.write(entry.c_str(), entryLen);
	}
}
void Diary::deserialize(ifstream& in)
{
	in.read(reinterpret_cast<char*>(&id), sizeof(id));

	size_t nameLen;
	in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	if (nameLen > in.tellg()) { // ����ȡ�ĳ����Ƿ����
		throw std::length_error("��ȡ�ĳ��ȳ����ļ���С");
	}
	name.resize(nameLen);
	in.read(&name[0], nameLen);

	size_t placeLen;
	in.read(reinterpret_cast<char*>(&placeLen), sizeof(placeLen));
	place.resize(placeLen);
	in.read(&place[0], placeLen);


	in.read(reinterpret_cast<char*>(&rating), sizeof(rating));
	in.read(reinterpret_cast<char*>(&ratedSize), sizeof(ratedSize));
	in.read(reinterpret_cast<char*>(&views), sizeof(views));

	size_t stuNameLen;
	in.read(reinterpret_cast<char*>(&stuNameLen), sizeof(stuNameLen));
	stuName.resize(stuNameLen);
	in.read(&stuName[0], stuNameLen);

	size_t stuIdLen;
	in.read(reinterpret_cast<char*>(&stuIdLen), sizeof(stuIdLen));
	stuId.resize(stuIdLen);
	in.read(&stuId[0], stuIdLen);

	size_t contentSize;
	in.read(reinterpret_cast<char*>(&contentSize), sizeof(contentSize));
	content.resize(contentSize);
	for (size_t i = 0; i < contentSize; ++i) {
		size_t entryLen;
		in.read(reinterpret_cast<char*>(&entryLen), sizeof(entryLen));
		content[i].resize(entryLen);
		in.read(&content[i][0], entryLen);
	}
}