#ifndef GRADER_H
#define GRADER_H

#include <QVBoxLayout>
#include <QGroupBox>

#include <QLabel>
#include <QObject>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>

class Grader : public QObject
{
    Q_OBJECT
public:
    explicit Grader(unsigned int nhws, QObject *parent = nullptr);

    unsigned int total() const;

    unsigned int midterm0() const;
    void setMidterm0(unsigned int midterm0);

    unsigned int midterm1() const;
    void setMidterm1(unsigned int midterm1);

    unsigned int final() const;
    void setFinal(unsigned int final);

    void changeScore(unsigned int index, int score);
    int getScore(unsigned int index);


    bool getSchema() const;
    void setSchema(bool getSchema);

signals:
    void scoreChanged();
    void totalUpdated();

public slots:
    void compute();

private:
    //set the total and emit totalUpdated
    void set_total(unsigned int total);

    // the amount of homeworks
    unsigned int m_nhws;

    // a dynamic array of the scores
    int* m_scores;

    unsigned int m_midterm0;
    unsigned int m_midterm1;
    unsigned int m_final;

    // The total score
    unsigned int m_total;

    // true for schema A and false for B
    bool m_schema;
};

#endif // GRADER_H
