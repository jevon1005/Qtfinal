#include "PersonChange.h"
#include <qlineedit>
#include <qmessagebox>
#include <QRegularExpressionValidator>

PersonChange::PersonChange(Person* set, QWidget* parent)
    : QDialog(parent),ui(new Ui::PersonChangeClass)
{
    m_Person = set;
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    // 应用深色主题
    this->setStyleSheet(R"(
        QDialog, QWidget {
            background-color: #232629;
            color: #d3dae3;
            font-family: 'Microsoft YaHei', '微软雅黑', Arial, sans-serif;
            font-size: 15px;
        }
        QLabel {
            color: #d3dae3;
            font-weight: bold;
        }
        QLineEdit, QPlainTextEdit, QTextEdit, QDateEdit, QComboBox {
            background-color: #232629;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 4px;
            selection-background-color: #3d8ec9;
            selection-color: #fff;
            padding: 4px;
        }
        QLineEdit:focus, QPlainTextEdit:focus, QTextEdit:focus, QDateEdit:focus, QComboBox:focus {
            border: 2px solid #3d8ec9;
        }
        QPushButton {
            background-color: #31363b;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3d8ec9;
            color: #fff;
        }
        QPushButton:pressed {
            background-color: #2d5a8b;
        }
    )");

    changeSetting();
}

PersonChange::PersonChange(PersonSet* set, QWidget* parent)
    : QDialog(), ui(new Ui::PersonChangeClass)
{
    m_Person = new Person();
    m_pPersonSet = set;
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    // 应用深色主题
    this->setStyleSheet(R"(
        QDialog, QWidget {
            background-color: #232629;
            color: #d3dae3;
            font-family: 'Microsoft YaHei', '微软雅黑', Arial, sans-serif;
            font-size: 15px;
        }
        QLabel {
            color: #d3dae3;
            font-weight: bold;
        }
        QLineEdit, QPlainTextEdit, QTextEdit, QDateEdit, QComboBox {
            background-color: #232629;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 4px;
            selection-background-color: #3d8ec9;
            selection-color: #fff;
            padding: 4px;
        }
        QLineEdit:focus, QPlainTextEdit:focus, QTextEdit:focus, QDateEdit:focus, QComboBox:focus {
            border: 2px solid #3d8ec9;
        }
        QPushButton {
            background-color: #31363b;
            color: #d3dae3;
            border: 1px solid #444;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3d8ec9;
            color: #fff;
        }
        QPushButton:pressed {
            background-color: #2d5a8b;
        }
    )");

    addSetting();
}

void PersonChange::setPersonInfo(Person* m_p) {
    m_Person = m_p;
    ui->ID->setText(QString::fromLocal8Bit(m_p->GetId().c_str()));
    ui->name->setText(QString::fromLocal8Bit(m_p->GetName().c_str()));
    ui->sex->setCurrentText(QString::fromLocal8Bit(m_p->GetSex().c_str()));
    ui->birthday->setDate(QDate(m_p->GetBirthday().GetYear(), m_p->GetBirthday().GetMonth(), m_p->GetBirthday().GetDay()));
    ui->address->setText(QString::fromLocal8Bit(m_p->GetAddress().c_str()));
    ui->phoneNo->setText(QString::fromLocal8Bit(m_p->GetPhoneNo().c_str()));
    ui->employeeNo->setText(QString::fromLocal8Bit(m_p->GetEmployeeNo().c_str()));
    ui->department->setText(QString::fromLocal8Bit(m_p->GetDepartment().c_str()));
    ui->post->setText(QString::fromLocal8Bit(m_p->GetPost().c_str()));
    ui->salary->setText(QString::number(m_p->GetSalary(),'f',2));
}

void PersonChange::GetPersonInfo() {
    if (!ui) return;

    // 构造生日
    Date birthday(
        ui->birthday->date().year(),
        ui->birthday->date().month(),
        ui->birthday->date().day()
    );

    m_Person->SetId(ui->ID->text().toStdString());
    m_Person->SetName(ui->name->text().toLocal8Bit().toStdString());
    m_Person->SetSex(ui->sex->currentText().toLocal8Bit().toStdString());
    m_Person->SetPhoneNo(ui->phoneNo->text().toStdString());
    m_Person->SetAddress(ui->address->text().toLocal8Bit().toStdString());
    m_Person->SetBirthday(birthday);
    m_Person->SetEmployeeNo(ui->employeeNo->text().toStdString());
    m_Person->SetDepartment(ui->department->text().toLocal8Bit().toStdString());
    m_Person->SetPost(ui->post->text().toLocal8Bit().toStdString());
    m_Person->SetSalary(ui->salary->text().toDouble());
}

void PersonChange::OnUpdatePerosnInfo() {
    GetPersonInfo();
    accept();
}

void PersonChange::syncBirthdayAndGender() {
    QString id = ui->ID->text();
    int year = id.mid(6, 4).toInt();
    int month = id.mid(10, 2).toInt();
    int day = id.mid(12, 2).toInt();

    int sexbit = id.mid(16, 1).toInt();

    ui->birthday->setDate(QDate(year, month, day));

    if (sexbit % 2)  //男
    {
        ui->sex->setCurrentIndex(0);
    }
    else
    {
        ui->sex->setCurrentIndex(1);
    }

}

void PersonChange::validateFields() //检查是否全部填写完成
{
    if (ui->name->text().isEmpty() || ui->ID->text().isEmpty() || ui->phoneNo->text().isEmpty() ||
        ui->address->text().isEmpty() || ui->birthday->text().isEmpty() || ui->employeeNo->text().isEmpty() ||
        ui->department->text().isEmpty() || ui->post->text().isEmpty() || ui->salary->text().isEmpty())
    {
        QMessageBox::warning(this, "提示", "人员信息填写不完整");
        return;
    }
    OnUpdatePerosnInfo();
}

void PersonChange::addSetting() {
        // 当ID编辑框内容变化且长度为18时，自动同步生日和性别
        connect(ui->ID, &QLineEdit::textEdited, this, [=](const QString &text) {
            if (text.length() == 18) {
                syncBirthdayAndGender();
            }
        });

        // 当点击OK按钮时，校验所有字段
        connect(ui->okButton, &QPushButton::clicked, this, [=]() {
            validateFields();
            m_pPersonSet->push_front(*m_Person);
        });
    }

void PersonChange::changeSetting() {
    ui->okButton->setText("更新");
    setPersonInfo(m_Person);
    ui->ID->setEnabled(false);
    ui->sex->setEnabled(false);
    ui->birthday->setEnabled(false);
    connect(ui->okButton, &QPushButton::clicked, this, [=]() {
        validateFields(); // 只在校验通过时才 accept()
    });
}

PersonChange::~PersonChange()
{
    delete ui;
}



//522121200410051650
