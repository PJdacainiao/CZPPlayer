#include "MusicList.h"
//音乐列表
MusicList::MusicList(QWidget *parent) :
    QWidget(parent)
{
    QPixmap backgound;
    backgound.load(":/image/playlist_skin.bmp");
    this->resize(backgound.width(),backgound.height());
    this->setMinimumSize(backgound.size());
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);//设置无边框子窗口
    this->setAttribute(Qt::WA_TintedBackground);

    curIdx=0;
    init_Controls();
    init_Skin();
    init_playList();

}

void MusicList::closeEvent(QCloseEvent *){
    PlayList->save();//保存当前所有的改变
    qDebug()<<"close";
}

void MusicList::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    QPixmap backgound;
    QPen pen(Qt::SolidLine);
    backgound.load(":/image/playlist_skin.bmp");
    int w=backgound.width();
    int h=backgound.height();
    paint.drawPixmap(0,0,w,h,backgound);//绘制背景图
    pen.setColor(QColor(37,63,96));
    paint.setPen(pen);

    //paint.setBrush(QBrush(QColor(37,63,96)));
   // paint.drawRect(w-1,0,this->rect().width()-w,32);//绘制多余的区域
   // paint.setBrush(QBrush(QColor(17,33,53)));
    //paint.drawRect(this->rect().left(),this->rect().bottom()-30,this->rect().right(),this->rect().bottom());

    event->accept();
}

void MusicList::mousePressEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        dragPosition=event->globalPos()-frameGeometry().topLeft();//获取当前鼠标在窗体中的位置
        event->accept();
    }
}

void MusicList::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        this->move(event->globalPos()-dragPosition);//移动窗体
        //playList->move(this->frameGeometry().bottomLeft());
        event->accept();
    }
}

void MusicList::init_Skin(){
    QFile playskin(":/qss/PlayList.qss");
    playskin.open(QFile::ReadOnly);

    PlayListWidget->setAlternatingRowColors(true);
    PlayListFilesWidget->setAlternatingRowColors(true);//设置QListwidget各行显示不同的颜色
    this->setStyleSheet(playskin.readAll());
    playskin.close();
}

