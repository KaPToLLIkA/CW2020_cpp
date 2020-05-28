#include "about.h"
#include "ui_about.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    QImage image(":/images/icon.png");
    image = image.scaled(200, 200);
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsViewImage->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    scene->addItem(item);
    ui->graphicsViewImage->show();

    setWindowTitle("О программе");

}

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    this->close();
}
