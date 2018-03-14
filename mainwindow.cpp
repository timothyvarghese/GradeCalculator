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

// This is where the midterm 1 code starts
    QLabel* midlabel= new QLabel("Midterm 1"); // Create a label for midterm 1

    QSpinBox *midsb = new QSpinBox(this); // Create a spinbox for midterm 1
    midsb->setRange(0,100); // Set the range of the Spin Box from 0 to 100

    midslider = new QSlider(Qt::Horizontal); // Create a new Slider for midterm 2
    // This connects a signal from the midsb to a slot function on mid slider and vice versa
    QObject::connect(midsb, SIGNAL(valueChanged(int)),midslider, SLOT(setValue(int)));
    QObject::connect(midslider, SIGNAL(valueChanged(int)),midsb
                     ,SLOT(setValue(int)));
    QObject::connect(midslider, SIGNAL(valueChanged(int)),this,SLOT(computeGrades()));

    QHBoxLayout *layoutmid = new QHBoxLayout();


    // This is where midterm 2 code starts
    QLabel* midlabel2= new QLabel("Midterm 2");

    QSpinBox *midsb2 = new QSpinBox(this); // Create a new spinbox for Midterm2
    midsb2->setRange(0,100);

    QSlider *midslider2 = new QSlider(Qt::Horizontal); // Create a new slider for Midterm 2
    // This connects a signal from the midsb2 to a slot function on mid slider2 and vice versa
    QObject::connect(midsb2, SIGNAL(valueChanged(int)),midslider2, SLOT(setValue(int)));
    QObject::connect(midslider2, SIGNAL(valueChanged(int)),midsb2
                     ,SLOT(setValue(int)));
    QObject::connect(midslider2, SIGNAL(valueChanged(int)),this,SLOT(computeGrades()));

    QHBoxLayout *layoutmid2 = new QHBoxLayout(); // Create a new layout for midterm2

    // This is where the final exam code starts
        QLabel* finallabel= new QLabel("Final Exam"); // Create a label for final

        QSpinBox *finalsb = new QSpinBox(this); // Create a spinbox for final
        finalsb->setRange(0,100); // Set the range of the Spin Box from 0 to 100

        QSlider *finalslider = new QSlider(Qt::Horizontal); // Create a new Slider for final
        // This connects a signal from the midsb to a slot function on mid slider and vice versa
        QObject::connect(finalsb, SIGNAL(valueChanged(int)),finalslider, SLOT(setValue(int)));
        QObject::connect(finalslider, SIGNAL(valueChanged(int)),finalsb
                         ,SLOT(setValue(int)));
        QObject::connect(finalslider, SIGNAL(valueChanged(int)),this,SLOT(computeGrades()));

        QHBoxLayout *layoutfinal = new QHBoxLayout();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(schemaa);
    vbox->addWidget(schemab);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    setCentralWidget(window);


    for (int i=0; i<nhws; i++) // Add the homeworks sliders and spinboxes
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

    layoutmid->addWidget(midlabel); // Add Midterm label to the layout of Midterm 1
    layoutmid->addWidget(midslider); // Add Midterm slider to the layout of Midterm 1
    layoutmid->addWidget(midsb);       // Add Midterm spinbox to the layout of Midterm 2


    layoutmid2->addWidget(midlabel2); // Add midterm 2 label to the layout of midterm 2
    layoutmid2->addWidget(midslider2); // Add midterm 2 slider to the
    layoutmid2->addWidget(midsb2);

    layoutfinal->addWidget(finallabel); // Add final label to the layout of final
    layoutfinal->addWidget(finalslider); // Add final slider to the layout
    layoutfinal->addWidget(finalsb);


    mainLayout->addLayout(layoutmid);// Add Midterm1 Layout to the main layout
    mainLayout->addLayout(layoutmid2); // Add Midterm 2 Layout to the main layout
    mainLayout->addLayout(layoutfinal); // Add final to the main layout
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


