#ifndef MYPLAYLIST_H
#define MYPLAYLIST_H

#include <QString>
#include <QStringList>
#include <QPair>


//������Ϣ�ṹ
typedef struct MUSIC_INFO{
    QString fileName;
    QString filePath;
}MusicInfo;

typedef QList<MusicInfo> MusicInfoList;

class MyPlayList
{
public:
    MyPlayList();


private:

    MusicInfoList curFiles;//��ǰ�����б��е������ļ���Ϣ
    QStringList PlayList;//���еĲ����б�����

    bool isChange;//�б��е��ļ�ʱ��ɾ��
    bool isOpen;//���ݿ�ʱ���Ѿ���

    QString curPlayList;


public:


    bool addPlayList(const QString name);//����µĲ����б�
    bool addItems(const QString playListName,const QStringList *items);//�򲥷��б�������ļ�
    void removePlayList(const QString playListName);
    bool removeItem(const QString playList,int row);//����ѡ�����б���ɾ��һ������
    bool removeItems(const QString playlist,int row_begin,int row_end);//�Ӳ����б���ɾ��ָ����Χ�ĸ���
    void renamePlayList(QString oldName,QString newName);
    QStringList getAllPlayList();//��ȡ���в����б�
    MusicInfoList getFilesList();//��ȡ��ǰ�����б������ļ�
    bool setCurPlayList(QString playlist);//���õ�ǰ�����б�
    void save();//������������
    void removeDuplicate();
    void removeErrorFiles();
    void removeAll();

private:

    bool saveFilesListToDb(QString playlist,MusicInfoList* files);//���浽���ݿ�
    bool getFilesListFromDb(QString playlist,MusicInfoList *files);//�����ݿ��ȡ���е��ļ���Ϣ
    void getPlayListFromDb();//�����ݿ��ȡ���еĲ����б�

};

#endif // MYPLAYLIST_H
