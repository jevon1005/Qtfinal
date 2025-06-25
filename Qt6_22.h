#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt6_22.h"
#include "PersonSet.h"
#include "UndoRedo.h"
#include <QDebug>

class Qt6_22 : public QMainWindow
{
    Q_OBJECT

public:
    Qt6_22(PersonSet *set,QWidget *parent = nullptr);
    ~Qt6_22();
    void personTableSetting();
    void statusBarSetting();
    void toolBarSetting();
    void refreshTable();
    void sortPersonInfo();
    void onRightClickShowMenu(QPoint);//
    void onDisplaySelectedPerson(QString m_pID);
    void onDisplaySelectedPerson();
    void onDeletePersonAction();
    void onUpdatePersonAction();
    void onUpdatePersonAction(QString m_pID);//
    void onAddPersonAction();
    void findPersonInfo();
    void findSetting();
    void addSetting();
    void updateUndoRedoState();

//public slots:
//    void onDisplaySelectedPerson();
//    void onDeletePersonAction();
//    void onUpdatePersonAction(QString m_pID);//
//    void onAddPersonAction();//
public:
    PersonSet* m_pPersonSet;
    UndoRedo* m_undoRedo;
private:
    Ui::Qt6_22Class ui;
    QAction* m_undoAction;
    QAction* m_redoAction;
};

