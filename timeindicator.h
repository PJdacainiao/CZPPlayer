#ifndef TIMEINDICATOR_H
#define TIMEINDICATOR_H
#include <QtGui>

class TimeIndicator: public QWidget
{
public:
    TimeIndicator(QWidget *parent = 0);

    void setTime(const QString &);
private:
    QPixmap m_pixmap;
    QList<QPixmap> m_numbers;

    void load_numbers();
protected:
    void paintEvent(QPaintEvent *);
};
#endif // TIMEINDICATOR_H
