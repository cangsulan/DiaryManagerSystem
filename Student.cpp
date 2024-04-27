#include "Student.hpp"
Student::Student() {
	this->name = "";
	this->id = "";
}
Student::Student(string name, string id) {
	this->name = name;
	this->id = id;
}
Student::~Student() {

}