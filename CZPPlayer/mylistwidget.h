#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QEvent>


class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = 0);

signals:
    void itemDelete();
    void itemTextChanged();
public slots:
protected:
    //重载keyPressEvvent拦截delete按键按键按下时发送itemDetete信号
    void keyPressEvent(QKeyEvent *event);
    //双击编辑结束后发送itemTextChanged信号
    void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

};

#endif // MYLISTWIDGET_H
