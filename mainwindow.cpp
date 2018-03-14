#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int nhws = 8;

    QWidget *window = new QWidget; // This creates a new window
    setWindowTitle("Grade Computation"); // This sets a title of the window

    QLabel* label[8];

    QLabel* overallScore = new QLabel("Overall Score",this);
    m_score = new QLabel("0.0",this);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *layouthw[8] ;

    QGroupBox *groupBox = new QGroupBox();

    schemaa = new QRadioButton("Schema A");
    QObject::connect(schemaa,SIGNAL(clicked(bool)), this, SLOT(computeGrades()));

    schemab = new QRadioButton("Schema B");
    QObject::connect(schemab,SIGNAL(clicked(bool)), this, SLOT(computeGrades()));

    schemaa->setChecked(true);


    QLabel* midlabel= new QLabel("Midterm");

    QSpinBox *midsb = new QSpinBox(this);
    midsb->setRange(0,100);

    midslider = new QSlider(Qt::Horizontal);
    // This connects a signal from the midsb to a slot function on mid slider and vice versa
    QObject::connect(midsb, SIGNAL(valueChanged(int)),midslider, SLOT(setValue(int)));
    QObject::connect(midslider, SIGNAL(valueChanged(int)),midsb,SLOT(setValue(int)));
    QObject::connect(midslider, SIGNAL(valueChanged(int)),this,SLOT(computeGrades()));

    QHBoxLayout *layoutmid = new QHBoxLayout();


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(schemaa);
    vbox->addWidget(schemab);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    setCentralWidget(window);


    for (int i=0; i<nhws; i++)
    {
        spinBox[i] = new QSpinBox; // This creates a new SpinBox for hw[i]
        spinBox[i]->setRange(0,100); // This sets the range of spinBox 2
        slider[i] = new QSlider(Qt::Horizontal); // This creates a new Slider for hw[i];

        QString s = QString::number(i+1);
        s = "Hw " + s;
        label[i]= new QLabel(s); // This creates a new Label for hw[i]
        QObject::connect(spinBox[i], SIGNAL(valueChanged(int)),slider[i], SLOT(setValue(int)));

        // This connects a signal from the spinBox [i] to a slot function on slider [i]
        QObject::connect(slider[i], SIGNAL(valueChanged(int)),spinBox[i],SLOT(setValue(int)));
        QObject::connect(slider[i], SIGNAL(valueChanged(int)),this,SLOT(computeGrades()));


        // This connects a signal from slider [i] to a slot function on spinBox [i] ;
        layouthw[i] = new QHBoxLayout; // This creates a new layout object
        layouthw[i]->addWidget(label[i]) ; // This adds the label to the layout
        layouthw[i]->addWidget(slider[i]); // This adds the slider to the layout
        layouthw[i]->addWidget(spinBox[i]); // This adds the spinBox to the layout


        mainLayout->addLayout(layouthw[i]);
    }

    layoutmid->addWidget(midlabel);
    layoutmid->addWidget(midslider);
    layoutmid->addWidget(midsb);

    mainLayout->addLayout(layoutmid);
    mainLayout->addWidget(groupBox);

    mainLayout->addWidget(overallScore);
    mainLayout->addWidget(m_score);



    window->setLayout(mainLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::computeGrades()
{
    m_grades.clear();

    int midterm =  midslider->value();

    for(auto s : slider) {
        int v = s->value();



        m_grades.push_back(v);
    }

    double hwgrade=0;
    int min = -1;

    for(auto v : m_grades) {
     hwgrade += v;
     if (v < min) min = v;
    }
    // drop lowest HW
    hwgrade = hwgrade - min;
    hwgrade = hwgrade/7;
    double finalgrade;
    if(schemab->isChecked()) {
        finalgrade= 0.5 * midterm + 0.5 * hwgrade;
    } else {
        finalgrade= 0.6 * midterm + 0.4 * hwgrade;
    }

    // ret = ret/m_grades.length();

    m_score->setText(QString::number(finalgrade, 'f', 2));
}


