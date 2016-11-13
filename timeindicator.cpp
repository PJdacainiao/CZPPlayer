#include "timeindicator.h"

TimeIndicator::TimeIndicator(QWidget *parent):QWidget(parent)
{
    load_numbers();
    m_pixmap=QPixmap(this->size());
}

void TimeIndicator::setTime(const QString &time){
   m_pixmap.fill(Qt::transparent);
    QPainter paint(&m_pixmap);
    int idx=0;
    for(int i=0;i<time.length();i++){
        if(time.at(i)==':'){
            idx=10;
        }else{
            idx=time.at(i).toAscii() - '0';
        }
        paint.drawPixmap(i*9,0,9,m_numbers.at(idx).height(),m_numbers.at(idx));

    }
    update();
}

void TimeIndicator::load_numbers(){
    QPixmap pix(tr(":/image/number.bmp"));
    for(int i=0;i<12;i++){
        m_numbers << pix.copy(i*9,0,9,pix.height());
    }
}

void TimeIndicator::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    this->resize(m_pixmap.size());

    paint.drawPixmap(0,0,m_pixmap.width(),m_pixmap.height(),m_pixmap);
    event->accept();
}






