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
#include "View.h"
#include "PersonChange.h"
#include <set>
#include <QFileDialog>
#include "QCloseEvent"

Qt6_22::Qt6_22(PersonSet *set,QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_pPersonSet = set;
    m_undoRedo = new UndoRedo();
    m_undoRedo->set = m_pPersonSet;  //让UndoRedo操作主数据

    personTableSetting();   
    statusBarSetting();
    toolBarSetting();
    refreshTable();

    // 初始化背景音乐
    m_backgroundMusic = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_backgroundMusic->setAudioOutput(m_audioOutput);
    m_backgroundMusic->setSource(QUrl::fromLocalFile("backgroundmusic.mp3"));
    m_audioOutput->setVolume(0.3); // 设置音量为30%
    m_backgroundMusic->setLoops(QMediaPlayer::Infinite); // 循环播放
    m_backgroundMusic->play();

    // 应用深色主题
    this->setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #232629;
            color: #d3dae3;
            font-family: 'Microsoft YaHei', '微软雅黑', Arial, sans-serif;
            font-size: 15px;
        }
        QMenuBar {
            background-color: #232629;
            color: #d3dae3;
        }
        QMenuBar::item {
            background: transparent;
            color: #d3dae3;
        }
        QMenuBar::item:selected {
            background: #31363b;
        }
        QMenu {
            background-color: #232629;
            color: #d3dae3;
            border: 1px solid #444;
        }
        QMenu::item:selected {
            background: #31363b;
        }
        QToolBar {
            background: #232629;
            border-bottom: 1px solid #444;
        }
        QStatusBar {
            background: #232629;
            color: #d3dae3;
        }
        QTableWidget {
            background-color: #2b2b2b;
            color: #d3dae3;
            gridline-color: #444;
            selection-background-color: #3d8ec9;
            selection-color: #fff;
            border: 1px solid #444;
        }
        QHeaderView::section {
            background-color: #31363b;
            color: #d3dae3;
            border: 1px solid #444;
            font-weight: bold;
        }
        QLineEdit, QPlainTextEdit, QTextEdit {
            background-color: #232629;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 4px;
            selection-background-color: #3d8ec9;
            selection-color: #fff;
        }
        QPushButton {
            background-color: #31363b;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 6px;
            padding: 6px 12px;
        }
        QPushButton:hover {
            background-color: #3d8ec9;
            color: #fff;
        }
        QCheckBox, QRadioButton {
            color: #d3dae3;
        }
        QCheckBox::indicator, QRadioButton::indicator {
            border: 1px solid #444;
            background: #232629;
        }
        QCheckBox::indicator:checked, QRadioButton::indicator:checked {
            background: #3d8ec9;
            border: 1px solid #3d8ec9;
        }
    )");

    //m_player = new QMediaPlayer(this);
    //m_audioOutput = new QAudioOutput(this);
    //m_player->setAudioOutput(m_audioOutput);
    //m_player->setSource(QUrl::fromLocalFile("backgroundmusic.mp3")); // 音乐文件名
    //m_audioOutput->setVolume(0.2); // 音量0~1之间
    //m_player->play();
}

void Qt6_22::personTableSetting() {
    //设置表单
    QTableWidget* table = ui.PersonTable;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "身份证" << "姓名" << "性别" << "生日" << "工资");
    QFont font = table->horizontalHeader()->font();
    font.setBold(true);
    table->horizontalHeader()->setFont(font);
    refreshTable();
    // 设置QTableWidget的属性，使其可以弹出上下文菜单
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    // 连接QTableWidget的customContextMenuRequested信号到槽函数
    connect(table, &QTableWidget::customContextMenuRequested, this, &Qt6_22::onRightClickShowMenu);
    ui.PersonTable->resizeColumnsToContents();
    for (int i = 0; i < ui.PersonTable->columnCount(); i++)
    {
        int width = ui.PersonTable->columnWidth(i);
        ui.PersonTable->setColumnWidth(i, width + 50);
    }
    sortPersonInfo();   //排序

    findSetting();  //查找
}

