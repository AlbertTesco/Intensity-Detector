#ifndef MY_LABEL_H
#define MY_LABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
class my_label : public QLabel
{
    Q_OBJECT
public:
    QPoint center; //Координаты центра лейбла
    QPoint rad;    //Координаты точки радиуса окружности
    QImage image;  //Загруженная на лейбл картинка

    explicit my_label(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *ev);
};

#endif // MY_LABEL_H
