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
    QString nextMusic();//��ȡ��ǰ�б��е���һ�׸���
    QString prevMusic();//��ȡ��ǰ�б��е���һ�׸���


private:
    QSplitter *splitter;
    MyListWidget *PlayListWidget;//�����б����
    MyListWidget *PlayListFilesWidget;//�����б�
    QSizeGrip  *sizeGrip;//ӻԾ���ڴ��ڴ�С
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
    MyPlayList  *PlayList;//�����б������
    int curIdx;//��ǰ���ڲ��ŵĸ����ڲ����б��е�����

    QAction     *actFile;
    QAction     *actFolder;
    QAction     *actDeleteFile;
    QAction     *actDeleteDuplicate;
    QAction     *actDeleteErrorFiles;
    QAction     *actDeleteAll;
    QAction     *actDeleteFromDisk;
    QAction     *actNewPlayList;
    QAction     *actDeletePlayList;

    QStringList *fileNameList;//�����б��е��ļ����б�

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
    void File();//�ļ��˵�
    void Folder();
    void deleteAction();
    void listAction();

    void doPlayListFilesChange(QListWidgetItem * item);//��ǰ�����б��е���Ŀ�ı�
    void doPlayListChange(QListWidgetItem* item);//�����б�����е���Ŀ�ı�
    void doItemDelete();//����ɾ��һ����Ŀ�Ĳ�
    void doItemDoubleClicked(QListWidgetItem * item);//˫���¼�
    void itemTextChanged();//��Ŀ�ı��༭����
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);//����ر���Ϣ


};
#endif // MUSICLIST_H
