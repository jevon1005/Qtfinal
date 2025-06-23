#include "Qt6_22.h"
#include <QtWidgets/QApplication>
#include "personset.h"

#define INFOLIBNAME "personnel.dat"
#define BAKLIBNAME "personnel.bak"

void  LoadLibToSet(PersonSet& Set)
{
    if (Set.ReadFromFile(INFOLIBNAME))
        qDebug() << "已经发现库文件，并成功读入。";
    else
        qDebug() << "未发现库文件或库文件为空。";
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
