#include "PersonInfListDlg.h"
#include "QMessageBox"

PersonInfListDlg::PersonInfListDlg(PersonSet* set, QWidget* parent) 
    :QMainWindow(parent){
    ui.setupUi(this);
    m_pPersonSet = set;
}

void PersonInfListDlg::personTableSetting() {
    //设置表单
    QTableWidget* table = ui.PersonTable;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "身份证" << "姓名" << "性别" << "生日" << "工资");
    QFont font = table->horizontalHeader()->font();
    font.setBold(true);
    table->horizontalHeader()->setFont(font);
    refreshTable();
    ui.PersonTable->resizeColumnsToContents();
    for (int i = 0; i < ui.PersonTable->columnCount(); i++)
    {
        int width = ui.PersonTable->columnWidth(i);
        ui.PersonTable->setColumnWidth(i, width + 50);
    }
}

void PersonInfListDlg::statusBarSetting()
{
    //设置头部导航栏
    QMenuBar* menuBar = ui.menuBar;
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* newAction = fileMenu->addAction("New");
    QAction* openAction = fileMenu->addAction("Open");
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction("close");
}

void PersonInfListDlg::toolBarSetting()
{
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

    connect(addToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "add a new person!"); });
    connect(deleteToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "delete the personnel information!"); });
    connect(viewToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "view more detailed information about the person!"); });
    connect(modifyToolAction, &QAction::triggered, [=]() {QMessageBox::information(this, "info", "modify the personnel information!"); });

}

void PersonInfListDlg::refreshTable()
{
    int i;
    int len = m_pPersonSet->size();
    QTableWidget* table = ui.PersonTable;
    table->setRowCount(len);
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

void PersonInfListDlg::sortPersonInfo()
{

}

void PersonInfListDlg::onRightClickShowMenu(QPoint)
{

}

void PersonInfListDlg::onDisplaySelectedPerson(QString m_pID)
{

}

void PersonInfListDlg::onDisplaySelectedPerson(QTableWidgetItem* item)
{

}

void PersonInfListDlg::onDeletePersonAction(QString m_pID)
{
    QTableWidget* table = ui.PersonTable;
    QList<QTableWidgetItem*> items = table->selectedItems();

}

void PersonInfListDlg::onUpdatePersonAction(QString m_pID)
{

}

void PersonInfListDlg::onAddPersonAction()
{

}




















PersonInfListDlg::~PersonInfListDlg() {

}