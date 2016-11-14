#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>
#include<QDir>
#include<QFileDialog>
#include<QMessageBox>
#include<QDesktopServices>
#include<QListWidget>
#include<QListWidgetItem>

namespace Ui {
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

void positionChanged(qint64);
void durationChanged(qint64);
void playTo(QListWidgetItem *);
void updateSongList(QListWidgetItem *);
//void showOrHideSongList();
void importSongs();
void playPrevious();
void playNext();
void plusSound();
void reduceSound();
void setPlaybackMode1();
void setPlaybackMode2();
void setPlaybackMode3();
void setPlaybackMode4();
void support();
void aboutUs();
void setPosition(int);
void iconActivated(QSystemTrayIcon::ActivationReason reason);
void miniBtn_clicked();
void closeBtn_clicked();

protected:

void mousePressEvent(QMouseEvent *);
void mouseMoveEvent(QMouseEvent *);
void closeEvent(QCloseEvent *);

private:

void createContextMenu();
void createSystemTrayIcon();
Ui::Widget *ui;
QPoint dragPos;
int volume;
QAction *restoreAction;
QAction *quitAction;
QAction *seperatorAction1;
QAction *seperatorAction2;
QAction *seperatorAction3;
QAction *seperatorAction4;
QAction *seperatorAction5;
QMenu *trayContextMenu;
QMediaPlayer *player;
QMediaPlaylist *playList;
QSystemTrayIcon *trayIcon;
};

#endif // WIDGET_H
