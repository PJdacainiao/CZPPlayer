#include "music.h"
#include <QtGui>
#include <QDebug>
#include "MusicList.h"

Music::Music(QWidget *parent)
    : QWidget(parent)
{
    QPixmap background;
    background.load(":/image/player_skin.bmp");
    this->resize(background.width(),background.height());
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TintedBackground);
    this->setWindowTitle(tr("CZPPlayer"));
    init_controls();
    init_phonon();
    init_skin();
    playList=new MusicList();
    playList->setObjectName(tr("playList"));
    playList->show();
    connect(playList,SIGNAL(selectChange(const QString&)),this,SLOT(selectChange(const QString&)));

   // playList->exec();
    playList->move(this->frameGeometry().bottomLeft());
}

Music::~Music()
{

}

void Music::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    QPixmap backgound;
    backgound.load(":/image/player_skin.bmp");

    this->setMask(backgound.mask());
    paint.drawPixmap(0,0,backgound.width(),backgound.height(),backgound);
   // this->setMask(timeInfo.mask());
   // paint.drawPixmap(280,68,timeInfo.width(),timeInfo.height(),timeInfo);
    event->accept();
}

void Music::mousePressEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        dragPosition=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void Music::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        this->move(event->globalPos()-dragPosition);
        playList->move(this->frameGeometry().bottomLeft());
        event->accept();
    }
}