void MusicList::init_Controls(){


    QVBoxLayout *formLayout=new QVBoxLayout(this);

    QHBoxLayout *layout=new QHBoxLayout;
    splitter=new QSplitter(Qt::Horizontal);
    PlayListWidget=new MyListWidget(this);
    PlayListFilesWidget=new MyListWidget(this);
    //PlayListFiles->setWindowFlags(Qt::ScrollBarAlwaysOff);
    PlayListFilesWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动
    PlayListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    PlayListWidget->setEnabled(true);
    PlayListWidget->setUpdatesEnabled(true);
    PlayListFilesWidget->setUpdatesEnabled(true);
    //PlayListWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    connect(PlayListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(doPlayListChange(QListWidgetItem*)));
    connect(PlayListFilesWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doPlayListFilesChange(QListWidgetItem*)));
    connect(PlayListWidget,SIGNAL(itemDelete()),this,SLOT(doItemDelete()));
    connect(PlayListFilesWidget,SIGNAL(itemDelete()),this,SLOT(doItemDelete()));
    connect(PlayListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doItemDoubleClicked(QListWidgetItem*)));
   // connect(PlayListWidget,SIGNAL(currentTextChanged(QString)),this,SLOT(doCurrentTextChanged(QString)));
   // connect(PlayListWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(doCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(PlayListWidget,SIGNAL(itemTextChanged()),this,SLOT(itemTextChanged()));

    splitter->addWidget(PlayListWidget);
    splitter->addWidget(PlayListFilesWidget);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,5);
    splitter->setStyleSheet(tr("QSplitter::handle { background-color: rgb(37,63,96); }"));
    splitter->setHandleWidth(3);
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);

    sizeGrip = new QSizeGrip(this);
    sizeGrip->setGeometry(this->rect().right()-10,this->rect().bottom()-10,this->rect().right(),this->rect().bottom());

    QHBoxLayout *btnlayout=new QHBoxLayout;
    btnFile=new QPushButton(this);
    btnDelete=new QPushButton(this);
    btnList=new QPushButton(this);
    btnSort=new QPushButton(this);
    btnFind =new QPushButton(this);
    btnEdit=new QPushButton(this);
    btnMode=new QPushButton(this);

    btnFile->setObjectName(tr("btnFile"));
    btnDelete->setObjectName(tr("btnDelete"));
    btnList->setObjectName(tr("btnList"));
    btnSort->setObjectName(tr("btnSort"));
    btnFind->setObjectName(tr("btnFind"));
    btnEdit->setObjectName(tr("btnEdit"));
    btnMode->setObjectName(tr("btnMode"));

    btnFile->setMinimumWidth(47);
    btnFile->setMinimumHeight(18);
    btnDelete->setMinimumWidth(47);
    btnDelete->setMinimumHeight(18);
    btnList->setMinimumWidth(47);
    btnList->setMinimumHeight(18);
    btnSort->setMinimumWidth(47);
    btnSort->setMinimumHeight(18);
    btnFind->setMinimumWidth(47);
    btnFind->setMinimumHeight(18);
    btnEdit->setMinimumWidth(47);
    btnEdit->setMinimumHeight(18);
    btnMode->setMinimumWidth(47);
    btnMode->setMinimumHeight(18);

    btnClose=new QPushButton(this);
    btnClose->setObjectName(tr("btnClose"));
    btnClose->setGeometry(311,5,18,18);
    btnClose->setToolTip(tr("关闭音乐列表"));
    btnClose->setStyleSheet("QPushButton:!hover{border-image: url(:/image/close_unhover.png);}"
                           "QPushButton:hover{border-image: url(:/image/close_hover.png);}"
                           "QPushButton:pressed{border-image: url(:/image/close_press.png);}"
                           "QPushButton:focus{padding:-1;}");

    btnlayout->addWidget(btnFile);
    btnlayout->addWidget(btnDelete);
    btnlayout->addWidget(btnList);
    btnlayout->addWidget(btnSort);
    btnlayout->addWidget(btnFind);
    btnlayout->addWidget(btnEdit);
    btnlayout->addWidget(btnMode);
    formLayout->addLayout(layout);
    formLayout->addLayout(btnlayout);
    QSpacerItem *horizontalSpacer;
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    btnlayout->addItem(horizontalSpacer);
    btnlayout->setMargin(3);
    formLayout->setSpacing(0);
    formLayout->setContentsMargins(0,32,0,0);


    QMenu *menuFile=new QMenu(btnFile);
    actFile=menuFile->addAction(tr("文件..."));
    actFolder=menuFile->addAction(tr("文件夹"));
    btnFile->setMenu(menuFile);

    QMenu   *menuDelete=new QMenu(btnDelete);
    actDeleteFile=menuDelete->addAction(tr("删除选中的文件"));
    actDeleteDuplicate=menuDelete->addAction(tr("删除重复的文件"));
    actDeleteErrorFiles=menuDelete->addAction(tr("删除错误的文件"));
    menuDelete->addSeparator();
    actDeleteAll=menuDelete->addAction(tr("删除所有文件"));
    menuDelete->addSeparator();
    actDeleteFromDisk=menuDelete->addAction(tr("从磁盘中删除"));
    btnDelete->setMenu(menuDelete);


    QMenu *menuPlayList=new QMenu(btnList);
    actNewPlayList=menuPlayList->addAction(tr("新建播放列表"));
    actDeletePlayList=menuPlayList->addAction(tr("删除当前列表"));
    btnList->setMenu(menuPlayList);

    //connect(BtnMin,SIGNAL(click()),this,SLOT(btnclose());
    connect(btnClose,SIGNAL(clicked()),this,SLOT(btnclose()));
    connect(actFile,SIGNAL(triggered()),this,SLOT(File()));
    connect(actFolder,SIGNAL(triggered()),this,SLOT(Folder()));

    connect(actDeleteFile,SIGNAL(triggered()),this,SLOT(deleteAction()));
    connect(actDeleteDuplicate,SIGNAL(triggered()),this,SLOT(deleteAction()));
    connect(actDeleteErrorFiles,SIGNAL(triggered()),this,SLOT(deleteAction()));
    connect(actDeleteAll,SIGNAL(triggered()),this,SLOT(deleteAction()));
    connect(actDeleteFromDisk,SIGNAL(triggered()),this,SLOT(deleteAction()));

    connect(actNewPlayList,SIGNAL(triggered()),this,SLOT(listAction()));
    connect(actDeletePlayList,SIGNAL(triggered()),this,SLOT(listAction()));

}

