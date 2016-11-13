/********************************
* author: czp  positive_ping@sjtu.edu.cn
* project: 基于Qt的音乐播放器
*
***********************************/


#include "music.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    Music w;
    w.show();

    return a.exec();
}