void Music::init_controls(){
    BtnClose=new QPushButton(this);
    BtnClose->setObjectName(tr("BtnClose"));
    BtnClose->setGeometry(311,5,18,18);
    BtnClose->setToolTip(tr("退出"));
    BtnClose->setStyleSheet("QPushButton:!hover{border-image: url(:/image/close_unhover.png);}"
                           "QPushButton:hover{border-image: url(:/image/close_hover.png);}"
                           "QPushButton:pressed{border-image: url(:/image/close_press.png);}"
                           "QPushButton:focus{padding:-1;}");
    BtnClose->setCursor(QCursor(Qt::PointingHandCursor));

    BtnMin=new QPushButton(this);
    BtnMin->setObjectName(tr("BtnMin"));
    BtnMin->setGeometry(291,5,18,18);
    BtnMin->setToolTip(tr("最小化"));
    BtnMin->setStyleSheet("QPushButton:!hover{border-image: url(:/image/minimize_unhover.png);}"
                           "QPushButton:hover{border-image: url(:/image/minimize_hover.png);}"
                           "QPushButton:pressed{border-image: url(:/image/minimize_press.png);}"
                           "QPushButton:focus{padding:-1;}");
    BtnMin->setCursor(QCursor(Qt::PointingHandCursor));

    BtnPlay=new QPushButton(this);
    BtnPlay->setObjectName(tr("BtnPlay"));
    BtnPlay->setGeometry(170,87,56,56);
    BtnPlay->setToolTip(tr("播放"));
    BtnPlay->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play_unhover.png);}"
                           "QPushButton:hover{border-image: url(:/image/play_hover.png);}"
                           "QPushButton:pressed{border-image: url(:/image/play_press.png);}"
                           "QPushButton:focus{padding:-1;}");
    BtnPlay->setCursor(QCursor(Qt::PointingHandCursor));

    BtnPrev=new QPushButton(this);
    BtnPrev->setObjectName(tr("BtnPrev"));
    BtnPrev->setGeometry(124,93,45,45);
    BtnPrev->setToolTip(tr("前一首"));
    BtnPrev->setStyleSheet("QPushButton:!hover{border-image: url(:/image/prev_unhover.png);}"
                           "QPushButton:hover{border-image: url(:/image/prev_hover.png);}"
                           "QPushButton:pressed{border-image: url(:/image/prev_press.png);}"
                           "QPushButton:focus{padding:-1;}");
    BtnPrev->setCursor(QCursor(Qt::PointingHandCursor));

    BtnNext=new QPushButton(this);
    BtnNext->setObjectName(tr("BtnNext"));
    BtnNext->setGeometry(227,93,45,45);
    BtnNext->setToolTip(tr("下一首"));
    BtnNext->setStyleSheet("QPushButton:!hover{border-image: url(:/image/next_unhover.png);}"
                           "QPushButton:hover{border-image: url(:/image/next_hover.png);}"
                           "QPushButton:pressed{border-image: url(:/image/next_press.png);}"
                           "QPushButton:focus{padding:-1;}");
    BtnNext->setCursor(QCursor(Qt::PointingHandCursor));


    btnBrowser=new QPushButton(this);
    btnBrowser->setObjectName(tr("btnBrowser"));
    btnBrowser->setGeometry(282,152,49,22);
    btnBrowser->setToolTip(tr("音乐窗"));
    btnBrowser->setCheckable(true);
    btnBrowser->setStyleSheet("QPushButton:!hover{border-image: url(:/image/browser_1.png);}"
                           "QPushButton:hover{border-image: url(:/image/browser_1.png);}"
                           "QPushButton:pressed{border-image: url(:/image/browser_1.png);}"
                           "QPushButton:focus{padding:-1;}");
    btnBrowser->setCursor(QCursor(Qt::PointingHandCursor));

    btnLyric=new QPushButton(this);
    btnLyric->setObjectName(tr("btnLyric"));
    btnLyric->setGeometry(240,152,39,22);
    btnLyric->setToolTip(tr("歌词"));
    btnLyric->setCheckable(true);
    btnLyric->setStyleSheet("QPushButton:!hover{border-image: url(:/image/lyric_1.png);}"
                           "QPushButton:hover{border-image: url(:/image/lyric_1.png);}"
                           "QPushButton:pressed{border-image: url(:/image/lyric_1.png);}"
                           "QPushButton:focus{padding:-1;}");
    btnLyric->setCursor(QCursor(Qt::PointingHandCursor));

    btnPlayList=new QPushButton(this);
    btnPlayList->setObjectName(tr("btnPlayList"));
    btnPlayList->setGeometry(198,152,39,22);
    btnPlayList->setToolTip(tr("播放列表"));
    btnPlayList->setCheckable(true);
    btnPlayList->setStyleSheet("QPushButton:!hover{border-image: url(:/image/playlist_1.png);}"
                           "QPushButton:hover{border-image: url(:/image/playlist_1.png);}"
                           "QPushButton:pressed{border-image: url(:/image/playlist_1.png);}"
                           "QPushButton:focus{padding:-1;}");
    btnPlayList->setCursor(QCursor(Qt::PointingHandCursor));

    timeInfo=new TimeIndicator(this);
    timeInfo->setGeometry(280,68,108,14);
    timeInfo->setTime(tr("00:00"));

    muteButton=new QPushButton(this);
    muteButton->setObjectName(tr("muteButton"));
    muteButton->setGeometry(14,156,15,15);
    muteButton->setStyleSheet("QPushButton:!hover{border-image: url(:/image/mute_1.png)}"
                              "QPushButton:hover{border-image: url(:/image/mute_2.png)}"
                              "QPushButton:pressed{border-image: url(:/image/mute_2.png)}"
                              "QPushButton:focus{padding:-1;}");
    muteButton->setToolTip(tr("关闭声音"));
    muteButton->setCursor(QCursor(Qt::PointingHandCursor));



    volumeControl=new QSlider(Qt::Horizontal,this);
    volumeControl->setObjectName(tr("volumeControl"));
    volumeControl->setGeometry(36,156,79,14);
    volumeControl->setCursor(QCursor(Qt::PointingHandCursor));
    volumeControl->setRange(0,100);

    connect(BtnMin,SIGNAL(clicked()),this,SLOT(showMinimized()));
    connect(btnLyric,SIGNAL(clicked()),this,SLOT(showLyric()));
    connect(btnBrowser,SIGNAL(clicked()),this,SLOT(showBrowser()));
    connect(btnPlayList,SIGNAL(clicked()),this,SLOT(showPlayList()));
    connect(BtnClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(BtnPlay,SIGNAL(clicked()),this,SLOT(playButtonClicked()));
    connect(muteButton,SIGNAL(clicked()),this,SLOT(muteClicked()));
    connect(BtnPrev,SIGNAL(clicked()),this,SLOT(prevButtonClicked()));
    connect(BtnNext,SIGNAL(clicked()),this,SLOT(NextButtonClicked()));
    connect(volumeControl,SIGNAL(valueChanged(int)),this,SLOT(volumeChange(int)));
}


