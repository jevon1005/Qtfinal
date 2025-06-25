#pragma once
#include "person.h"
#include <stack>
#include <list>
#include <algorithm>
#include "PersonSet.h"
using namespace std;

typedef struct {
	int type; // 操作类型，例如 1-添加，2-删除，3-修改
	list<Person> personlist;
	list<int> indexlist; // 对应位置索引（可选）
} operation;

class UndoRedo {
public:
	bool undoAction(); // 执行撤销操作,弹出 undo 栈顶的操作并调用 undoOp(op) 撤销；然后将此操作压入 redo 栈。
	bool redoAction(); // 执行重做操作,弹出 redo 栈顶的操作并调用 redoOp(op) 重做；然后将此操作重新压入 undo 栈
	void undoOp(operation op); // 撤销某操作
	void redoOp(operation op); // 重做某操作,每次执行增删改操作时，调用此函数记录当前操作，压入 undo 栈，清空 redo 栈。
	void recordOp(operation op); // 记录操作
	stack<operation> undoStack; // 撤销操作栈
	stack<operation> redoStack; // 重做操作栈
	PersonSet* set; // 指向主数据对象
};