#include "mainwindow.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  this->setWindowTitle("TSV Editor");
  this->setMinimumHeight(400);
  this->setMinimumWidth(600);

  initializeMenu();
  initializeButtons();

   m_toolbar = new QToolBar(this);

  QWidget * containerWidget = new QWidget();
  QVBoxLayout * containerLayout = new QVBoxLayout(containerWidget);

  QHBoxLayout *topLayout = new QHBoxLayout();
  topLayout->addWidget(m_dropDownBtn1);
  topLayout->addWidget(m_dropDownBtn2);
  topLayout->addStretch();

  QHBoxLayout *bottomLayout = new QHBoxLayout();
  bottomLayout->addWidget(m_btn1);
  bottomLayout->addWidget(m_btn2);
  bottomLayout->addWidget(m_btn3);
  bottomLayout->addWidget(m_btn4);

  containerLayout->addLayout(topLayout);
  containerLayout->addLayout(bottomLayout);
  m_toolbar->addWidget(containerWidget);

  m_toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  this->addToolBar(Qt::TopToolBarArea, m_toolbar);

  initializeTable();
  this->setCentralWidget(m_table);


  connect(m_btn1, &QPushButton::clicked, this, &MainWindow::isBtn1Clicked);
  connect(m_btn2, &QPushButton::clicked, this, &MainWindow::isBtn2Clicked);
  connect(m_btn3, &QPushButton::clicked, this, &MainWindow::isBtn3Clicked);
  connect(m_btn4, &QPushButton::clicked, this, &MainWindow::isBtn4Clicked);
  connect(m_table->horizontalHeader(), &QHeaderView::sectionDoubleClicked,
          this, &MainWindow::isDoubleClecked);

}

MainWindow::~MainWindow() {}

void MainWindow::initializeMenu()
{
  m_dropDownBtn1 = new QToolButton(this);
  m_dropDownBtn1->setText("Файл");
  m_dropDownBtn1->setPopupMode(QToolButton::InstantPopup);
  m_dropDownBtn1->setStyleSheet("QToolButton { "
                                "border: none; "
                                "background: transparent; "
                                "padding: 4px 8px; "
                                "color: #000000; "
                                "}");
  m_menu1 = new QMenu(this);

  m_menu1->addAction("Открыть");
  m_menu1->addAction("Сохранить как");
  m_menu1->addSeparator();
  m_menu1->addAction("Выход");


  m_dropDownBtn2 = new QToolButton(this);
  m_dropDownBtn2->setText("Изменить");
  m_dropDownBtn2->setPopupMode(QToolButton::InstantPopup);
  m_dropDownBtn2->setStyleSheet("QToolButton { "
                                "border: none; "
                                "background: transparent; "
                                "padding: 4px 8px; "
                                "color: #000000; "
                                "}");
  m_menu2 = new QMenu(this);

  m_menu2->addAction("+ Добавить строку");
  m_menu2->addAction("- Удалить строку");
  m_menu2->addSeparator();
  m_menu2->addAction("+ Добавить столбец");
  m_menu2->addAction("- Удалить столбец");

  m_dropDownBtn1->setMenu(m_menu1);
  m_dropDownBtn2->setMenu(m_menu2);
}

void MainWindow::initializeButtons()
{
  m_btn1 = new QPushButton("+ Добавить строку");
  m_btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_btn2 = new QPushButton("- Удалить строку");
  m_btn2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_btn3 = new QPushButton("+ Добавить столбец");
  m_btn3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_btn4 = new QPushButton("- Удалить столбец");
  m_btn4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void MainWindow::initializeTable()
{
    m_tableModel = new QStandardItemModel(10,10,this);
    m_table = new QTableView(this);
    m_table->setModel(m_tableModel);
    m_table->verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //реализация

}


//Слоты

void MainWindow::isBtn1Clicked()
{
}

void MainWindow::isBtn2Clicked()
{
}

void MainWindow::isBtn3Clicked()
{
}

void MainWindow::isBtn4Clicked()
{

}
QString MainWindow::isDoubleClecked()
{
  QInputDialog dialog;
  dialog.setWindowTitle("Заголовок столбца");
  dialog.setFixedSize(250,300);
  dialog.setLabelText("Текст заголовка");
  dialog.setTextValue("Заголовок");
  QString enteredText;
  if (dialog.exec() == QDialog::Accepted)
  {
    enteredText = dialog.textValue();
  }
  return enteredText;
}