void Music::playButtonClicked()
{
    if (mediaObject ->state() == Phonon::PlayingState)
    {
        mediaObject ->pause();
        BtnPlay->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play_unhover.png);}"
                               "QPushButton:hover{border-image: url(:/image/play_hover.png);}"
                               "QPushButton:pressed{border-image: url(:/image/play_press.png);}"
                               "QPushButton:focus{padding:-1;}");

    }
    else
    {
        mediaObject ->play();
        BtnPlay->setStyleSheet("QPushButton:!hover{border-image: url(:/image/pause_unhover.png);}"
                               "QPushButton:hover{border-image: url(:/image/pause_hover.png);}"
                               "QPushButton:pressed{border-image: url(:/image/pause_press.png);}"
                               "QPushButton:focus{padding:-1;}");
    }

}

void Music::init_phonon(){

    audioOutput=new Phonon::AudioOutput(Phonon::MusicCategory,this);
    mediaObject=new Phonon::MediaObject(this);
    metaInformation=new Phonon::MediaObject(this);
    mediaObject->setTickInterval(1000);

    seekSlider=new Phonon::SeekSlider(mediaObject,this);
    seekSlider->setGeometry(124, 62,150,28);
    seekSlider->setObjectName(tr("seekSlider"));
    qDebug()<<seekSlider->parent()->metaObject()->className();


   /* volumeSlider ->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    volumeSlider->setGeometry(10,156,101,12);

    volumeSlider ->setObjectName(tr("volumeSlider"));
    QList<QObject*> list=volumeSlider->children();
    QToolButton* mute;
    QBoxLayout* layout;
    for(int i=0;i<list.size();++i){
        if(list.at(i)->metaObject()->className()==tr("QToolButton")){
            mute=qobject_cast<QToolButton*>(list.at(i));
        }else if(list.at(i)->metaObject()->className()==tr("QBoxLayout")){
            layout=qobject_cast<QBoxLayout*>(list.at(i));
        }
    }
    layout->setSpacing(7);
    mute->setObjectName(tr("mute"));
    mute->setIconSize(QSize(15,15));
    mute->setGeometry(14,156,15,15);
    mute->setIcon(QIcon(QPixmap(tr(":/image/mute_1.png"))));*/



    connect(mediaObject,SIGNAL(tick(qint64)),this,SLOT(tick(qint64)));
    connect(mediaObject,SIGNAL(stateChanged(Phonon::State,Phonon::State)),this,SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformation,SIGNAL(stateChanged(Phonon::State,Phonon::State)),this,SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject,SIGNAL(aboutToFinish()),this,SLOT(aboutToFinish()));
    connect(mediaObject,SIGNAL(currentSourceChanged(Phonon::MediaSource)),this,SLOT(sourceChanged(Phonon::MediaSource)));

    Phonon::createPath(mediaObject,audioOutput);


    //sources.append(source);
    //mediaObject->setCurrentSource(sources[0]);
    volumeControl->setValue(audioOutput->volume()*100);

}

void Music::prevButtonClicked(){

    QString file=playList->prevMusic();
    if(!file.isEmpty()){
        Phonon::MediaSource source(file);
        mediaObject->setCurrentSource(source);
        mediaObject->play();
    }
}

void Music::NextButtonClicked(){
    QString file=playList->nextMusic();
    if(!file.isEmpty()){
        Phonon::MediaSource source(file);
        mediaObject->setCurrentSource(source);
        mediaObject->play();
    }
}

