#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "grader.h"

#include <QDebug>

#include <QMainWindow>
#include <QComboBox>
#include <QGroupBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateTotal();
    void changeGrader();

    void midtermChanged(int score);
    void secondMidtermChanged(int score);
    void finalChanged(int score);

    void setSchema(bool isA);

private:
    Grader* current_grader();

    Ui::MainWindow *ui;
    QWidget *m_window ;

    QComboBox* m_selector;

    const int m_nhws = 8;
    const int m_classes = 10;
    Grader** m_graders;

    QVBoxLayout* m_layout;
    QVBoxLayout* m_currentLayout;

    QRadioButton *m_schemaa;
    QRadioButton *m_schemab;

    QLabel* m_total;

    QSpinBox** m_spinBox;
    QSlider** m_slider;

    QSlider* m_midslider;
    QSlider* m_midslider2;
    QSlider* m_finalslider;

};

#endif // MAINWINDOW_H
