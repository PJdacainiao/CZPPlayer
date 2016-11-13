#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QSplitter>
#include <QWidget>
#include <QtGui>
#include <QScreen>
#include <QSizeGrip>
#include "myplaylist.h"
#include "mylistwidget.h"

class MusicList : public QWidget
{
    Q_OBJECT
public:
    explicit MusicList(QWidget *parent = 0);

public:
    QString nextMusic();//获取当前列表中的下一首歌曲
    QString prevMusic();//获取当前列表中的上一首歌曲


private:
    QSplitter *splitter;
    MyListWidget *PlayListWidget;//播放列表管理
    MyListWidget *PlayListFilesWidget;//播放列表
    QSizeGrip  *sizeGrip;//踊跃调节窗口大小
    QFormLayout *layout;
    QPoint dragPosition;

    QPushButton *btnFile;
    QPushButton *btnDelete;
    QPushButton *btnList;
    QPushButton *btnSort;
    QPushButton *btnFind;
    QPushButton *btnEdit;
    QPushButton *btnMode;
    QPushButton *btnClose;
    MyPlayList  *PlayList;//播放列表类对象
    int curIdx;//当前正在播放的歌曲在播放列表中的索引

    QAction     *actFile;
    QAction     *actFolder;
    QAction     *actDeleteFile;
    QAction     *actDeleteDuplicate;
    QAction     *actDeleteErrorFiles;
    QAction     *actDeleteAll;
    QAction     *actDeleteFromDisk;
    QAction     *actNewPlayList;
    QAction     *actDeletePlayList;

    QStringList *fileNameList;//播放列表中的文件名列表

    void init_Skin();
    void init_Controls();
    void init_playList();
    void updatePlayListFilesWidget();

    QStringList *findFiles(const QDir &dir,QStringList &fileExts);
signals:
    void selectChange(const QString&);


public slots:

private slots:
    void btnclose();
    void File();//文件菜单
    void Folder();
    void deleteAction();
    void listAction();

    void doPlayListFilesChange(QListWidgetItem * item);//当前播放列表中的项目改变
    void doPlayListChange(QListWidgetItem* item);//播放列表管理中的项目改变
    void doItemDelete();//键盘删除一个项目的槽
    void doItemDoubleClicked(QListWidgetItem * item);//双击事件
    void itemTextChanged();//项目文本编辑结束
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);//窗体关闭消息


};
#endif // MUSICLIST_H
