#include "mainwindow.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QItemSelectionModel>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFile>

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

    connect(m_btn1, &QPushButton::clicked, this, &MainWindow::isAddRow);
    connect(m_btn2, &QPushButton::clicked, this, &MainWindow::isDeleteRow);
    connect(m_btn3, &QPushButton::clicked, this, &MainWindow::isAddColumn);
    connect(m_btn4, &QPushButton::clicked, this, &MainWindow::idDeleteColunm);
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

    QAction *actOpen = m_menu1->addAction("Открыть");
    connect(actOpen, &QAction::triggered, this, &MainWindow::isOpen);
    m_menu1->addAction("Сохранить как");
    m_menu1->addSeparator();
    QAction *actQuit = m_menu1->addAction("Выход");
    connect(actQuit, &QAction::triggered, this, &MainWindow::isQuit);


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

    QAction * actAddRow = m_menu2->addAction("+ Добавить строку");
    connect(actAddRow, &QAction::triggered, this, &MainWindow::isAddRow);
    QAction * actDeleteRow = m_menu2->addAction("- Удалить строку");
    connect(actDeleteRow, &QAction::triggered, this, &MainWindow::isDeleteRow);
    m_menu2->addSeparator();
    QAction * actAddColumn= m_menu2->addAction("+ Добавить столбец");
    connect(actAddColumn, &QAction::triggered, this, &MainWindow::isAddColumn);
    QAction * actDeleteColumn = m_menu2->addAction("- Удалить столбец");
    connect(actDeleteColumn, &QAction::triggered, this, &MainWindow::idDeleteColunm);

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

    m_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setSortIndicatorShown(true);
    m_table->setSortingEnabled(true);
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
void MainWindow::isAddRow()
{
    m_tableModel->insertRow(m_tableModel->rowCount());
    m_table->scrollToBottom();
}

void MainWindow::isDeleteRow()
{
  int rowCount = m_tableModel->rowCount();

  if(rowCount == 0)
  {
    qDebug()<<"Количество строк = 0. Удаление не выполнено";
    return;
  }
  else
  {
    QModelIndexList s_rows = m_table->selectionModel()->selectedRows();
    if (s_rows.size() == 0)
    {
      qDebug()<<"Не выбрано ни одной строки. Удаление не выполнено";
      return;
    }
    else if(s_rows.size() > 1)
    {
      qDebug()<<"Выбрано несколько строк. Удаление не выполнено";
      return;

    }
    m_tableModel->removeRow(s_rows.at(0).row());
    m_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }

}

void MainWindow::isAddColumn()
{
    m_tableModel->insertColumn(m_tableModel->columnCount());
    m_table->scrollToBottom();
}

void MainWindow::idDeleteColunm()
{
    int columnCount = m_tableModel->columnCount();

    if(columnCount == 0)
    {
        qDebug()<<"Количество столбцов = 0. Удаление не выполнено";
        return;
    }
    else
    {
        QModelIndexList s_column = m_table->selectionModel()->selectedColumns();
        if (s_column.size() == 0)
        {
            qDebug()<<"Не выбран ни один столбец. Удаление не выполнено";
            return;
        }
        else if(s_column.size() > 1)
        {
            qDebug()<<"Выбрано несколько столбцов. Удаление не выполнено";
            return;

        }
        m_tableModel->removeColumn(s_column.at(0).column());
        m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

}
void MainWindow::isDoubleClecked(int section)
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
        if (!enteredText.isEmpty() && m_table && m_table->model())
        {
            m_table->model()->setHeaderData(section, Qt::Horizontal, enteredText, Qt::DisplayRole);
        }
        else
        {
            qDebug()<<"Пустой текст - изменение не выполнено";
            return;
        }
    }
}

void MainWindow::isOpen()
{
    const QString filter = "Все файлы (*.*);;TSV (*.tsv)";
    const QString filePath = QFileDialog::getOpenFileName(
      this, "Открыть TSV файл", QDir::homePath(), filter);

    if (filePath.isEmpty())
    {
        qDebug() << "Открытие отменено";
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + filePath);
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    const QString content = in.readAll();
    file.close();
   //заполнение таблицы открытым файлом
}

void MainWindow::isQuit()
{
    //Добавить вопрос о сохранении данных, если были внесены изменения
    const auto ret = QMessageBox::question(this,
      "Выход", "Закрыть TSV Editor?",
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(ret != QMessageBox::Yes)
      return;

    QCoreApplication::quit();
}
