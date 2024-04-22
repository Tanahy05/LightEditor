#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include "functions.h"
#include <QDebug>
#include <QMessageBox>
Image image(0,0),image2;
int red=0,green=0,blue=0;


void MainWindow::hide(){
    ui->flipH->hide();
    ui->flipV->hide();
    ui->colour->hide();
    ui->colourN->hide();
    ui->colourF->hide();
    ui->bright->hide();
    ui->bright_slider->hide();
    ui->blur_slider->hide();
    ui->blur_text->hide();
    ui->rleft->hide();
    ui->rright->hide();
    ui->mright->hide();
    ui->mleft->hide();
    ui->width->hide();
    ui->widthtxt->hide();
    ui->height->hide();
    ui->heightxt->hide();
    ui->resizek->hide();
    ui->cropH->hide();
    ui->cropW->hide();
    ui->cropX->hide();
    ui->cropY->hide();
    ui->cropHtxt->hide();
    ui->cropWtxt->hide();
    ui->cropXtxt->hide();
    ui->cropYtxt->hide();
    ui->cropK->hide();
    ui->mergeF->hide();
    ui->startX->hide();
    ui->startXtxt->hide();
    ui->startY->hide();
    ui->startYtxt->hide();
    ui->mergeK->hide();
    ui->skew_2->hide();
    ui->skewK->hide();
    ui->skewText->hide();
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hide();
    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_load_clicked()
{
    file=QFileDialog::getOpenFileName(window(),
                                                "Select a File",
                                                "",  // Optional: Initial directory
                                                "All Files (*.*)"); // Optional: Filters;
    QPixmap picture(file);
    if(file!=""){
    image.loadNewImage(file.toStdString());

    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);}
    else ui->size->setText("Picture dimensions= 0 x 0");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_save_clicked()
{

    QString save_file= QFileDialog::getSaveFileName(window(),
                                                     "Select a File",
                                                     "",  // Optional: Initial directory
                                                     "Image File (*.jpg) ;; Image File (*.png) ;; Image File (*.tga) ;; Image File (*.tga)");
    if(save_file!="")
    image.saveImage(save_file.toStdString());
}


void MainWindow::on_reset_clicked()
{
    hide();
    if(file!=""){
    QPixmap picture(file);
    image.loadNewImage(file.toStdString());
        ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));}
    ui->bright_slider->setSliderPosition(10);
    ui->blur_slider->setSliderPosition(5);
    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);
}


void MainWindow::on_grayScale_clicked()
{
    hide();
    grayscale(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));


}


void MainWindow::on_BW_clicked()
{
    hide();
    bw(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));

}


void MainWindow::on_inverted_clicked()
{
    hide();
    invert(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}



void MainWindow::on_wano_clicked()
{
    hide();
    landOfWano(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));

}


