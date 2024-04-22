#include "mainwindow.h"
#include <QApplication>
//File: CS112_A3_Part2B_S3,4_20230316_20230431_20230275

//Github Repo: https://github.com/Tanahy05/LightEditor

// Demo video link: https://drive.google.com/file/d/1ZMitVK43cLXNkwAUaOy6zno6MJVyge3B/view?usp=sharing

// PDF lik: https://drive.google.com/file/d/1kTWCDTXDikfx8Cc1lBdlqGd0J0d62wUx/view?usp=sharing

//Authors:

//Mohamed Ahmed Mohamed Mohamed Eltanahy 20230316
//Momen Desouky Mahmoud 20230431
//Amer Wael Mousa 20230275
//Section: 3/4

//Amr Wael made filters: 1,4,7,10,15,17,20
//Mohamed Eltanahy made filters: 2,5,8,11,14,18
//Momen Hamam made filters: 3,6,9,12,13,16,19
//numbers by PDF order
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
