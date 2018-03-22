#include "grader.h"


Grader::Grader(unsigned int nhws, QObject *parent) : QObject(parent),m_nhws(nhws),
    m_scores(new int[m_nhws]()),m_midterm0(0),m_midterm1(0),m_final(0), m_schema(true)
{
    //When the score is changed compute a new total
    connect(this,&Grader::scoreChanged, this, &Grader::compute);
}

void Grader::compute()
{
    double hwgrade=0;
    int min = -1;

    for(unsigned int i = 0; i < m_nhws; i++) {
        hwgrade += m_scores[i];
        if (m_scores[i] < min) min = m_scores[i];
    }
    // drop lowest HW
    hwgrade = hwgrade - min;
    hwgrade = hwgrade/7;

    int highest ;
    if(m_midterm0 > m_midterm1)
        highest= m_midterm0 ;
    else highest = m_midterm1 ;
    double finalgrade;

    if(m_schema)
        finalgrade= 0.2 * m_midterm0 + 0.2 * m_midterm1 + 0.35 * m_final + 0.25 * hwgrade;
    else
        finalgrade= 0.3 * highest + 0.25 * hwgrade + 0.44 * m_final;

    //set the total and emit that the total was updated
    set_total(finalgrade);
}

void Grader::set_total(unsigned int total)
{
    m_total = total;
    emit totalUpdated();
}

bool Grader::getSchema() const
{
    return m_schema;
}

void Grader::setSchema(bool changeSchema)
{
    m_schema = changeSchema;
    emit scoreChanged();
}

unsigned int Grader::final() const
{
    return m_final;
}

void Grader::setFinal(unsigned int final)
{
    m_final = final;
    emit scoreChanged();
}

void Grader::changeScore(unsigned int index, int score)
{
    m_scores[index] = score;
    emit scoreChanged();
}

int Grader::getScore(unsigned int index)
{
    return m_scores[index];
}

unsigned int Grader::midterm1() const
{
    return m_midterm1;
}

void Grader::setMidterm1(unsigned int midterm1)
{
    m_midterm1 = midterm1;
    emit scoreChanged();
}

unsigned int Grader::midterm0() const
{
    return m_midterm0;
}

void Grader::setMidterm0(unsigned int midterm0)
{
    m_midterm0 = midterm0;
    emit scoreChanged();
}

unsigned int Grader::total() const
{
    return m_total;
}

