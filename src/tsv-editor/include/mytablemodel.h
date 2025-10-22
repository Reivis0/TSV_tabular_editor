#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>


class MyTableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  explicit MyTableModel(QObject *parent = nullptr);
  ~MyTableModel() {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  void setHeaders(const QStringList &headers);
  void setDataMatrix(const QVector<QStringList> &dataMatrix);

  void addRow();
  void removeRow(int row);
  void addColumn(const QString &header);
  void removeColumn(int column);
  void setHeader(int section, const QString &text);

  void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

private:
    QStringList m_headers;
    QVector<QStringList> m_data;
};

#endif // MYTABLEMODEL_H
