#pragma once
#include "person.h"
#include <stack>
#include <list>
#include <algorithm>
#include "PersonSet.h"
using namespace std;

typedef struct {
	int type; // �������ͣ����� 1-��ӣ�2-ɾ����3-�޸�
	list<Person> personlist;
	list<int> indexlist; // ��Ӧλ����������ѡ��
} operation;

class UndoRedo {
public:
	bool undoAction(); // ִ�г�������,���� undo ջ���Ĳ��������� undoOp(op) ������Ȼ�󽫴˲���ѹ�� redo ջ��
	bool redoAction(); // ִ����������,���� redo ջ���Ĳ��������� redoOp(op) ������Ȼ�󽫴˲�������ѹ�� undo ջ
	void undoOp(operation op); // ����ĳ����
	void redoOp(operation op); // ����ĳ����,ÿ��ִ����ɾ�Ĳ���ʱ�����ô˺�����¼��ǰ������ѹ�� undo ջ����� redo ջ��
	void recordOp(operation op); // ��¼����
	stack<operation> undoStack; // ��������ջ
	stack<operation> redoStack; // ��������ջ
	PersonSet* set; // ָ�������ݶ���
};