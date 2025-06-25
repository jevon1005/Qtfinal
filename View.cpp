#include "View.h"
#include "QPushButton"
View::View(Person* set, QWidget* parent)
    : QMainWindow()
{
    ui.setupUi(this);

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