void MainWindow::on_purple_clicked()
{
    hide();
    purple(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_infared_clicked()
{
    hide();
    samurai(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_tv_clicked()
{
    hide();
    TvEffect(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_skew_clicked()
{
    hide();
    ui->skew_2->show();
    ui->skewK->show();
    ui->skewText->show();
}
void MainWindow::on_skewK_sliderReleased()
{
    try{
        int theta=ui->skewK->value();
        if(theta>=360)
            theta-=360;
        if(theta>0 and theta<90)
        skew(image,theta);
        else if(theta>90 and theta<180){
            skew(image,180-theta);
            flip(image,1);
        }
        else if(theta>180 and theta<270){
            skew(image,theta-180);
            flip(image,1);
            flip(image,0);

        }
        else if(theta>270 and theta<360){
            skew(image,360-theta);
            flip(image,0);


        }
        image.saveImage("temp.jpg");
        QPixmap picture("temp.jpg");
        ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
        QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
        ui->size->setText(text);
    }
    catch(...){
        QMessageBox::critical(this,"ERROR","Out Of Bounds");
    }
    ui->skewK->setSliderPosition(0);

}
void MainWindow::on_edge_detect_clicked()
{
    hide();
    EdgeDetection(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}

//needs correction
void MainWindow::on_flip_clicked()
{
    ui->bright->hide();
    ui->bright_slider->hide();
    ui->colour->hide();
    ui->colourN->hide();
    ui->colourF->hide();
    ui->flipH->show();
    ui->flipV->show();
    ui->blur_slider->hide();
    ui->blur_text->hide();

}



void MainWindow::on_flipH_clicked()
{
    flip(image,1);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_flipV_clicked()
{
    flip(image,0);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_frame_clicked()
{
    hide();
    ui->colour->show();
    ui->colourN->show();
    ui->colourF->show();
}



void MainWindow::on_colour_clicked()
{
    QColor colours = QColorDialog::getColor(Qt::white,this,tr("Select Colour"));
    frame(image,colours.red(),colours.green(),colours.blue(),ui->colourF->isChecked());
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_DarkLight_clicked()
{
    hide();
    ui->bright->show();
    ui->bright_slider->setSliderPosition(10);
    ui->bright_slider->show();


}


void MainWindow::on_bright_slider_sliderReleased()
{
    DarkenLighten(image,ui->bright_slider->sliderPosition());
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    ui->bright_slider->setSliderPosition(10);

}


void MainWindow::on_blur_clicked()
{
    hide();
    ui->blur_slider->setSliderPosition(5);
    ui->blur_slider->show();
    ui->blur_text->show();

}



void MainWindow::on_blur_slider_sliderReleased()
{
    blur(image,ui->blur_slider->value());
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    ui->blur_slider->setSliderPosition(5);

}




void MainWindow::on_rotate_clicked()
{
    hide();
    ui->rleft->show();
    ui->rright->show();

}


void MainWindow::on_rleft_clicked()
{
    rotate_img(image,2);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);
}


void MainWindow::on_rright_clicked()
{
    rotate_img(image,1);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);
}


void MainWindow::on_mirror_clicked()
{
    hide();
    ui->mright->show();
    ui->mleft->show();
}



void MainWindow::on_mleft_clicked()
{
    mirror(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_mright_clicked()
{
    flip(image,1);
    mirror(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));

}


void MainWindow::on_oilPainting_clicked()
{
    hide();
    if(file!="")
        Oil(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));

}


void MainWindow::on_burn_clicked()
{
    hide();
    burn(image);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
}


void MainWindow::on_resize_clicked()
{
    hide();
    ui->width->show();
    ui->widthtxt->show();
    ui->height->show();
    ui->heightxt->show();
    ui->resizek->show();
}


void MainWindow::on_resizek_clicked()
{
    int width,height;
    bool isnum=true;
    try{
        width=stoi(ui->width->text().toStdString());
        height=stoi(ui->height->text().toStdString());
    }
    catch(...){isnum=false;}
    if(isnum)
    rsize(image,width,height);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);
}


void MainWindow::on_crop_clicked()
{
    hide();
    ui->cropH-> show();
    ui->cropW-> show();
    ui->cropX-> show();
    ui->cropY-> show();
    ui->cropHtxt-> show();
    ui->cropWtxt-> show();
    ui->cropXtxt-> show();
    ui->cropYtxt-> show();
    ui->cropK->show();
}


void MainWindow::on_cropK_clicked()
{
    int width,height,X,Y;
    bool isnum=true;
    try{
        width=stoi(ui->cropW->text().toStdString());
        height=stoi(ui->cropH->text().toStdString());
        X=stoi(ui->cropX->text().toStdString());
        Y=stoi(ui->cropY->text().toStdString());
    }
    catch(...){isnum=false;}
    if(isnum){
        try{
            crop(image,X,Y,width,height);
            image.saveImage("temp.jpg");
            QPixmap picture("temp.jpg");
            ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
            QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
            ui->size->setText(text);
        }
        catch(...){
            QMessageBox::critical(this,"ERROR","Out of Bounds");
        }
        ui->cropH->setText("");
        ui->cropW->setText("");
        ui->cropX->setText("");
        ui->cropY->setText("");
    }
}


void MainWindow::on_merge_clicked()
{
    hide();
    ui->mergeF->show();
    ui->startX->show();
    ui->startXtxt->show();
    ui->startY->show();
    ui->startYtxt->show();
    ui->mergeK->show();
    file2=QFileDialog::getOpenFileName(window(),
                                        "Select a File",
                                        "",  // Optional: Initial directory
                                        "All Files (*.*)"); // Optional: Filters;

}


void MainWindow::on_mergeF_clicked()
{
    if(file2!="")
        image2.loadNewImage(file2.toStdString());
    merge(image,image2);
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    QString text = QString("Picture dimensions= %1 x %2").arg(image.width).arg(image.height);
    ui->size->setText(text);
}


void MainWindow::on_mergeK_clicked()
{
    int X,Y;
    bool isnum=true;
    if(file2!=""){
        image2.loadNewImage(file2.toStdString());
    try{
        X=stoi(ui->startX->text().toStdString());
        Y=stoi(ui->startY->text().toStdString());
    }
    catch(...){
        isnum=false;}

    if(isnum){
        if(X>image.width && Y>image.height)
            QMessageBox::critical(this,"ERROR","Out Of Bounds");
        else
            merge(image,image2,X,Y);
    }
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
    ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));
    ui->startX->setText("");
    ui->startY->setText("");

    }
}

void MainWindow:: checkup(){
    if(file!=""){
    image.saveImage("temp.jpg");
    QPixmap picture("temp.jpg");
        ui->label->setPixmap(picture.scaled(ui->label->width(),ui->label->height()));}
}



