#ifndef MYPLAYLIST_H
#define MYPLAYLIST_H

#include <QString>
#include <QStringList>
#include <QPair>


//歌曲信息结构
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

    MusicInfoList curFiles;//当前播放列表中的所有文件信息
    QStringList PlayList;//所有的播放列表名字

    bool isChange;//列表中的文件时候删除
    bool isOpen;//数据库时候已经打开

    QString curPlayList;


public:


    bool addPlayList(const QString name);//添加新的播放列表
    bool addItems(const QString playListName,const QStringList *items);//向播放列表中添加文件
    void removePlayList(const QString playListName);
    bool removeItem(const QString playList,int row);//从所选播放列表中删除一个歌曲
    bool removeItems(const QString playlist,int row_begin,int row_end);//从播放列表中删除指定范围的歌曲
    void renamePlayList(QString oldName,QString newName);
    QStringList getAllPlayList();//获取所有播放列表
    MusicInfoList getFilesList();//获取当前播放列表所有文件
    bool setCurPlayList(QString playlist);//设置当前播放列表
    void save();//保存所有数据
    void removeDuplicate();
    void removeErrorFiles();
    void removeAll();

private:

    bool saveFilesListToDb(QString playlist,MusicInfoList* files);//保存到数据库
    bool getFilesListFromDb(QString playlist,MusicInfoList *files);//从数据库读取所有得文件信息
    void getPlayListFromDb();//从数据库读取所有的播放列表

};

#endif // MYPLAYLIST_H
