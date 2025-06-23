#pragma once
#include "date.h"

class Person
{
public:
    // Constructor
    Person(void);

public:
    // Destructor
    virtual ~Person(void);

public:
    // Overloaded operator() for setting properties of Person object
    void operator()(string id, string name, string sex,
        string phoneNo, string address, Date& birthday,
        string employeeNo, string department, string post, double salary);

    // Overloaded comparison operators for comparison operations of Person objects
    friend bool operator !=(Person person1, Person person2);
    friend bool operator ==(Person person1, Person person2);
    friend bool operator <(Person person1, Person person2);
    friend bool operator >(Person person1, Person person2);
    friend bool operator <=(Person person1, Person person2);
    friend bool operator >=(Person person1, Person person2);

    // Property setting operations
    void SetId(string Id);
    void SetName(string Name);
    void SetSex(string Sex);
    void SetPhoneNo(string PhoneNo);
    void SetAddress(string Address);
    void SetBirthday(const Date& Birthday);
    void SetEmployeeNo(string EmployeeNo);
    void SetDepartment(string Department);
    void SetPost(string Post);
    void SetSalary(double Salary);

    // Property getting operations
    string GetId();
    string GetName();
    string GetSex();
    string GetPhoneNo();
    string GetAddress();
    Date GetBirthday();
    string GetEmployeeNo();
    string GetDepartment();
    string GetPost();
    double GetSalary();

    // Overloaded standard input operator>> and operator<< for I/O operations of Person object
    friend istream& operator >> (istream& in, Person& person);
    friend ostream& operator<<(ostream& out, Person& person);

protected:
    string id; // ID number
    string name; // Name
    string sex; // Sex
    string phoneNo; // Phone number
    string address; // Home address
    Date birthday; // Date of birth
    string employeeNo; // Employee number
    string department; // Department
    string post; // Position
    double salary; // Salary
};