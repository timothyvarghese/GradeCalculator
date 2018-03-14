#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QLabel>
#include <QBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QRadioButton>

#include <QDebug>

#include <QMainWindow>

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
    void computeGrades();

private:
    Ui::MainWindow *ui;

    QVector<int> m_grades;

    QRadioButton *schemaa;
    QRadioButton *schemab;

    QLabel* m_score;

    QSpinBox *spinBox[8];
    QSlider* slider[8];

   QSlider* midslider;
};

#endif // MAINWINDOW_H
