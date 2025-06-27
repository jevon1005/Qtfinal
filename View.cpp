#include "View.h"
#include "QPushButton"
View::View(Person* set, QWidget* parent)
    : QMainWindow()
{
    ui.setupUi(this);

    // 应用深色主题
    this->setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #232629;
            color: #d3dae3;
            font-family: 'Microsoft YaHei', '微软雅黑', Arial, sans-serif;
            font-size: 15px;
        }
        QLabel {
            color: #d3dae3;
            font-weight: bold;
        }
        QLineEdit, QPlainTextEdit, QTextEdit {
            background-color: #232629;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 4px;
            selection-background-color: #3d8ec9;
            selection-color: #fff;
            padding: 4px;
        }
        QLineEdit:read-only {
            background-color: #2b2b2b;
            color: #a0a0a0;
        }
    )");

    ui.ID->setText(QString::fromLocal8Bit(set->GetId()));
    ui.name->setText(QString::fromLocal8Bit(set->GetName()));
    ui.sex->setText(QString::fromLocal8Bit(set->GetSex()));
    ui.phoneNo->setText(QString::fromLocal8Bit(set->GetPhoneNo()));
    ui.address->setText(QString::fromLocal8Bit(set->GetAddress()));
    ui.birthday->setText(QString::fromLocal8Bit(set->GetBirthday().Format()));
    ui.employeeNo->setText(QString::fromLocal8Bit(set->GetEmployeeNo()));
    ui.department->setText(QString::fromLocal8Bit(set->GetDepartment()));
    ui.post->setText(QString::fromLocal8Bit(set->GetPost()));
    ui.salary->setText(QString::number(set->GetSalary()));
}

View::~View()
{

}