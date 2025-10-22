#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mytablemodel.h"
#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QTableView>


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void isAddRow();
  void isDeleteRow();
  void isAddColumn();
  void isDeleteColumn();
  void isDoubleClicked(int section);
  void isOpen();
  void isSave();
  void isQuit();

private:
  void initializeMenu();
  void initializeButtons();
  void initializeTable();
  void openFile(const QString& content);

  QPushButton *m_btnAddRow;
  QPushButton *m_btnDelRow;
  QPushButton *m_btnAddCol;
  QPushButton *m_btnDelCol;

  QMenu *m_menuFile;
  QMenu *m_menuEdit;
  QToolButton *m_btnFileMenu;
  QToolButton *m_btnEditMenu;

  QToolBar *m_toolbar;
  MyTableModel *m_tableModel;
  QTableView *m_table;
};

#endif // MAINWINDOW_H
