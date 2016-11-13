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
    //����keyPressEvvent����delete������������ʱ����itemDetete�ź�
    void keyPressEvent(QKeyEvent *event);
    //˫���༭��������itemTextChanged�ź�
    void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

};

#endif // MYLISTWIDGET_H