void Qt6_22::findSetting() {

    QTableWidget* table = ui.PersonTable;
    connect(ui.find, &QPushButton::clicked, this, &Qt6_22::findPersonInfo);
    connect(ui.textFind, &QLineEdit::returnPressed, this, &Qt6_22::findPersonInfo);

    // 设置find和textFind的可用状态
    bool enabled = ui.checkBoxFind->isChecked();
    ui.find->setEnabled(enabled);
    ui.textFind->setEnabled(enabled);

    // 连接checkBoxFind的状态变化信号
    connect(ui.checkBoxFind, &QCheckBox::stateChanged, this, [=](int state) {
        bool checked = (state == Qt::Checked);
        ui.find->setEnabled(checked);
        ui.textFind->setEnabled(checked);
        if (!checked)
        {
            ui.textFind->clear();
            for (int i = 0; i < m_pPersonSet->size(); i++)
                table->setRowHidden(i, false);
        }
    });
}

void Qt6_22::statusBarSetting()
{
    //设置头部导航栏
    QMenuBar* menuBar = ui.menuBar;
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* newAction = fileMenu->addAction("New");
    QAction* openAction = fileMenu->addAction("Open");
    QAction* saveAction = fileMenu->addAction("Save"); // 新增保存
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction("Close");

    connect(newAction, &QAction::triggered, this, &Qt6_22::onNewFile);
    connect(openAction, &QAction::triggered, this, &Qt6_22::onOpenFile);
    connect(saveAction, &QAction::triggered, this, &Qt6_22::onSaveFile); // 连接保存
    connect(closeAction, &QAction::triggered, this, &Qt6_22::onCloseFile);
}

void Qt6_22::toolBarSetting()
{
    //设置工具导航栏
    ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QAction* addToolAction = new QAction(QIcon(":/new/prefix1/icon/add.png"), "add", this);
    QAction* deleteToolAction = new QAction(QIcon(":/new/prefix1/icon/delete.png"), "delete", this);
    QAction* viewToolAction = new QAction(QIcon(":/new/prefix1/icon/view.png"), "view", this);
    QAction* modifyToolAction = new QAction(QIcon(":/new/prefix1/icon/modify.png"), "modify", this);
    m_undoAction = new QAction(QIcon(":/new/prefix1/icon/undo.png"), "undo", this);
    m_redoAction = new QAction(QIcon(":/new/prefix1/icon/redo.png"), "redo", this);

    // 添加音乐控制按钮
    QAction* musicToggleAction = new QAction("🎵 音乐", this);
    musicToggleAction->setCheckable(true);
    musicToggleAction->setChecked(true);

    ui.mainToolBar->addAction(addToolAction);
    ui.mainToolBar->addAction(deleteToolAction);
    ui.mainToolBar->addAction(viewToolAction);
    ui.mainToolBar->addAction(modifyToolAction);
    ui.mainToolBar->addAction(m_undoAction);
    ui.mainToolBar->addAction(m_redoAction);
    ui.mainToolBar->addSeparator();
    ui.mainToolBar->addAction(musicToggleAction);

    connect(addToolAction, &QAction::triggered, this, &Qt6_22::onAddPersonAction);
    connect(deleteToolAction, &QAction::triggered,this, &Qt6_22::onDeletePersonAction);
    connect(viewToolAction, &QAction::triggered, this, [=]() {
        onDisplaySelectedPerson();
        });
    connect(modifyToolAction, &QAction::triggered,this, [=]() {
        onUpdatePersonAction();
        });
    connect(m_undoAction, &QAction::triggered, this, [=]() {
        if (m_undoRedo->undoAction()) {
            refreshTable();
            updateUndoRedoState();
        }
    });
    connect(m_redoAction, &QAction::triggered, this, [=]() {
        if (m_undoRedo->redoAction()) {
            refreshTable();
            updateUndoRedoState();
        }
    });

    // 音乐控制连接
    connect(musicToggleAction, &QAction::toggled, this, [=](bool checked) {
        if (checked) {
            m_backgroundMusic->play();
            musicToggleAction->setText("🎵 音乐");
        } else {
            m_backgroundMusic->pause();
            musicToggleAction->setText("🔇 音乐");
        }
    });

    // 初始化按钮状态
    updateUndoRedoState();
}