//打开文件选择对话框向当前播放列表中添加文件
void MusicList::File(){
    QStringList files=QFileDialog::getOpenFileNames(this,tr("选择文件"),QDir::currentPath(),tr("*.mp3 *.wma *.m4a *.ogg *.aac *.ape"));

    PlayList->addItems(PlayListWidget->currentItem()->text(),&files);

    updatePlayListFilesWidget();//更新播放列表显示


}

void MusicList::init_playList(){


    PlayList=new MyPlayList;//初始化播放列表管理类
    PlayListWidget->addItems(PlayList->getAllPlayList());//读取所有的播放列表并显示

    PlayListWidget->setCurrentRow(0);//选中第一个播放列表
    fileNameList=new QStringList;//用于存放已编号的文件名信息

    updatePlayListFilesWidget();//刷新显示
    PlayListFilesWidget->setCurrentRow(0);//选中第一个文件

}

void MusicList::btnclose(){
    this->hide();//隐藏窗口
}

//用户双击某个文件时播放该文件
void MusicList::doPlayListFilesChange(QListWidgetItem * item){

     // curPlayList->setIdx(PlayListFiles->currentRow());
    int idx=PlayListFilesWidget->currentRow();//获取当前选择的文件行
    curIdx=idx;//更新文件索引
       emit selectChange(PlayList->getFilesList().at(idx).filePath);//发出文件媒体文件改变信号
      qDebug()<<PlayList->getFilesList().at(idx).filePath;

}

void MusicList::doPlayListChange(QListWidgetItem* item){
    PlayList->setCurPlayList(item->text());//设置当前的播放列表
    curIdx=0;//更新索引为0
    updatePlayListFilesWidget();//更新显示

}

//获得下一首歌曲
QString MusicList::nextMusic(){
   // qDebug()<<tr("next button");
    if(PlayList->getFilesList().isEmpty())
        return NULL;
    if(curIdx<PlayList->getFilesList().count()-1){//不是最后一个
        curIdx++;
        PlayListFilesWidget->setCurrentRow(curIdx);
        return PlayList->getFilesList().at(curIdx).filePath;
    }else{
        curIdx=0;//返回到第一个
        PlayListFilesWidget->setCurrentRow(curIdx);
        return PlayList->getFilesList().at(curIdx).filePath;
    }
}

QString MusicList::prevMusic(){
    //qDebug()<<tr("prev button");
    if(PlayList->getFilesList().isEmpty())
        return NULL;
    if(curIdx==0){
        curIdx=PlayList->getFilesList().count()-1;
        PlayListFilesWidget->setCurrentRow(curIdx);
        return PlayList->getFilesList().at(curIdx).filePath;
    }else{
        curIdx--;
        PlayListFilesWidget->setCurrentRow(curIdx);
        return PlayList->getFilesList().at(curIdx).filePath;
    }
}

void MusicList::doItemDelete(){
    MyListWidget *List=qobject_cast<MyListWidget*>(sender());
    if(List==PlayListFilesWidget){//判断当前是哪个控件发出的信号
        qDebug()<<"remove an item";
        int idx=PlayListFilesWidget->currentRow();//获取当前行
        if(idx==-1)
            return;
        PlayList->removeItem(PlayListWidget->currentItem()->text(),idx);//删除该文件
        updatePlayListFilesWidget();//更新显示
        if(idx>(PlayList->getFilesList().count()-1))//如果删除的事最后一个文件就播放第一个
            idx=0;
        PlayListFilesWidget->setCurrentRow(idx);
    }
}

void MusicList::updatePlayListFilesWidget(){
    int cnt=PlayList->getFilesList().count();//获取总的文件数
    fileNameList->clear();//清空
    for(int i=0;i<cnt;i++){
        fileNameList->append(tr("%1.%2").arg(i+1).arg(PlayList->getFilesList().at(i).fileName));
    }
    PlayListFilesWidget->clear();
    PlayListFilesWidget->addItems(*fileNameList);
}

void MusicList::doItemDoubleClicked(QListWidgetItem *item){
    QListWidget *list=qobject_cast<QListWidget*>(sender());
    if(list==PlayListWidget){
        item->setFlags(item->flags()| Qt::ItemIsEditable);//设置该项目可编辑
        PlayListWidget->editItem(item);//编辑该项目
    }
}

