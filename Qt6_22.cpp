#include "Qt6_22.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include "Date.h"
#include "Person.h"
#include "PersonSet.h"
#include <qtablewidget.h>
#include <qlabel.h>
#include <qtimer.h>
#include <QDatetime.h>

Qt6_22::Qt6_22(PersonSet *set,QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_pPersonSet = set;
    PersonTableSetting();
}

void Qt6_22::PersonTableSetting()
{
    //设置头部导航栏
    QMenuBar* menuBar = ui.menuBar;
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* newAction = fileMenu->addAction("New");
    QAction* openAction = fileMenu->addAction("Open");
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction("close");

    //设置工具导航栏
    ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QAction* addToolAction = new QAction(QIcon(":/new/prefix1/icon/add.png"), "add", this);
    QAction* deleteToolAction = new QAction(QIcon(":/new/prefix1/icon/delete.png"), "delete", this);
    QAction* viewToolAction = new QAction(QIcon(":/new/prefix1/icon/view.png"), "view", this);
    QAction* modifyToolAction = new QAction(QIcon(":/new/prefix1/icon/modify.png"), "modify", this);

    ui.mainToolBar->addAction(addToolAction);
    ui.mainToolBar->addAction(deleteToolAction);
    ui.mainToolBar->addAction(viewToolAction);
    ui.mainToolBar->addAction(modifyToolAction);

    connect(addToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "add a new person!");});
    connect(deleteToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "delete the personnel information!");});
    connect(viewToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "view more detailed information about the person!");});
    connect(modifyToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "modify the personnel information!");});

    //设置表单
    QTableWidget* table = ui.PersonTable;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnCount(5);
    int len = m_pPersonSet->size();
    table->setRowCount(len);
    table->setHorizontalHeaderLabels(QStringList() << "身份证" << "姓名" << "性别" << "生日" << "工资");
    QFont font = table->horizontalHeader()->font();
    font.setBold(true);
    table->horizontalHeader()->setFont(font);
    RefreshTable(m_pPersonSet);
    ui.PersonTable->resizeColumnsToContents();
    for (int i = 0; i < ui.PersonTable->columnCount(); i++)
    {
        int width = ui.PersonTable->columnWidth(i);
        ui.PersonTable->setColumnWidth(i, width + 50);
    }

    //设置底部状态栏
    ui.statusBar->addPermanentWidget(new QLabel("Capital Normal University", this));
    QLabel* timeLabel = new QLabel;
    ui.statusBar->addWidget(timeLabel);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [timeLabel]() {
        QDateTime dateTime = QDateTime::currentDateTime();
        timeLabel->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss"));
        });
    timer->start(1000);
}


void Qt6_22::RefreshTable(PersonSet* set)
{
    int i;
    int len = m_pPersonSet->size();
    QTableWidget* table = ui.PersonTable;
    for (int row = 0; row < len; row++)
    {
        Person& person = m_pPersonSet->at(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit(person.GetId())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromLocal8Bit(person.GetName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromLocal8Bit(person.GetSex())));
        string year = to_string(person.GetBirthday().GetYear() / 100);
        string birthday = year + person.GetBirthday().Format();
        table->setItem(row, 3, new QTableWidgetItem(QString::fromLocal8Bit(birthday)));
        //table->setItem(row, 4, new QTableWidgetItem(QString::fromLocal8Bit(person.GetAddress())));
        //table->setItem(row, 5, new QTableWidgetItem(QString::fromLocal8Bit(person.GetPhoneNo())));
        //table->setItem(row, 6, new QTableWidgetItem(QString::fromLocal8Bit(person.GetEmployeeNo())));
        //table->setItem(row, 7, new QTableWidgetItem(QString::fromLocal8Bit(person.GetDepartment())));
        //table->setItem(row, 8, new QTableWidgetItem(QString::fromLocal8Bit(person.GetPost().c_str())));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(person.GetSalary(), 'f', 2)));
    }
}
Qt6_22::~Qt6_22()
{}

//排序，增删改查