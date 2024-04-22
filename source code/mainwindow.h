#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString file,file2;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void hide();

    void on_load_clicked();

    void on_grayScale_clicked();

    void on_save_clicked();

    void on_BW_clicked();

    void on_inverted_clicked();

    void on_reset_clicked();

    void on_wano_clicked();

    void on_purple_clicked();

    void on_infared_clicked();

    void on_tv_clicked();

    void on_skew_clicked();

    void on_edge_detect_clicked();

    void on_flip_clicked();

    void on_flipH_clicked();

    void on_flipV_clicked();

    void on_frame_clicked();

    void on_colour_clicked();

    void on_DarkLight_clicked();

    void on_bright_slider_sliderReleased();

    void on_blur_clicked();

    void on_blur_slider_sliderReleased();

    void on_rotate_clicked();

    void on_rleft_clicked();

    void on_rright_clicked();

    void on_mirror_clicked();

    void on_mleft_clicked();

    void on_mright_clicked();

    void on_oilPainting_clicked();

    void on_burn_clicked();

    void on_resize_clicked();

    void on_resizek_clicked();

    void on_crop_clicked();

    void on_cropK_clicked();

    void on_merge_clicked();

    void on_mergeF_clicked();

    void on_mergeK_clicked();

    void checkup();

    void on_skewK_sliderReleased();

private:
    Ui::MainWindow *ui;


protected:
    void changeEvent(QEvent *event) override {
        if (event->type() == QEvent::WindowStateChange){
            checkup();
            }

    }
    void resizeEvent(QResizeEvent *event) override {
        checkup();
        QMainWindow::resizeEvent(event);
    }

};


#endif // MAINWINDOW_H
