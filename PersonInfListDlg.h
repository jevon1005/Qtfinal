#pragma once
#include "D:\Qt\6.7.3\msvc2022_64\include\QtWidgets\qmainwindow.h"
#include <PersonSet.h>
#include "QTableWidgetItem"
#include "ui_Qt6_22.h"

class PersonInfListDlg :
    public QMainWindow
{
    Q_OBJECT
public:
    PersonInfListDlg(PersonSet* set, QWidget* parent = nullptr);
    ~PersonInfListDlg();
public slots:
    void personTableSetting();
    void statusBarSetting();
    void toolBarSetting();
    void refreshTable();
    void sortPersonInfo();
    void onRightClickShowMenu(QPoint);
    void onDisplaySelectedPerson(QString m_pID);
    void onDisplaySelectedPerson(QTableWidgetItem* item);
    void onDeletePersonAction(QString m_pID);
    void onUpdatePersonAction(QString m_pID);
    void onAddPersonAction();
public:
    PersonSet* m_pPersonSet;
private:
    Ui::Qt6_22Class ui;
};