void Music::showPlayList(){
    if(btnPlayList->isChecked()){
        playList->show();

    }else{
        playList->hide();
    }

}

void Music::showLyric(){

}
void Music::showBrowser(){

}

void Music::stateChanged(Phonon::State newState,Phonon::State oldState){

    switch(newState){
        case Phonon::PlayingState:
        BtnPlay->setToolTip(tr("暂停"));
        BtnPlay->setStyleSheet("QPushButton:!hover{border-image: url(:/image/pause_unhover.png);}"
                               "QPushButton:hover{border-image: url(:/image/pause_hover.png);}"
                               "QPushButton:pressed{border-image: url(:/image/pause_press.png);}"
                               "QPushButton:focus{padding:-1;}");
            break;
        case Phonon::PausedState:
        BtnPlay->setToolTip(tr("播放"));
        BtnPlay->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play_unhover.png);}"
                               "QPushButton:hover{border-image: url(:/image/play_hover.png);}"
                               "QPushButton:pressed{border-image: url(:/image/play_press.png);}"
                               "QPushButton:focus{padding:-1;}");
            break;
        case Phonon::StoppedState:
        BtnPlay->setToolTip(tr("播放"));
        BtnPlay->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play_unhover.png);}"
                               "QPushButton:hover{border-image: url(:/image/play_hover.png);}"
                               "QPushButton:pressed{border-image: url(:/image/play_press.png);}"
                               "QPushButton:focus{padding:-1;}");
            break;
        default:
            break;

    }
}

void Music::muteClicked(){
    static bool flag=true;
    if(flag){

        muteButton->setStyleSheet("QPushButton:!hover{border-image: url(:/image/mute_2.png)}"
                                  "QPushButton:hover{border-image: url(:/image/mute_2.png)}"
                                  "QPushButton:pressed{border-image: url(:/image/mute_2.png)}"
                                  "QPushButton:focus{padding:-1;}");
        muteButton->setToolTip(tr("打开声音"));
        audioOutput->setMuted(true);
    }else{
        muteButton->setStyleSheet("QPushButton:!hover{border-image: url(:/image/mute_1.png)}"
                                  "QPushButton:hover{border-image: url(:/image/mute_2.png)}"
                                  "QPushButton:pressed{border-image: url(:/image/mute_2.png)}"
                                  "QPushButton:focus{padding:-1;}");

        muteButton->setToolTip(tr("关闭声音"));
        audioOutput->setMuted(false);
    }
    flag=!flag;
}

void Music::tick(qint64 time){
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeInfo->setTime(displayTime.toString("mm:ss"));
    //this->show_numbers(displayTime.toString("mm:ss"));
}

void Music::sourceChanged(const Phonon::MediaSource &source){

}

void Music::metaStateChanged(Phonon::State newState,Phonon::State oldState){

}

void Music::aboutToFinish(){
    QString file=playList->nextMusic();
    if(!file.isEmpty()){
        Phonon::MediaSource source(file);
        mediaObject->setCurrentSource(source);
        mediaObject->play();
    }
}

void Music::volumeChange(int newVal){
    qreal vol=newVal/100.0;
    audioOutput->setVolume(vol);
}

void Music::init_skin(){
    QFile file(tr(":/qss/MusicPlayer.qss"));
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(QObject::tr(file.readAll()));
    file.close();
    QFile seekSliderSkin(":/qss/seekSlider.qss");
    seekSliderSkin.open(QFile::ReadOnly);
    seekSlider->setStyleSheet(seekSliderSkin.readAll());
    seekSliderSkin.close();
}

void Music::selectChange(const QString& file){
    qDebug()<<file;
    Phonon::MediaSource source(file);
    mediaObject->setCurrentSource(source);
    mediaObject->play();
}

void Music::closeEvent(QCloseEvent *event){
    playList->close();
    event->accept();
}
