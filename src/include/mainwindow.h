#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QTableView>
#include <QStandardItemModel>
#include <QString>


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
    void idDeleteColunm();
    void isDoubleClecked(int section);
    void isOpen();
    //void isSave();
    void isQuit();

private:
    void initializeMenu();
    void initializeButtons();
    void initializeTable();

    QPushButton * m_btn1;
    QPushButton * m_btn2;
    QPushButton * m_btn3;
    QPushButton * m_btn4;

    QMenu * m_menu1;
    QMenu * m_menu2;
    QToolButton *m_dropDownBtn1;
    QToolButton *m_dropDownBtn2;

    QToolBar * m_toolbar;
    QStandardItemModel * m_tableModel;
    QTableView * m_table;

};
#endif // MAINWINDOW_H
