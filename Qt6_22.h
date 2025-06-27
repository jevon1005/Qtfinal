#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt6_22.h"
#include "PersonSet.h"
#include "UndoRedo.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>

class Qt6_22 : public QMainWindow
{
    Q_OBJECT

public:
    Qt6_22(PersonSet *set,QWidget *parent = nullptr);
    ~Qt6_22();
    void personTableSetting();
    void statusBarSetting();
    void toolBarSetting();
    void refreshTable();
    void sortPersonInfo();
    void onRightClickShowMenu(QPoint);
    void onDisplaySelectedPerson(QString m_pID);
    void onDisplaySelectedPerson();
    void onDeletePersonAction();
    void onUpdatePersonAction();
    void onUpdatePersonAction(QString m_pID);
    void onAddPersonAction();
    void findPersonInfo();
    void findSetting();
    void updateUndoRedoState();
    void onNewFile();
    void onOpenFile();
    void onCloseFile();
    bool maybeSave();
    void setModified(bool modified = true);
    void  onSaveFile();
    void closeEvent(QCloseEvent* event) override;
public:
    PersonSet* m_pPersonSet;
    UndoRedo* m_undoRedo;
    QString m_currentFileName;
    bool m_isModified = false;
private:
    Ui::Qt6_22Class ui;
    QAction* m_undoAction;
    QAction* m_redoAction;
    QMediaPlayer* m_backgroundMusic;
    QAudioOutput* m_audioOutput;
};

