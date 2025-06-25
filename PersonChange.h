#pragma once

#include <qdialog.h>
#include <QObject>
#include <QtWidgets/QMainWindow>
#include "ui_PersonChange.h"
#include "Person.h"
#include "PersonSet.h"


class PersonChange  : public QDialog
{
	Q_OBJECT

public:
	PersonChange(Person *set, QWidget* parent = nullptr);	//ÐÞ¸Ä
	PersonChange(PersonSet *set, QWidget* parent = nullptr);	//Ìí¼Ó
	~PersonChange();
	void setPersonInfo(Person* m_p);
	void GetPersonInfo();

public slots:
	void OnUpdatePerosnInfo();
	void syncBirthdayAndGender();
	void validateFields();
	void addSetting();
	void changeSetting();

private:
	Ui::PersonChangeClass* ui;
public:
	Person* m_Person;
	PersonSet* m_pPersonSet;
};

