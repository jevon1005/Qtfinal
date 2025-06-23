#include "PersonSet.h"
#include "fstream"

PersonSet::PersonSet(void):deque(){

}

PersonSet::~PersonSet(void) {

}

bool PersonSet::push_back(const Person& person) {
	for (auto it = begin(); it != end(); it++)
		if (person == *it)
			return false;
		else deque<Person>::push_back(person);
	return	true;
}

bool PersonSet::push_front(const Person& person) {
	for (auto it = begin(); it != end(); it++)
		if (person == *it)
			return false;
		else deque<Person>::push_front(person);
	return	true;
}

deque<Person>::iterator PersonSet::insert(deque<Person>::iterator i, const Person& person) {
	return deque<Person>::insert(i,person);
}

int PersonSet::ReadFromFile(const char filename[]) {
	int count = 0;
	ifstream fin(filename, ios::in);
	if (fin) {
		Person p;
		while (fin >> p)
		{
			deque<Person>::push_back(p);
			count++;
		}
		fin.close();
	}
	return count;
}

int PersonSet::WriteToFile(const char filename[]) {
	int count = 0;
	ofstream fout(filename);
	if (fout) {
		iterator i;
		for(i = begin();i != end();i++)
		{
			fout << *i;
			count++;
		}
		fout.close();
	}
	return count;
}