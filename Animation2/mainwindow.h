#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

private slots:
    void on_actionAbout_triggered();

    void on_actionVolume_triggered();

    int volume() const;
    void setVolume(int);



//void on_sliderVolume_sliderMoved(int position);



private:
    Ui::MainWindow *ui;
    QMediaPlayer * player;
};

#endif // MAINWINDOW_H
