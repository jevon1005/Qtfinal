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
	this->salary = salary;
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


string Person::GetId() const{
    return this->id;
}

string Person::GetName() const{
    return this->name;
}

string Person::GetSex() const{
    return this->sex;
}

string Person::GetPhoneNo() const{
    return this->phoneNo;
}

string Person::GetAddress() const{
    return this->address;
}

Date Person::GetBirthday() const{
    return this->birthday;
}

string Person::GetEmployeeNo() const{
    return this->employeeNo;
}

string Person::GetDepartment() const{
    return this->department;
}

string Person::GetPost() const{
    return this->post;
}

double Person::GetSalary() const{
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