void Qt6_22::refreshTable()
{
    int len = m_pPersonSet->size();
    QTableWidget* table = ui.PersonTable;

    table->setSortingEnabled(false);

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

    table->setSortingEnabled(true);

}

void Qt6_22::sortPersonInfo()
{
    QTableWidget* table = ui.PersonTable;
    table->setSortingEnabled(true);
    refreshTable();
}

void Qt6_22::onRightClickShowMenu(QPoint pos)
{
    QTableWidgetItem* item = ui.PersonTable->itemAt(pos);
    if (item != nullptr)
    {
        QMenu* menu = new QMenu(this);
        QAction* addToolAction = new QAction(QIcon(":/new/prefix1/icon/add.png"), "add", this);
        QAction* deleteToolAction = new QAction(QIcon(":/new/prefix1/icon/delete.png"), "delete", this);
        QAction* viewToolAction = new QAction(QIcon(":/new/prefix1/icon/view.png"), "view", this);
        QAction* modifyToolAction = new QAction(QIcon(":/new/prefix1/icon/modify.png"), "modify", this);

        connect(addToolAction, &QAction::triggered, this, &Qt6_22::onAddPersonAction);
        connect(deleteToolAction, &QAction::triggered, this, &Qt6_22::onDeletePersonAction);
        connect(viewToolAction, &QAction::triggered, this, [=]() {
            onDisplaySelectedPerson();
            });
        connect(modifyToolAction, &QAction::triggered, this, [=]() {
            onUpdatePersonAction();
            });
        menu->addAction(addToolAction);
        menu->addAction(deleteToolAction);
        menu->addAction(viewToolAction);
        menu->addAction(modifyToolAction);
        menu->popup(ui.PersonTable->viewport()->mapToGlobal(pos));
    }
}

void Qt6_22::onDisplaySelectedPerson(QString m_pID)
{
    Person selectedperson;
    selectedperson.SetId(m_pID.toStdString());
    for (auto iter = m_pPersonSet->begin(); iter != m_pPersonSet->end(); ++iter)
    {
        if (*iter == selectedperson)
        {
            // 传递容器中对象的地址
            View* view = new View(&(*iter), this);
            view->setAttribute(Qt::WA_DeleteOnClose);
            view->show();

            break; // 找到后可以退出循环
        }
    }
}

void Qt6_22::onDisplaySelectedPerson()
{
    QTableWidget* table = ui.PersonTable;
    QList<QTableWidgetItem*> selecteditems = table->selectedItems();
    QString m_PID,m_Name;
    if (selecteditems.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要查看的人员信息！");
        return;
    }
    else
    {
        Person person;
        int row;
        row = selecteditems.at(0)->row();
        QTableWidgetItem* firstItem = table->item(row, 0);
        QTableWidgetItem* nameItem = table->item(row, 1);
        m_PID = firstItem->text();
        m_Name = nameItem->text();
        string hinttexxt = "确定查看" + m_Name.toStdString() + "吗";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "查看人员", "确定查看成员吗", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        else onDisplaySelectedPerson(m_PID);
    }
}