void MusicList::itemTextChanged(){
    int idx=PlayListWidget->currentRow();
    QString newText=PlayListWidget->currentItem()->text();//获取最新的文本
    QString oldText=PlayList->getAllPlayList().at(idx);//旧的文本
    if(newText==oldText)//如果一样直接返回
        return;
    if(newText.isEmpty()){//如果为空继续用之前的
        PlayListWidget->currentItem()->setText(oldText);
    }else{
        if(PlayList->getAllPlayList().contains(newText)){//如果已存在其他的就继续用之前的
            PlayListWidget->currentItem()->setText(oldText);
        }else{
            PlayList->renamePlayList(oldText,newText);//修改播放列表名字
            PlayList->setCurPlayList(newText);
            updatePlayListFilesWidget();
        }

    }
}

void MusicList::Folder(){
    QStringList exts;
    exts.append(tr("*.mp3"));
    exts.append(tr("*.wma"));
    exts.append(tr("*.ape"));
    exts.append(tr("*.m4a"));
    exts.append(tr("*.ogg"));
    QString dir=QFileDialog::getExistingDirectory(this,tr("选择项目文件夹"),QDir::currentPath());
    QStringList *files=findFiles(dir,exts);
    qDebug()<<*files;
    PlayList->addItems(PlayListWidget->currentItem()->text(),files);

    updatePlayListFilesWidget();//更新播放列表显示

}

QStringList* MusicList::findFiles(const QDir &dir,QStringList &fileExts){
    QStringList *result=new QStringList;
    QStringList *tmpList=new QStringList;
    QStringList folders=dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(int i=0;i<folders.size();i++){
        qApp->processEvents();
        QString subDir=QString(tr("%1/%2").arg(dir.absolutePath()).arg(folders[i]));

        tmpList=findFiles(subDir,fileExts);

        *result<<*tmpList;
    }

    QFileInfoList files=dir.entryInfoList(fileExts,QDir::Files|QDir::NoSymLinks);
    for(int i=0;i<files.size();i++){
        result->append(files.at(i).absoluteFilePath());
    }
    return result;
}

void MusicList::deleteAction(){
    QAction *act=qobject_cast<QAction*>(sender());
    if(act==actDeleteFile){
        int row=PlayListWidget->currentRow();
        if(row==-1)
            return ;
        PlayList->removeItem(PlayListWidget->currentItem()->text(),row-1);
        updatePlayListFilesWidget();
    }else if(act==actDeleteDuplicate){
        PlayList->removeDuplicate();
        updatePlayListFilesWidget();
    }else if(act==actDeleteErrorFiles){
        PlayList->removeErrorFiles();
        updatePlayListFilesWidget();
    }else if(act==actDeleteAll){
        PlayList->removeAll();
        updatePlayListFilesWidget();
    }else if(act==actDeleteFromDisk){
        int row=PlayListWidget->currentRow();
        if(row==-1)
            return ;
        QFile::remove(PlayList->getFilesList().at(row-1).filePath);
        PlayList->removeItem(PlayListWidget->currentItem()->text(),row-1);
        updatePlayListFilesWidget();

    }

}

void MusicList::listAction(){
    QAction* act=qobject_cast<QAction*>(sender());
    if(act==actNewPlayList){
        int i=PlayList->getAllPlayList().count();
        PlayList->addPlayList(tr("新列表%1").arg(i));
        QListWidgetItem *item=new QListWidgetItem(PlayListWidget);
        item->setText(tr("新列表%1").arg(i));
        PlayListWidget->addItem(item);
        PlayListWidget->setCurrentItem(item);
        item->setFlags(item->flags()| Qt::ItemIsEditable);//设置该项目可编辑
        PlayListWidget->editItem(item);//编辑该项目
        PlayList->setCurPlayList(PlayListWidget->currentItem()->text());

    }else if(act==actDeletePlayList){
        if(PlayList->getAllPlayList().count()==1)
            return;
        int idx=PlayListWidget->currentRow();
        PlayList->removePlayList(PlayListWidget->currentItem()->text());
        PlayListWidget->clear();
        PlayListWidget->addItems(PlayList->getAllPlayList());
        PlayListWidget->setCurrentRow(idx-1);

        PlayList->setCurPlayList(PlayListWidget->currentItem()->text());
        updatePlayListFilesWidget();

    }
}






























































































