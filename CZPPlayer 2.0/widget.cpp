#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(QIcon(":/images/icon.jpg"));
    setWindowTitle("Player");
    //设置背景图片
    QPixmap pixmap(":/images/background5.jpg");//当前文件夹下面的图片
    QPalette palette = this->palette();
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    setPalette(palette);
    //设置音量
    volume=80;
    //初始化
    createContextMenu();
    createSystemTrayIcon();

    playList=new QMediaPlaylist;
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    player=new QMediaPlayer;
    player->setPlaylist(playList);
    player->setVolume(volume);
    //信号与槽连接
    connect(ui->miniButton,SIGNAL(clicked()),this, SLOT(miniBtn_clicked()));
    connect(ui->closeButton,SIGNAL(clicked()),this, SLOT(closeBtn_clicked()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(playTo(QListWidgetItem *)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(updateSongList(QListWidgetItem *)));
    connect(ui->action_Import, SIGNAL(triggered()), this, SLOT(importSongs()));
    connect(ui->action_Last, SIGNAL(triggered()), this, SLOT(playPrevious()));
    connect(ui->action_Play, SIGNAL(triggered()), this, SLOT(playOrPause()));
    connect(ui->action_Stop, SIGNAL(triggered()), player, SLOT(stop()));
    connect(ui->action_Next, SIGNAL(triggered()), this, SLOT(playNext()));
    connect(ui->action_SoundPlus, SIGNAL(triggered()), this, SLOT(plusSound()));
    connect(ui->action_SoundReduce, SIGNAL(triggered()), this, SLOT(reduceSound()));
    connect(ui->action_Mode1, SIGNAL(triggered()), this, SLOT(setPlaybackMode1()));
    connect(ui->action_Mode2, SIGNAL(triggered()), this, SLOT(setPlaybackMode2()));
    connect(ui->action_Mode3, SIGNAL(triggered()), this, SLOT(setPlaybackMode3()));
    connect(ui->action_Mode4, SIGNAL(triggered()), this, SLOT(setPlaybackMode4()));
    connect(ui->action_Support, SIGNAL(triggered()), this, SLOT(support()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(aboutUs()));
    connect(ui->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->toolButton_Last, SIGNAL(clicked()), this, SLOT(playPrevious()));
    connect(ui->toolButton_Play, SIGNAL(clicked()), player, SLOT(play()));
    connect(ui->toolButton_Stop, SIGNAL(clicked()), player, SLOT(pause()));
    connect(ui->toolButton_Next, SIGNAL(clicked()), this, SLOT(playNext()));
}

Widget::~Widget()
{
    delete ui;
}

//关闭
void Widget::closeBtn_clicked()
{
    this->hide();
}

//最小化
void Widget::miniBtn_clicked()
{

    this->showMinimized();
}

//面板右键菜单栏显示
void Widget::createContextMenu()

{

    seperatorAction1=new QAction(this);
    seperatorAction1->setSeparator(true);
    seperatorAction2=new QAction(this);
    seperatorAction2->setSeparator(true);
    seperatorAction3=new QAction(this);
    seperatorAction3->setSeparator(true);
    seperatorAction4=new QAction(this);
    seperatorAction4->setSeparator(true);
    seperatorAction5=new QAction(this);
    seperatorAction5->setSeparator(true);

    addAction(ui->action_Import);
    addAction(seperatorAction1);
    addAction(ui->action_Last);
    addAction(ui->action_Play);
    addAction(ui->action_Stop);
    addAction(ui->action_Next);
    addAction(seperatorAction2);
    addAction(ui->action_Mode1);
    addAction(ui->action_Mode2);
    addAction(ui->action_Mode3);
    addAction(ui->action_Mode4);
    addAction(seperatorAction3);
    addAction(ui->action_SoundPlus);
    addAction(ui->action_SoundReduce);
    addAction(seperatorAction4);
    addAction(ui->action_Support);
    addAction(ui->action_About);
    addAction(seperatorAction5);
    addAction(ui->action_Quit);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}


//系统最小化设置
void Widget::createSystemTrayIcon()

{

    trayIcon=new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(tr(":/images/icon")));
    trayIcon->setToolTip(tr("酷音听听 - 音乐播放器"));
    restoreAction=new QAction(tr("打开主面板"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(show()));
    quitAction=new QAction(tr("退出"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayContextMenu=new QMenu(this);
    //trayContextMenu->addAction(ui->action_SongList);
    trayContextMenu->addAction(ui->action_Import);
    trayContextMenu->addSeparator();
    trayContextMenu->addAction(ui->action_Last);
    trayContextMenu->addAction(ui->action_Play);
    trayContextMenu->addAction(ui->action_Stop);
    trayContextMenu->addAction(ui->action_Next);
    trayContextMenu->addSeparator();
    trayContextMenu->addAction(ui->action_Mode1);
    trayContextMenu->addAction(ui->action_Mode2);
    trayContextMenu->addAction(ui->action_Mode3);
    trayContextMenu->addAction(ui->action_Mode4);
    trayContextMenu->addSeparator();
    trayContextMenu->addAction(ui->action_SoundPlus);
    trayContextMenu->addAction(ui->action_SoundReduce);
    trayContextMenu->addSeparator();
    trayContextMenu->addAction(ui->action_Support);
    trayContextMenu->addAction(ui->action_About);
    trayContextMenu->addSeparator();
    trayContextMenu->addAction(restoreAction);
    trayContextMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayContextMenu);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

}


void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)

{

switch(reason) {

    case QSystemTrayIcon::DoubleClick:

    case QSystemTrayIcon::Trigger:

    if(this->isVisible()==true) ;
    else
    {

    this->show();

    this->activateWindow();

    }

    break;

    default:

    break;

    }

}

//处理关闭事件
void Widget::closeEvent(QCloseEvent *event)

{

    if(trayIcon->isVisible()) {

        hide();

        trayIcon->showMessage(tr("提示"), tr("酷音听听将在后台运行"));

        event->ignore();

        } else {

        event->accept();

    }

}

//鼠标点击事件
void Widget::mousePressEvent(QMouseEvent *event)

{

    if(event->button()==Qt::LeftButton) {

    dragPos=event->globalPos()-frameGeometry().topLeft();

    event->accept();

    }

}

//鼠标移动事件
void Widget::mouseMoveEvent(QMouseEvent *event)

{

    if(event->buttons()&Qt::LeftButton) {

    move(event->globalPos()-dragPos);

    event->accept();

    }

}


void Widget::positionChanged(qint64 position)

{

    ui->horizontalSlider->setValue(position);

}


void Widget::durationChanged(qint64 duration)

{

    ui->horizontalSlider->setRange(0, duration);

}

//显示播放
void Widget::updateSongList(QListWidgetItem *index)

{

     int  i = ui->listWidget->row(index);

    ui->label->setText(tr("正在播放: %0").arg(ui->listWidget->item(i)->text()));

}


//播放
void Widget::playTo(QListWidgetItem * listwidget )

{

    int  i = ui->listWidget->row(listwidget)-1;
    playList->setCurrentIndex(i);
    player->play();

}

//导入歌单
void Widget::importSongs()

{

    QString initialName=QDir::currentPath();

    QStringList pathList=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName);

    for(int i=0; i<pathList.size(); ++i)
    {

    QString path=QDir::toNativeSeparators(pathList.at(i));

         if(!path.isEmpty())
        {

            playList->addMedia(QUrl::fromLocalFile(path));

            QString fileName=path.split("\\").last();

            int rownum=ui->listWidget->count();
            ui->listWidget->insertItem(rownum,new QListWidgetItem(fileName.split(".").front()));

        }

    }

}

//播放上一首
void Widget::playPrevious()

{

    int currentIndex=playList->currentIndex();

    if(--currentIndex<0) currentIndex=0;

    playList->setCurrentIndex(currentIndex);

    player->play();
    ui->label->setText(tr("正在播放: %0").arg(ui->listWidget->item(++currentIndex)->text()));

}

//播放下一首
void Widget::playNext()

{

    int currentIndex=playList->currentIndex();

    if(++currentIndex==playList->mediaCount()) currentIndex=0;

    playList->setCurrentIndex(currentIndex);

    player->play();

    ui->label->setText(tr("正在播放: %0").arg(ui->listWidget->item(++currentIndex)->text()));

}

//增大音量
void Widget::plusSound()

{

    volume+=20;

    if(volume>=100)
    {
    volume=100;
    ui->action_SoundPlus->setEnabled(false);
    }

    player->setVolume(volume);
    if(!ui->action_SoundReduce->isEnabled())
    ui->action_SoundReduce->setEnabled(true);
}

//减小音量
void Widget::reduceSound()

{

    volume-=20;
    if(volume<=0)
    {
    volume=0;
    ui->action_SoundReduce->setEnabled(false);
    }

    player->setVolume(volume);
    if(!ui->action_SoundPlus->isEnabled())
    ui->action_SoundPlus->setEnabled(true);
}


void Widget::setPosition(int position)

{
    player->setPosition(position);

}

//循环播放
void Widget::setPlaybackMode1()

{

    playList->setPlaybackMode(QMediaPlaylist::Loop);

}

//随机播放
void Widget::setPlaybackMode2()

{

    playList->setPlaybackMode(QMediaPlaylist::Random);

}

//单曲循环
void Widget::setPlaybackMode3()

{

    playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

}

//顺序播放
void Widget::setPlaybackMode4()

{

    playList->setPlaybackMode(QMediaPlaylist::Sequential);

}


void Widget::support()

{

    QMessageBox::about(this, tr("关于酷音听听"), \

    tr("酷音听听，感谢您的使用！"));

}

void Widget::aboutUs()

{

    const QUrl url("https://github.com/positiveczp/CZPPlayer");

    QDesktopServices::openUrl(url);

}


