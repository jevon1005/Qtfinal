#pragma once

#include <QObject>
#include <QtWidgets/QMainWindow>
#include "ui_view.h"
#include "PersonSet.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Person* set, QWidget* parent = nullptr);
    ~View();

private:
    Ui::ViewClass ui;
};
