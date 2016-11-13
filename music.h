#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QtGui>
#include <phonon>
#include <QList>
#include "MusicList.h"
#include "timeindicator.h"


class Music : public QWidget
{
    Q_OBJECT

public:
    Music(QWidget *parent = 0);
    ~Music();

private:
    QPoint dragPosition;
    QPushButton *BtnClose;
    QPushButton *BtnMin;
    QPushButton *BtnPlay;
    QPushButton *BtnPrev;
    QPushButton *BtnNext;

    QPushButton *btnBrowser;
    QPushButton *btnPlayList;
    QPushButton *btnLyric;
 //   QLabel      *timeInfo;
    TimeIndicator *timeInfo;
    QPushButton *muteButton;
    QSlider     *volumeControl;
    MusicList   *playList;
    QList<QPixmap> m_numbers;
    //QPixmap  timeInfo;


    Phonon::SeekSlider *seekSlider;
  //  Phonon::VolumeSlider *volumeSlider;
    Phonon::AudioOutput *audioOutput;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformation;
   // QList<Phonon::MediaSource> sources;


    void init_controls();
    void init_phonon();
    void init_skin();
public:
    void closeEvent(QCloseEvent *);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void close();
private slots:
    void playButtonClicked(void);
    void prevButtonClicked(void);
    void NextButtonClicked(void);
    void showPlayList();
    void showLyric();
    void showBrowser();
    void muteClicked();
    void volumeChange(int);
    void selectChange(const QString&);

    void stateChanged(Phonon::State newState,Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState,Phonon::State oldState);
    void aboutToFinish();
};
#endif // MUSIC_H
