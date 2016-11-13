#include "MusicList.h"
//�����б�
MusicList::MusicList(QWidget *parent) :
    QWidget(parent)
{
    QPixmap backgound;
    backgound.load(":/image/playlist_skin.bmp");
    this->resize(backgound.width(),backgound.height());
    this->setMinimumSize(backgound.size());
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);//�����ޱ߿��Ӵ���
    this->setAttribute(Qt::WA_TintedBackground);

    curIdx=0;
    init_Controls();
    init_Skin();
    init_playList();

}

void MusicList::closeEvent(QCloseEvent *){
    PlayList->save();//���浱ǰ���еĸı�
    qDebug()<<"close";
}

void MusicList::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    QPixmap backgound;
    QPen pen(Qt::SolidLine);
    backgound.load(":/image/playlist_skin.bmp");
    int w=backgound.width();
    int h=backgound.height();
    paint.drawPixmap(0,0,w,h,backgound);//���Ʊ���ͼ
    pen.setColor(QColor(37,63,96));
    paint.setPen(pen);

    //paint.setBrush(QBrush(QColor(37,63,96)));
   // paint.drawRect(w-1,0,this->rect().width()-w,32);//���ƶ��������
   // paint.setBrush(QBrush(QColor(17,33,53)));
    //paint.drawRect(this->rect().left(),this->rect().bottom()-30,this->rect().right(),this->rect().bottom());

    event->accept();
}

void MusicList::mousePressEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        dragPosition=event->globalPos()-frameGeometry().topLeft();//��ȡ��ǰ����ڴ����е�λ��
        event->accept();
    }
}

void MusicList::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        this->move(event->globalPos()-dragPosition);//�ƶ�����
        //playList->move(this->frameGeometry().bottomLeft());
        event->accept();
    }
}

