#pragma once
#include "person.h"
#include <deque>
class PersonSet :
	public deque<Person>
{
public:
	PersonSet(void);
public:
	virtual ~PersonSet(void);
public:
	// Overloaded deque::push_back for adding a new Person object at the end of the collection.
	bool push_back(const Person& person);
	// Overloaded deque::push_front for adding a new Person object at the beginning of the collection.
	bool push_front(const Person& person);
	// Overloaded deque::insert for adding a new Person object at the specified position in thecollection.
	deque<Person>::iterator insert(deque<Person>::iterator i, const Person& person = Person());
	// Reads sequentially from the specified file, constructs Person class objects, and adds them to thecollection.
	int ReadFromFile(const char filename[]);
	// Writes the Person class objects in the collection sequentially into the specified file.
	int WriteToFile(const char filename[]);
};
