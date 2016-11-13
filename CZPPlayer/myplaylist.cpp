#include "myplaylist.h"
#include <QtSql>
#include<QFile>
#include <QMessageBox>

MyPlayList::MyPlayList()
{
    isChange=false;
    isOpen=false;
    if(QFile::exists("MusicPlayer.sqllite")){
        QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("MusicPlayer.sqllite");
        if (!db.open()){
                QMessageBox::warning(0, QObject::tr("数据库打开错误!"),
                                     db.lastError().text());
        }else{
            isOpen=true;
            getPlayListFromDb();
            curPlayList=PlayList.at(0);
            getFilesListFromDb(curPlayList,&curFiles);

        }
        qDebug()<<"open success";

    }else{
        QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("MusicPlayer.sqllite");
        if (!db.open()){
                QMessageBox::warning(0, QObject::tr("数据库打开错误!"),
                                     db.lastError().text());

        }else{
            QSqlQuery sql;

            sql.exec(QObject::tr("drop table *"));
            sql.exec(QObject::tr("create table PlayList (playlist varchar(255) primary key not null)"));
            sql.prepare(QObject::tr("insert into PlayList values(?)"));
            sql.addBindValue(QObject::tr("默认"));
            sql.exec();

            sql.exec(QObject::tr("create table 默认 (filename varchar(255) primary key not null,filepath varchar(1024) not null)"));
            PlayList<<QObject::tr("默认");
            isOpen=true;
        }

    }
}

void MyPlayList::save(){
    if(isChange){
        bool b=saveFilesListToDb(curPlayList,&curFiles);
        qDebug()<<b;
    }
}

//添加新的播放列表
bool MyPlayList::addPlayList(const QString name){
    QSqlQuery query;
    QString create;
    create=QObject::tr("create table '%1' (filename varchar(255) primary key,filepath varchar(1024) not null)").arg(name);

    if(query.exec(create)){
        query.prepare(QObject::tr("insert into PlayList values(?)"));
        query.addBindValue(name);
        qDebug()<<"create new playlist";
        if(query.exec()){
            PlayList.append(name);
            qDebug()<<"add new playlist";
            return true;
        }else{
            query.exec(QObject::tr("drop table '%1'").arg(name));
            qDebug()<<"add new playlist failed";
            return false;
        }
    }else{
        return false;
    }
}

//向播放列表中添加文件
bool MyPlayList::addItems(const QString playListName,const QStringList *items){
    QString insert(QObject::tr("insert into '%1' values(?,?)").arg(playListName));
    QSqlQuery query;
    query.prepare(insert);
    for(int i=0;i<items->count();i++){
        QFileInfo info(items->at(i));
        query.addBindValue(info.fileName());
        query.addBindValue(items->at(i));
        query.exec();
    }
    getFilesListFromDb(playListName,&curFiles);
    return true;
}

//从所选播放列表中删除一个歌曲
bool MyPlayList::removeItem(const QString playList,int row){

    if(row>(curFiles.count()-1))
        return false;
    QSqlQuery query;
    query.exec(QObject::tr("delete from '%1' where filename='%2' and filepath='%3'")
               .arg(playList).arg(curFiles.at(row).fileName).arg(curFiles.at(row).filePath));
    curFiles.removeAt(row);
    //isChange=true;
    return true;

}

//从播放列表中删除指定范围的歌曲
bool MyPlayList::removeItems(const QString playlist,int row_begin,int row_end){

    if(row_end>(curFiles.count()-1))
        return false;
    for(int i=row_end;i>=row_begin;i--){
        curFiles.removeAt(i);
    }
    return true;
}

bool MyPlayList::setCurPlayList(QString playlist){
    if(curPlayList==playlist){
        return false;
    }

    if(PlayList.contains(playlist)){
        if(isChange){
           saveFilesListToDb(curPlayList,&curFiles);
           isChange=false;
        }
        curFiles.clear();
        getFilesListFromDb(playlist,&curFiles);
        curPlayList=playlist;
        return true;
    }
}

bool MyPlayList::saveFilesListToDb(QString playlist,MusicInfoList* files){

    if(!isOpen)
        return false;
    QSqlQuery query;
    bool b=query.exec(QObject::tr("delete from '%1' where 1=1").arg(playlist));
    qDebug()<<b<<" remove all item";
    query.prepare(QObject::tr("insert into '%1' values(?,?)").arg(playlist));
    for(int i=0;i<files->count();i++){
        query.addBindValue(files->at(i).fileName);
        query.addBindValue(files->at(i).filePath);
        query.exec();
    }
    return true;
}

bool MyPlayList::getFilesListFromDb(QString playlist,MusicInfoList *files){
    if(!isOpen)
        return false;

    QSqlQuery query;
    query.prepare(QObject::tr("select filename,filepath from '%1' ").arg(playlist));
    MusicInfo info;
    query.exec();
    while(query.next()){
        info.fileName=query.value(0).toString();
        info.filePath=query.value(1).toString();
        //qDebug()<<info.fileName<<" "<<info.filePath;
        files->append(info);
    }

    return true;
}

QStringList MyPlayList::getAllPlayList(){
    return PlayList;

}

MusicInfoList MyPlayList::getFilesList(){
    return curFiles;
}

void MyPlayList::getPlayListFromDb(){
    QSqlQuery query;
    query.exec(QObject::tr("select playlist from PlayList"));
    while(query.next()){
        PlayList<<query.value(0).toString();
    }
}

void MyPlayList::renamePlayList(QString oldName, QString newName){
    MusicInfoList tempList;
    getFilesListFromDb(oldName,&tempList);
    QSqlQuery query;
    qDebug()<<query.exec(QObject::tr("update PlayList set playlist='%1' where playlist='%2' ").arg(newName).arg(oldName));
    qDebug()<<query.exec(QObject::tr("drop table '%1'").arg(oldName));
    qDebug()<<query.exec(QObject::tr("create table '%1' (filename varchar(255) primary key,filepath varchar(1024) not null)").arg(newName));
    qDebug()<<query.prepare(QObject::tr("insert into '%1' values(?,?)").arg(newName));
    for(int i=0;i<tempList.count();i++){
        query.addBindValue(tempList.at(i).fileName);
        query.addBindValue(tempList.at(i).filePath);
        query.exec();
    }
}

void MyPlayList::removeDuplicate(){
    if(!isOpen)
        return;

    QSqlQuery query;
    query.prepare(QObject::tr("select distinct filename,filepath from '%1' ").arg(curPlayList));
    MusicInfo info;
    query.exec();
    curFiles.clear();
    while(query.next()){
        info.fileName=query.value(0).toString();
        info.filePath=query.value(1).toString();
        //qDebug()<<info.fileName<<" "<<info.filePath;
        curFiles.append(info);
    }
    isChange=true;
    save();

}


void MyPlayList::removeErrorFiles(){
    for(int i=0;i<curFiles.count();i++){
        if(!QFile::exists(curFiles.at(i).filePath)){
            removeItem(curPlayList,i);
            i--;
        }
    }
}

void MyPlayList::removeAll(){
    curFiles.clear();
    QSqlQuery query;
    query.exec(QObject::tr("delete from '%1' where 1=1").arg(curPlayList));
}

void MyPlayList::removePlayList(const QString playListName){
    QSqlQuery query;
    query.exec(QObject::tr("drop table '%1'").arg(playListName));
    query.exec(QObject::tr("delete from PlayList where playlist='%1'").arg(playListName));
    int idx=PlayList.indexOf(playListName);
    PlayList.removeAt(idx);
}
