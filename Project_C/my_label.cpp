#include "my_label.h"
#include "qwidget.h"
#include <QPainter>
#include <mainwindow.h>
#include <QMessageBox>
my_label::my_label(QWidget *parent)
    : QLabel{parent}
{
    center = QPoint(0, 0);
}

void my_label::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        this->setPixmap(QPixmap::fromImage( this->image.scaled(this->size())));
        this->center = ev->pos();
        QMessageBox::information(this,"Оповещение","Центр окружности успешно выбран");
    } else if (ev->button() == Qt::RightButton) {
        this->setPixmap(QPixmap::fromImage( this->image.scaled(this->size())));
        this->rad = ev->pos();
        QMessageBox::information(this,"Оповещение","Радиус окружности успешно выбран");
    }
}



