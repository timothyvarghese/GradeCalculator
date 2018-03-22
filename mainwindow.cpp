#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Grade Computation");

    m_window = new QWidget;
    m_layout = new QVBoxLayout(m_window);

    m_selector = new QComboBox(this);

    // prepare a grader change when a new class is selected
    connect(m_selector,SIGNAL(currentIndexChanged(int)),this,SLOT(changeGrader()));

    m_layout->addWidget(m_selector);

    QLabel* label[10];
    QLabel* overallScore = new QLabel("Overall Score");
    m_total = new QLabel("0.0");

    QHBoxLayout *layouthw[10] ;
    QGroupBox *groupBox = new QGroupBox();

    m_schemaa = new QRadioButton("Schema A");
    connect(m_schemaa,&QRadioButton::clicked, this,[&](){
        setSchema(true);
    });

    m_schemab = new QRadioButton("Schema B");
    connect(m_schemab,&QRadioButton::clicked, this,[&](){
        setSchema(false);
    });

    m_schemaa->setChecked(true);

    // This is where the midterm 1 code starts
    QLabel* midlabel= new QLabel("Midterm 1"); // Create a label for midterm 1

    QSpinBox *midsb = new QSpinBox; // Create a spinbox for midterm 1
    midsb->setRange(0,100); // Set the range of the Spin Box from 0 to 100

    m_midslider = new QSlider(Qt::Horizontal); // Create a new Slider for midterm 2
    // This connects a signal from the midsb to a slot function on mid slider and vice versa
    connect(midsb, SIGNAL(valueChanged(int)),m_midslider, SLOT(setValue(int)));
    connect(m_midslider, SIGNAL(valueChanged(int)),midsb,SLOT(setValue(int)));
    connect(m_midslider, SIGNAL(valueChanged(int)),this,SLOT(midtermChanged(int)));

    QHBoxLayout *layoutmid = new QHBoxLayout();

    // This is where midterm 2 code starts
    QLabel* midlabel2= new QLabel("Midterm 2");

    QSpinBox *midsb2 = new QSpinBox; // Create a new spinbox for Midterm2
    midsb2->setRange(0,100);

    m_midslider2 = new QSlider(Qt::Horizontal); // Create a new slider for Midterm 2
    // This connects a signal from the midsb2 to a slot function on mid slider2 and vice versa
    connect(midsb2, SIGNAL(valueChanged(int)),m_midslider2, SLOT(setValue(int)));
    connect(m_midslider2, SIGNAL(valueChanged(int)),midsb2
                     ,SLOT(setValue(int)));

    connect(m_midslider2, SIGNAL(valueChanged(int)),this,SLOT(secondMidtermChanged(int)));

    QHBoxLayout *layoutmid2 = new QHBoxLayout(); // Create a new layout for midterm2

    // This is where the final exam code starts
    QLabel* finallabel= new QLabel("Final Exam"); // Create a label for final

    QSpinBox *finalsb = new QSpinBox; // Create a spinbox for final
    finalsb->setRange(0,100); // Set the range of the Spin Box from 0 to 100

    m_finalslider = new QSlider(Qt::Horizontal); // Create a new Slider for final
    // This connects a signal from the midsb to a slot function on mid slider and vice versa
    connect(finalsb, SIGNAL(valueChanged(int)),m_finalslider, SLOT(setValue(int)));
    connect(m_finalslider, SIGNAL(valueChanged(int)),finalsb
                     ,SLOT(setValue(int)));
    connect(m_finalslider, SIGNAL(valueChanged(int)),this,SLOT(finalChanged(int)));

    QHBoxLayout *layoutfinal = new QHBoxLayout();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_schemaa);
    vbox->addWidget(m_schemab);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    m_spinBox = new QSpinBox*[m_nhws];
    m_slider = new QSlider*[m_nhws];

    for (int i = 0; i < m_nhws; i++) // Add the homeworks sliders and spinboxes
    {
        m_spinBox[i] = new QSpinBox; // This creates a new SpinBox for hw[i]
        m_spinBox[i]->setRange(0,100); // This sets the range of spinBox 2
        m_slider[i] = new QSlider(Qt::Horizontal); // This creates a new m_slider for hw[i];

        QString s = QString::number(i+1);
        s = "Hw " + s;
        label[i]= new QLabel(s); // This creates a new Label for hw[i]
        connect( m_spinBox[i], SIGNAL(valueChanged(int)),m_slider[i], SLOT(setValue(int)));

        // This connects a signal from the spinBox [i] to a slot function on m_slider [i]
        connect(m_slider[i], SIGNAL(valueChanged(int)), m_spinBox[i],SLOT(setValue(int)));

        connect(m_slider[i], &QSlider::valueChanged,this,[=](){
            current_grader()->changeScore(i,m_slider[i]->value());
        });

        // This connects a signal from m_slider [i] to a slot function on spinBox [i] ;
        layouthw[i] = new QHBoxLayout; // This creates a new layout object
        layouthw[i]->addWidget(label[i]) ; // This adds the label to the layout
        layouthw[i]->addWidget(m_slider[i]); // This adds the m_slider to the layout
        layouthw[i]->addWidget( m_spinBox[i]); // This adds the  m_spinBox to the layout


        m_layout->addLayout(layouthw[i]);
    }

    layoutmid->addWidget(midlabel); // Add Midterm label to the layout of Midterm 1
    layoutmid->addWidget(m_midslider); // Add Midterm slider to the layout of Midterm 1
    layoutmid->addWidget(midsb);       // Add Midterm  m_spinBox to the layout of Midterm 2


    layoutmid2->addWidget(midlabel2); // Add midterm 2 label to the layout of midterm 2
    layoutmid2->addWidget(m_midslider2); // Add midterm 2 slider to the
    layoutmid2->addWidget(midsb2);

    layoutfinal->addWidget(finallabel); // Add final label to the layout of final
    layoutfinal->addWidget(m_finalslider); // Add final slider to the layout
    layoutfinal->addWidget(finalsb);


    m_layout->addLayout(layoutmid);// Add Midterm1 Layout to the main layout
    m_layout->addLayout(layoutmid2); // Add Midterm 2 Layout to the main layout
    m_layout->addLayout(layoutfinal); // Add final to the main layout
    m_layout->addWidget(groupBox);

    m_layout->addWidget(overallScore);
    m_layout->addWidget(m_total);

    // create a grader for each class
    m_graders = new Grader*[m_classes];

    // initialize the graders to nhws
    for (int i = 0; i < m_classes; i++) {
        m_graders[i] = new Grader(m_nhws,this);
        m_selector->addItem("Class #" + QString::number(i + 1));

        connect(m_graders[i],&Grader::totalUpdated,this,&MainWindow::updateTotal);
    }

    m_window->setLayout(m_layout);
    setCentralWidget(m_window);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTotal()
{
    m_total->setText(QString::number(current_grader()->total(), 'f', 2));
}

void MainWindow::changeGrader()
{
    for (int i = 0; i < m_nhws; i++) {
        m_slider[i]->setValue(current_grader()->getScore(i));
    }
    m_midslider->setValue(current_grader()->midterm0());
    m_midslider2->setValue(current_grader()->midterm1());
    m_finalslider->setValue(current_grader()->final());


    bool schema = current_grader()->getSchema();
    m_schemaa->setChecked(schema);
    m_schemab->setChecked(!schema);
}

void MainWindow::midtermChanged(int score)
{
    current_grader()->setMidterm0(score);
}

void MainWindow::secondMidtermChanged(int score)
{
    current_grader()->setMidterm1(score);
}

void MainWindow::finalChanged(int score)
{
    current_grader()->setFinal(score);
}

void MainWindow::setSchema(bool isA)
{
    current_grader()->setSchema(isA);
}

Grader *MainWindow::current_grader()
{
 return m_graders[m_selector->currentIndex()];
}
