#include "UndoRedo.h"


// 执行撤销操作
bool UndoRedo::undoAction() {
    if (undoStack.empty()) return false;
    operation op = undoStack.top();
    undoStack.pop();
    undoOp(op);
    redoStack.push(op);
    return true;
}

// 执行重做操作
bool UndoRedo::redoAction() {
    if (redoStack.empty()) return false;
    operation op = redoStack.top();
    redoStack.pop();
    redoOp(op);
    undoStack.push(op);
    return true;
}

// 撤销某操作
void UndoRedo::undoOp(operation op) {
    if (!set) return;
    auto& ps = *set;
    switch (op.type) {
    case 1: // 添加操作，撤销时删除
        {
            auto it = op.indexlist.begin();
            auto pit = op.personlist.begin();
            for (; it != op.indexlist.end() && pit != op.personlist.end(); ++it, ++pit) {
                if (*it >= 0 && *it < (int)ps.size()) {
                    ps.erase(ps.begin() + *it);
                }
            }
        }
        break;
    case 2: // 删除操作，撤销时恢复
        {
            auto idxIt = op.indexlist.begin();
            auto personIt = op.personlist.begin();
            for (; idxIt != op.indexlist.end() && personIt != op.personlist.end(); ++idxIt, ++personIt) {
                if (*idxIt >= 0 && *idxIt <= (int)ps.size()) {
                    ps.insert(ps.begin() + *idxIt, *personIt);
                }
            }
        }
        break;
    case 3: // 修改操作，撤销时恢复原值
        if (!op.indexlist.empty() && op.personlist.size() >= 2) {
            int idx = op.indexlist.front();
            if (idx >= 0 && idx < (int)ps.size()) {
                ps[idx] = op.personlist.front(); // 旧值
            }
        }
        break;
    default:
        break;
    }
}

// 重做某操作
void UndoRedo::redoOp(operation op) {
    if (!set) return;
    auto& ps = *set;
    switch (op.type) {
    case 1: // 添加操作，重做时添加
        {
            auto idxIt = op.indexlist.begin();
            auto personIt = op.personlist.begin();
            for (; idxIt != op.indexlist.end() && personIt != op.personlist.end(); ++idxIt, ++personIt) {
                if (*idxIt >= 0 && *idxIt <= (int)ps.size()) {
                    ps.insert(ps.begin() + *idxIt, *personIt);
                }
            }
        }
        break;
    case 2: // 删除操作，重做时删除
        {
            auto it = op.indexlist.rbegin();
            auto pit = op.personlist.rbegin();
            for (; it != op.indexlist.rend() && pit != op.personlist.rend(); ++it, ++pit) {
                if (*it >= 0 && *it < (int)ps.size()) {
                    ps.erase(ps.begin() + *it);
                }
            }
        }
        break;
    case 3: // 修改操作，重做时应用新值
        if (!op.indexlist.empty() && op.personlist.size() >= 2) {
            int idx = op.indexlist.front();
            if (idx >= 0 && idx < (int)ps.size()) {
                ps[idx] = op.personlist.back(); // 新值
            }
        }
        break;
    default:
        break;
    }
}

// 记录操作
void UndoRedo::recordOp(operation op) {
    undoStack.push(op);
    // 新操作后清空 redo 栈
    while (!redoStack.empty()) redoStack.pop();
}
