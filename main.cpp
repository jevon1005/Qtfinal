#include "Qt6_22.h"
#include <QtWidgets/QApplication>
#include "personset.h"

#define INFOLIBNAME "personnel.dat"
#define BAKLIBNAME "personnel.bak"

void  LoadLibToSet(PersonSet& Set)
{
    if (Set.ReadFromFile(INFOLIBNAME))
        qDebug() << "�Ѿ����ֿ��ļ������ɹ����롣";
    else
        qDebug() << "δ���ֿ��ļ�����ļ�Ϊ�ա�";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PersonSet set;
    LoadLibToSet(set);

    Qt6_22 window(&set);
    window.show();
    return app.exec();
}