void MusicList::init_Skin(){
    QFile playskin(":/qss/PlayList.qss");
    playskin.open(QFile::ReadOnly);

    PlayListWidget->setAlternatingRowColors(true);
    PlayListFilesWidget->setAlternatingRowColors(true);//����QListwidget������ʾ��ͬ����ɫ
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
    PlayListFilesWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//�ر�ˮƽ����
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
    btnClose->setToolTip(tr("�ر������б�"));
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
    actFile=menuFile->addAction(tr("�ļ�..."));
    actFolder=menuFile->addAction(tr("�ļ���"));
    btnFile->setMenu(menuFile);

    QMenu   *menuDelete=new QMenu(btnDelete);
    actDeleteFile=menuDelete->addAction(tr("ɾ��ѡ�е��ļ�"));
    actDeleteDuplicate=menuDelete->addAction(tr("ɾ���ظ����ļ�"));
    actDeleteErrorFiles=menuDelete->addAction(tr("ɾ��������ļ�"));
    menuDelete->addSeparator();
    actDeleteAll=menuDelete->addAction(tr("ɾ�������ļ�"));
    menuDelete->addSeparator();
    actDeleteFromDisk=menuDelete->addAction(tr("�Ӵ�����ɾ��"));
    btnDelete->setMenu(menuDelete);


    QMenu *menuPlayList=new QMenu(btnList);
    actNewPlayList=menuPlayList->addAction(tr("�½������б�"));
    actDeletePlayList=menuPlayList->addAction(tr("ɾ����ǰ�б�"));
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

//���ļ�ѡ��Ի�����ǰ�����б�������ļ�
void MusicList::File(){
    QStringList files=QFileDialog::getOpenFileNames(this,tr("ѡ���ļ�"),QDir::currentPath(),tr("*.mp3 *.wma *.m4a *.ogg *.aac *.ape"));

    PlayList->addItems(PlayListWidget->currentItem()->text(),&files);

    updatePlayListFilesWidget();//���²����б���ʾ


}

void MusicList::init_playList(){


    PlayList=new MyPlayList;//��ʼ�������б������
    PlayListWidget->addItems(PlayList->getAllPlayList());//��ȡ���еĲ����б���ʾ

    PlayListWidget->setCurrentRow(0);//ѡ�е�һ�������б�
    fileNameList=new QStringList;//���ڴ���ѱ�ŵ��ļ�����Ϣ

    updatePlayListFilesWidget();//ˢ����ʾ
    PlayListFilesWidget->setCurrentRow(0);//ѡ�е�һ���ļ�

}

void MusicList::btnclose(){
    this->hide();//���ش���
}

//�û�˫��ĳ���ļ�ʱ���Ÿ��ļ�
void MusicList::doPlayListFilesChange(QListWidgetItem * item){

     // curPlayList->setIdx(PlayListFiles->currentRow());
    int idx=PlayListFilesWidget->currentRow();//��ȡ��ǰѡ����ļ���
    curIdx=idx;//�����ļ�����
       emit selectChange(PlayList->getFilesList().at(idx).filePath);//�����ļ�ý���ļ��ı��ź�
      qDebug()<<PlayList->getFilesList().at(idx).filePath;

}

void MusicList::doPlayListChange(QListWidgetItem* item){
    PlayList->setCurPlayList(item->text());//���õ�ǰ�Ĳ����б�
    curIdx=0;//��������Ϊ0
    updatePlayListFilesWidget();//������ʾ

}

//�����һ�׸���
QString MusicList::nextMusic(){
   // qDebug()<<tr("next button");
    if(PlayList->getFilesList().isEmpty())
        return NULL;
    if(curIdx<PlayList->getFilesList().count()-1){//�������һ��
        curIdx++;
        PlayListFilesWidget->setCurrentRow(curIdx);
        return PlayList->getFilesList().at(curIdx).filePath;
    }else{
        curIdx=0;//���ص���һ��
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
    if(List==PlayListFilesWidget){//�жϵ�ǰ���ĸ��ؼ��������ź�
        qDebug()<<"remove an item";
        int idx=PlayListFilesWidget->currentRow();//��ȡ��ǰ��
        if(idx==-1)
            return;
        PlayList->removeItem(PlayListWidget->currentItem()->text(),idx);//ɾ�����ļ�
        updatePlayListFilesWidget();//������ʾ
        if(idx>(PlayList->getFilesList().count()-1))//���ɾ���������һ���ļ��Ͳ��ŵ�һ��
            idx=0;
        PlayListFilesWidget->setCurrentRow(idx);
    }
}

void MusicList::updatePlayListFilesWidget(){
    int cnt=PlayList->getFilesList().count();//��ȡ�ܵ��ļ���
    fileNameList->clear();//���
    for(int i=0;i<cnt;i++){
        fileNameList->append(tr("%1.%2").arg(i+1).arg(PlayList->getFilesList().at(i).fileName));
    }
    PlayListFilesWidget->clear();
    PlayListFilesWidget->addItems(*fileNameList);
}

void MusicList::doItemDoubleClicked(QListWidgetItem *item){
    QListWidget *list=qobject_cast<QListWidget*>(sender());
    if(list==PlayListWidget){
        item->setFlags(item->flags()| Qt::ItemIsEditable);//���ø���Ŀ�ɱ༭
        PlayListWidget->editItem(item);//�༭����Ŀ
    }
}

void MusicList::itemTextChanged(){
    int idx=PlayListWidget->currentRow();
    QString newText=PlayListWidget->currentItem()->text();//��ȡ���µ��ı�
    QString oldText=PlayList->getAllPlayList().at(idx);//�ɵ��ı�
    if(newText==oldText)//���һ��ֱ�ӷ���
        return;
    if(newText.isEmpty()){//���Ϊ�ռ�����֮ǰ��
        PlayListWidget->currentItem()->setText(oldText);
    }else{
        if(PlayList->getAllPlayList().contains(newText)){//����Ѵ��������ľͼ�����֮ǰ��
            PlayListWidget->currentItem()->setText(oldText);
        }else{
            PlayList->renamePlayList(oldText,newText);//�޸Ĳ����б�����
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
    QString dir=QFileDialog::getExistingDirectory(this,tr("ѡ����Ŀ�ļ���"),QDir::currentPath());
    QStringList *files=findFiles(dir,exts);
    qDebug()<<*files;
    PlayList->addItems(PlayListWidget->currentItem()->text(),files);

    updatePlayListFilesWidget();//���²����б���ʾ

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
        PlayList->addPlayList(tr("���б�%1").arg(i));
        QListWidgetItem *item=new QListWidgetItem(PlayListWidget);
        item->setText(tr("���б�%1").arg(i));
        PlayListWidget->addItem(item);
        PlayListWidget->setCurrentItem(item);
        item->setFlags(item->flags()| Qt::ItemIsEditable);//���ø���Ŀ�ɱ༭
        PlayListWidget->editItem(item);//�༭����Ŀ
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






























































