void Qt6_22::onDeletePersonAction()
{
    QTableWidget* table = ui.PersonTable;
    QList<QTableWidgetItem*> selecteditems = table->selectedItems();
    if (selecteditems.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的人员信息！");
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "删除人员", "确定删除成员吗", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return;

    operation op;
    op.type = 2; // 删除
    std::set<int> rows; // 存储内存中的真实序号

    // 通过选中项的身份证号，查找内存中的序号
    std::set<std::string> selectedIds;
    for (auto item : selecteditems) {
        int row = item->row();
        QTableWidgetItem* idItem = table->item(row, 0);
        if (idItem) {
            selectedIds.insert(idItem->text().toStdString());
        }
    }

    for (int i = 0; i < m_pPersonSet->size(); ++i) {
        const Person& person = m_pPersonSet->at(i);
        if (selectedIds.count(person.GetId()) > 0) {
            rows.insert(i);
        }
    }

    // 逆序删除，防止下标错乱
    std::vector<int> sortedRows(rows.begin(), rows.end());
    std::sort(sortedRows.rbegin(), sortedRows.rend());
    for (int row : sortedRows) {
        Person person = m_pPersonSet->at(row);
        op.indexlist.push_front(row);
        op.personlist.push_front(person);
        m_pPersonSet->erase(m_pPersonSet->begin() + row);
    }
    if (!op.indexlist.empty())
        m_undoRedo->recordOp(op);
    refreshTable();
    updateUndoRedoState();

    // 检查是否执行过查找操作，若是则再次执行查找刷新表格
    if (ui.checkBoxFind->isChecked() && !ui.textFind->text().isEmpty()) {
        findPersonInfo();
    }

    setModified(true); //删除后标记为已修改
}

void Qt6_22::onUpdatePersonAction()
{
    QTableWidget* table = ui.PersonTable;
    QList<QTableWidgetItem*> selecteditems = table->selectedItems();
    QString m_PID, m_Name;
    if (selecteditems.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要修改的人员信息！");
        return;
    }
    else
    {
        Person person;
        int row;
        row = selecteditems.at(0)->row();
        QTableWidgetItem* firstItem = table->item(row, 0);
        QTableWidgetItem* nameItem = table->item(row, 1);
        m_PID = firstItem->text();
        m_Name = nameItem->text();
        string hinttexxt = "确定修改" + m_Name.toStdString() + "吗";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "修改人员", "确定修改成员吗", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        else 
        {
            onUpdatePersonAction(m_PID);
            setModified(true);
        }
    }
}

void Qt6_22::onUpdatePersonAction(QString m_pID)
{
    for (int i = 0; i < m_pPersonSet->size(); i++) {
        if (QString::fromStdString(m_pPersonSet->at(i).GetId()) == m_pID) {
            Person oldPerson = m_pPersonSet->at(i);
            PersonChange* personChange = new PersonChange(&m_pPersonSet->at(i), this);
            personChange->setAttribute(Qt::WA_DeleteOnClose);
            personChange->show();
            connect(personChange, &QDialog::accepted, this, [=]() {
                Person newPerson = m_pPersonSet->at(i);

                // 手动比较所有关键字段
                bool isChanged = false;
                if (
                    oldPerson.GetName() != newPerson.GetName() ||
                    oldPerson.GetAddress() != newPerson.GetAddress() ||
                    oldPerson.GetPhoneNo() != newPerson.GetPhoneNo() ||
                    oldPerson.GetEmployeeNo() != newPerson.GetEmployeeNo() ||
                    oldPerson.GetDepartment() != newPerson.GetDepartment() ||
                    oldPerson.GetPost() != newPerson.GetPost() ||
                    oldPerson.GetSalary() != newPerson.GetSalary()
                ) {
                    isChanged = true;
                }

                if (isChanged) {
                    operation op;
                    op.type = 3;
                    op.indexlist.push_back(static_cast<int>(i));
                    op.personlist.push_back(oldPerson);
                    op.personlist.push_back(newPerson);
                    m_undoRedo->recordOp(op);
                }
                refreshTable();
                updateUndoRedoState();
            });
            connect(personChange, &QDialog::rejected, this, [=]() {
                qDebug() << "Dialog rejected";
            });
            break;
        }
    }
}

void Qt6_22::onAddPersonAction()
{
    int oldSize = m_pPersonSet->size();
    PersonChange* personChange = new PersonChange(m_pPersonSet, this);
    personChange->setAttribute(Qt::WA_DeleteOnClose);
    personChange->show();
    connect(personChange, &QDialog::destroyed, this, [=]() {
        if (m_pPersonSet->size() > oldSize) {
            operation op;
            op.type = 1;
            op.indexlist.push_back(0);
            op.personlist.push_back(m_pPersonSet->front());
            m_undoRedo->recordOp(op);
        }
        refreshTable();
        updateUndoRedoState(); 
    });
    setModified(true);
}

void Qt6_22::findPersonInfo()
{
    QString str = ui.textFind->text();
    if (str.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入要查找的内容！");
        return;
    }

    QTableWidget* table = ui.PersonTable;
    QList<QTableWidgetItem*> findItems = table->findItems(str, Qt::MatchContains);
    int row;
    for (int j = 0; j < m_pPersonSet->size(); j++)//全部隐藏
        table->setRowHidden(j, true);
    for (int i = 0; i < findItems.size(); i++)  //显示找到的
    {
        row = findItems.at(i)->row();
        table->setRowHidden(row, false);
    }
}

void Qt6_22::updateUndoRedoState()
{
    m_undoAction->setEnabled(!m_undoRedo->undoStack.empty());
    m_redoAction->setEnabled(!m_undoRedo->redoStack.empty());
}

void Qt6_22::onNewFile()
{
    if (!maybeSave()) return;

    QString fileName = QFileDialog::getSaveFileName(this, "新建数据文件", "", "Data Files (*.dat);;All Files (*)");
    if (fileName.isEmpty()) return;

    m_pPersonSet->clear();
    m_currentFileName = fileName;
    m_pPersonSet->WriteToFile(m_currentFileName.toStdString().c_str());
    refreshTable();
    setModified(false);
}

void Qt6_22::onOpenFile()
{
    if (!maybeSave()) return;

    QString fileName = QFileDialog::getOpenFileName(this, "打开数据文件", "", "Data Files (*.dat);;All Files (*)");
    if (fileName.isEmpty()) return;

    m_pPersonSet->clear();
    m_pPersonSet->ReadFromFile(fileName.toStdString().c_str());
    m_currentFileName = fileName;
    refreshTable();
    setModified(false);
}

void Qt6_22::onSaveFile()
{
    if (m_currentFileName.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this, "保存数据文件", "", "Data Files (*.dat);;All Files (*)");
        if (fileName.isEmpty()) return;
        m_currentFileName = fileName;
    }
    m_pPersonSet->WriteToFile(m_currentFileName.toStdString().c_str());
    setModified(false);
    refreshTable();
    QMessageBox::information(this, "保存", "保存成功！");
}

void Qt6_22::onCloseFile()
{
    if (!maybeSave()) return;

    QApplication::quit();
}

bool Qt6_22::maybeSave()
{
    if (!m_isModified) return true;
    auto ret = QMessageBox::warning(this, "保存更改", "文件已被修改，是否保存？",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        if (m_currentFileName.isEmpty()) {
            QString fileName = QFileDialog::getSaveFileName(this, "保存数据文件", "", "Data Files (*.dat);;All Files (*)");
            if (fileName.isEmpty()) return false;
            m_currentFileName = fileName;
        }
        m_pPersonSet->WriteToFile(m_currentFileName.toStdString().c_str());
        setModified(false);
        return true;
    } else if (ret == QMessageBox::No) {
        return true;
    }
    return false;
}

void Qt6_22::setModified(bool modified)
{
    m_isModified = modified;
}

void Qt6_22::closeEvent(QCloseEvent* event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

Qt6_22::~Qt6_22()
{}

//排序，增删改查
//排序，删，查看

