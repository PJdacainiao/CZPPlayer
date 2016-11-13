#include "mylistwidget.h"
#include <QKeyEvent>

MyListWidget::MyListWidget(QWidget *parent) :
    QListWidget(parent)
{
}
void MyListWidget::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){//如果按下delete按键就发送信号
        emit itemDelete();
    }else{
        QListWidget::keyPressEvent(event);
    }
}
void MyListWidget::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint){
    //QListWidgetItem* item=qobject_cast<QListWidgetItem*>(editor);
    emit itemTextChanged();
    QAbstractItemView::closeEditor(editor,hint);
}


