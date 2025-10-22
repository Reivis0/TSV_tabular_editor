#include "mainwindow.h"

#include <QAction>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  setWindowTitle("TSV Editor");
  setMinimumSize(600, 400);

  initializeMenu();
  initializeButtons();

  m_toolbar = new QToolBar(this);

  QWidget *containerWidget = new QWidget();
  QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);

  QHBoxLayout *topLayout = new QHBoxLayout();
  topLayout->addWidget(m_btnFileMenu);
  topLayout->addWidget(m_btnEditMenu);
  topLayout->addStretch();

  QHBoxLayout *bottomLayout = new QHBoxLayout();
  bottomLayout->addWidget(m_btnAddRow);
  bottomLayout->addWidget(m_btnDelRow);
  bottomLayout->addWidget(m_btnAddCol);
  bottomLayout->addWidget(m_btnDelCol);

  containerLayout->addLayout(topLayout);
  containerLayout->addLayout(bottomLayout);
  m_toolbar->addWidget(containerWidget);
  m_toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  addToolBar(Qt::TopToolBarArea, m_toolbar);

  initializeTable();
  setCentralWidget(m_table);


  connect(m_btnAddRow, &QPushButton::clicked, this, &MainWindow::isAddRow);
  connect(m_btnDelRow, &QPushButton::clicked, this, &MainWindow::isDeleteRow);
  connect(m_btnAddCol, &QPushButton::clicked, this, &MainWindow::isAddColumn);
  connect(m_btnDelCol, &QPushButton::clicked, this, &MainWindow::isDeleteColumn);
  connect(m_table->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, &MainWindow::isDoubleClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::initializeMenu()
{
  m_btnFileMenu = new QToolButton(this);
  m_btnFileMenu->setText("Файл");
  m_btnFileMenu->setPopupMode(QToolButton::InstantPopup);
  m_btnFileMenu->setStyleSheet("QToolButton { border: none; background: transparent; padding: 4px 8px; color:#000000; }");

  m_menuFile = new QMenu(this);
  QAction *actOpen = m_menuFile->addAction("Открыть");
  connect(actOpen, &QAction::triggered, this, &MainWindow::isOpen);
  QAction *actSave = m_menuFile->addAction("Сохранить как");
  connect(actSave, &QAction::triggered, this, &MainWindow::isSave);
  m_menuFile->addSeparator();
  QAction *actQuit = m_menuFile->addAction("Выход");
  connect(actQuit, &QAction::triggered, this, &MainWindow::isQuit);
  m_btnFileMenu->setMenu(m_menuFile);

  m_btnEditMenu = new QToolButton(this);
  m_btnEditMenu->setText("Изменить");
  m_btnEditMenu->setPopupMode(QToolButton::InstantPopup);
  m_btnEditMenu->setStyleSheet("QToolButton { border: none; background: transparent; padding: 4px 8px; color:#000000; }");

  m_menuEdit = new QMenu(this);
  QAction *actAddRow = m_menuEdit->addAction("+ Добавить строку");
  connect(actAddRow, &QAction::triggered, this, &MainWindow::isAddRow);
  QAction *actDelRow = m_menuEdit->addAction("- Удалить строку");
  connect(actDelRow, &QAction::triggered, this, &MainWindow::isDeleteRow);
  m_menuEdit->addSeparator();
  QAction *actAddCol = m_menuEdit->addAction("+ Добавить столбец");
  connect(actAddCol, &QAction::triggered, this, &MainWindow::isAddColumn);
  QAction *actDelCol = m_menuEdit->addAction("- Удалить столбец");
  connect(actDelCol, &QAction::triggered, this, &MainWindow::isDeleteColumn);

  m_btnEditMenu->setMenu(m_menuEdit);
}

void MainWindow::initializeButtons()
{
  m_btnAddRow = new QPushButton("+ Добавить строку");
  m_btnAddRow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_btnDelRow = new QPushButton("- Удалить строку");
  m_btnDelRow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_btnAddCol = new QPushButton("+ Добавить столбец");
  m_btnAddCol->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_btnDelCol = new QPushButton("- Удалить столбец");
  m_btnDelCol->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void MainWindow::initializeTable()
{
  m_tableModel = new MyTableModel(this);
  m_table = new QTableView(this);
  m_table->setModel(m_tableModel);

  m_table->verticalHeader()->setVisible(false);
  m_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table->horizontalHeader()->setSortIndicatorShown(true);
  m_table->setSortingEnabled(true);
}

void MainWindow::isAddRow()
{
  m_tableModel->addRow();
  m_table->scrollToBottom();
}

void MainWindow::isDeleteRow()
{
  QModelIndexList selected = m_table->selectionModel()->selectedRows();
  if (selected.size() == 1)
  {
    m_tableModel->removeRow(selected.at(0).row());
  }
  else
  {
    qDebug() << "Выберите одну строку для удаления.";
  }
}

void MainWindow::isAddColumn()
{
  bool ok;
  QString header = QInputDialog::getText(this, "Добавить столбец", "Заголовок столбца:", QLineEdit::Normal, QString(), &ok);
  if (ok && !header.isEmpty())
  {
    m_tableModel->addColumn(header);
    m_table->scrollToBottom();
  }
}

void MainWindow::isDeleteColumn()
{
  QModelIndexList selected = m_table->selectionModel()->selectedColumns();
  if (selected.size() == 1)
  {
    m_tableModel->removeColumn(selected.at(0).column());
  }
  else
  {
    qDebug() << "Выберите один столбец для удаления.";
  }
}

void MainWindow::isDoubleClicked(int section)
{
  bool ok;
  QString currentHeader = m_tableModel->headerData(section, Qt::Horizontal).toString();
  QString newHeader = QInputDialog::getText(this, "Заголовок столбца", "Новый заголовок:", QLineEdit::Normal, currentHeader, &ok);
  if (ok && !newHeader.isEmpty())
  {
    m_tableModel->setHeader(section, newHeader);
}
}

void MainWindow::openFile(const QString &content)
{
  QStringList rows = content.split('\n', Qt::SkipEmptyParts);
  rows.erase(std::remove_if(rows.begin(), rows.end(),
    [](const QString &row) { return row.trimmed().isEmpty(); }),
               rows.end());

  if (rows.isEmpty())
  {
    qDebug() << "Файл пуст";
    return;
  }

  QStringList headers = rows[0].split('\t');
  for (auto &h : headers) 
  {
    h = h.trimmed();
  }

  QVector<QStringList> dataMatrix;
  for (int i = 1; i < rows.size(); ++i)
  {
    QStringList cols = rows[i].split('\t');
    while (!cols.isEmpty() && cols.last().trimmed().isEmpty())
    {
      cols.removeLast();
    }
    dataMatrix.append(cols);
  }

  m_tableModel->setHeaders(headers);
  m_tableModel->setDataMatrix(dataMatrix);
}

void MainWindow::isOpen()
{
  const QString filter = "Все файлы (*.*);;TSV (*.tsv)";
  QString filePath = QFileDialog::getOpenFileName(this, "Открыть TSV файл", QDir::homePath(), filter);

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
  QString content = in.readAll();
  file.close();

  openFile(content);
}

void MainWindow::isSave()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", QDir::homePath(), "TSV (*.tsv)");

  if (fileName.isEmpty())
  {
    return;
  }

  if (!fileName.endsWith(".tsv"))
  {
    fileName += ".tsv";
  }

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QMessageBox::warning(this, "Ошибка", "Не удалось создать файл: " + file.errorString());
    return;
  }

  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  int rowCount = m_tableModel->rowCount();
  int colCount = m_tableModel->columnCount();

  for (int col = 0; col < colCount; ++col)
  {
    QString header = m_tableModel->headerData(col, Qt::Horizontal).toString();
    header = header.replace('\t', ' ').replace('\n', ' ');
    stream << header;
    if (col != colCount - 1)
    {
        stream << '\t';
    }
  }
  stream << '\n';

  for (int row = 0; row < rowCount; ++row)
  {
    for (int col = 0; col < colCount; ++col)
    {
      QModelIndex idx = m_tableModel->index(row, col);
      QString cell = m_tableModel->data(idx).toString();
      cell = cell.replace('\t', ' ').replace('\n', ' ');
      stream << cell;
      if (col != colCount - 1)
      {
        stream << '\t';
      }
    }
        stream << '\n';
  }

  file.close();
  QMessageBox::information(this, "Сохранить как", "Файл успешно сохранен: " + fileName);
}

void MainWindow::isQuit()
{
  if (QMessageBox::question(this, "Выход", "Закрыть TSV Editor?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
  {
    QCoreApplication::quit();
  }
}
