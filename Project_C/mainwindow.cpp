#include "mainwindow.h"
#include "qpainter.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QColor>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Отрисовка круга
void MainWindow::print_circle(double radius)
{
    QImage tmp(ui->label_img->pixmap().toImage());

    QPainter painter(&tmp);
    QPen paintpen(Qt::red);
    paintpen.setWidth(5);
    painter.setPen(paintpen);
    painter.drawEllipse(ui->label_img->center, (int)radius, (int)radius);

    ui->label_img->setPixmap(QPixmap::fromImage(tmp));


}

//Выбор картинки
void MainWindow::on_btn_choose_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images(*.png *.jpg *jpeg *bmp *.gif)"));

    if(QString::compare(file_name, QString()) != 0){
        bool valid = ui->label_img->image.load(file_name);
        if(valid){
            ui->label_img->setPixmap(QPixmap::fromImage( ui->label_img->image.scaled(ui->label_img->size())));
        }
    } else {
        //Error
        QMessageBox::critical(this, "Внимание", "Произошла ошибка при загрузки изображения!");
    }
}




void MainWindow::on_pushButton_clicked()
{
    double rad;
    rad = abs(sqrt( pow((ui->label_img->center.x() - ui->label_img->rad.x()),2) +
                    pow( (ui->label_img->center.y() - ui->label_img->rad.y()),2)));

    print_circle(rad);
    int sat_min = 256;
    int sat_max = -1;
    int sat_midl = 0;
    int cnt = 0;

    int x = ui->label_img->center.x();
    int y = ui->label_img->center.y();
    int width = ui->label_img->width();
    int height = ui->label_img->height();

    QImage image(ui->label_img->pixmap().toImage());

    for (int i = std::max(x - rad, 0.0); i <= std::min(x + rad, width - 1.0); i++){
        for (int j = std::max(y - rad, 0.0); j <= std::min(y + rad, height - 1.0); j++){
            if ((i - x) * (i - x) + (j - y) * (j - y) <= rad * rad)
            {
                sat_min = std::min(sat_min, qGray(image.pixelColor(i, j).rgba()));
                sat_max = std::max(sat_max, qGray(image.pixelColor(i, j).rgba()));
                sat_midl += qGray(image.pixelColor(i, j).rgba());
                cnt++;
            }
        }
    }
    sat_midl /= cnt;

    ui->label_min->setText(QString::number(sat_min));
    ui->label_max->setText(QString::number(sat_max));
    ui->label_midl->setText(QString::number(sat_midl));
}

