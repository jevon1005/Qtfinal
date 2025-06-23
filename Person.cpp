#include "Person.h"

Person::Person(void) {
	this->id = "unknow";
	this->name = "unknow";
	this->sex = "unknow";
	this->phoneNo = "unknow";
	this->address = "unknow";
	this->birthday = Date();
	this->employeeNo = "unknow";
	this->department = "unknow";
	this->post = "unknow";
	this->salary = 0.0;
}

Person::~Person(void) {

}

void Person::operator()(string id, string name, string sex,
	string phoneNo, string address, Date& birthday,
	string employeeNo, string department, string post, double salary) {
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->phoneNo = phoneNo;
	this->address = address;
	this->birthday = birthday;
	this->employeeNo = employeeNo;
	this->department = department;
	this->post = post;
	this->salary = 0.0;
}

bool operator !=(Person person1, Person person2) {
	return person1.id != person2.id;
}

bool operator ==(Person person1, Person person2) {
    return person1.id == person2.id;
}

bool operator <(Person person1, Person person2) {
    return person1.id < person2.id;
}

bool operator >(Person person1, Person person2) {
    return person1.id > person2.id;
}

bool operator <=(Person person1, Person person2) {
    return person1.id <= person2.id;
}

bool operator >=(Person person1, Person person2) {
    return person1.id >= person2.id;
}

void Person::SetId(string Id) {
    this->id = Id;
}

void Person::SetName(string Name) {
    this->name = Name;
}

void Person::SetSex(string Sex) {
    this->sex = Sex;
}

void Person::SetPhoneNo(string PhoneNo) {
    this->phoneNo = PhoneNo;
}

void Person::SetAddress(string Address) {
    this->address = Address;
}

void Person::SetBirthday(const Date& Birthday) {
    this->birthday = Birthday;
}

void Person::SetEmployeeNo(string EmployeeNo) {
    this->employeeNo = EmployeeNo;
}

void Person::SetDepartment(string Department) {
    this->department = Department;
}

void Person::SetPost(string Post) {
    this->post = Post;
}

void Person::SetSalary(double Salary) {
    this->salary = Salary;
}


string Person::GetId() {
    return this->id;
}

string Person::GetName() {
    return this->name;
}

string Person::GetSex() {
    return this->sex;
}

string Person::GetPhoneNo() {
    return this->phoneNo;
}

string Person::GetAddress() {
    return this->address;
}

Date Person::GetBirthday() {
    return this->birthday;
}

string Person::GetEmployeeNo() {
    return this->employeeNo;
}

string Person::GetDepartment() {
    return this->department;
}

string Person::GetPost() {
    return this->post;
}

double Person::GetSalary() {
    return this->salary;
}

istream& operator >> (istream& in, Person& person) {
    in >> person.id
       >> person.name
       >> person.sex
       >> person.birthday
       >> person.address
       >> person.phoneNo
       >> person.employeeNo
       >> person.department
       >> person.post
       >> person.salary;
    return in;
}

ostream& operator<<(ostream& out, Person& person) {
    out << person.id << "\n"
        << person.name << "\n"
        << person.sex << "\n"
        << person.birthday << "\n"
        << person.address << "\n"
        << person.phoneNo << "\n"
        << person.employeeNo << "\n"
        << person.department << "\n"
        << person.post << "\n"
        << person.salary<<"\n";
    return out;
}
