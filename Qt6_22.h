#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt6_22.h"
#include "PersonSet.h"

class Qt6_22 : public QMainWindow
{
    Q_OBJECT

public:
    Qt6_22(PersonSet *set,QWidget *parent = nullptr);
    ~Qt6_22();
    void PersonTableSetting();
    void RefreshTable(PersonSet* set);

private:
    Ui::Qt6_22Class ui; 
    PersonSet *m_pPersonSet;
};

