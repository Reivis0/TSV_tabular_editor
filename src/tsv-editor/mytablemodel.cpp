#include "mytablemodel.h"
#include <algorithm>

static void adjustStringListLength(QStringList &list, int newSize)
{
  while (list.size() < newSize)
  {
    list.append(QString());
  }
  while (list.size() > newSize)
  {
    list.removeLast();
  }
}

MyTableModel::MyTableModel(QObject *parent) : QAbstractTableModel(parent) {}

int MyTableModel::rowCount(const QModelIndex &) const
{
  return m_data.size();
}

int MyTableModel::columnCount(const QModelIndex &) const
{
  return m_headers.size();
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }
  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    int row = index.row();
    int col = index.column();

    if (row < m_data.size() && col < m_headers.size())
    {
      if (col < m_data[row].size())
      {
        return m_data[row][col];
      }
      else
      {
        return QString();
      }
    }
  }
  return QVariant();
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role != Qt::EditRole)
  {
    return false;
  }

  int row = index.row();
  int col = index.column();

  if (row >= 0 && row < m_data.size() && col >= 0 && col < m_headers.size())
  {
    if (col >= m_data[row].size())
    {
        adjustStringListLength(m_data[row], m_headers.size());
    }

    m_data[row][col] = value.toString();
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return Qt::NoItemFlags;
  }

  return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }
  if (orientation == Qt::Horizontal)
  {
    if (section >= 0 && section < m_headers.size())
    {
        return m_headers[section];
    }
    else
    {
      return QString("Column %1").arg(section + 1);
    }
  }
  else
  {
    return QVariant(section + 1);
  }
}

void MyTableModel::setHeaders(const QStringList &headers)
{
  beginResetModel();
  m_headers = headers;
  for (auto &row : m_data)
  {
    adjustStringListLength(row, m_headers.size());
  }
  endResetModel();
}

void MyTableModel::setDataMatrix(const QVector<QStringList> &dataMatrix)
{
  beginResetModel();
  m_data = dataMatrix;
  for (auto &row : m_data)
  {
    adjustStringListLength(row, m_headers.size());
  }
  endResetModel();
}

void MyTableModel::addRow()
{
  beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  QStringList newRow;
  newRow.reserve(m_headers.size());
  for (int i = 0; i < m_headers.size(); ++i)
  {
    newRow.append(QString());
  }
  m_data.append(newRow);
  endInsertRows();
}

void MyTableModel::removeRow(int row)
{
  if (row < 0 || row >= m_data.size())
  {
    return;
  }

  beginRemoveRows(QModelIndex(), row, row);
  m_data.removeAt(row);
  endRemoveRows();
}

void MyTableModel::addColumn(const QString &header)
{
  beginResetModel();
  m_headers.append(header);
  for (auto &row : m_data)
  {
    row.append(QString());
  }
  endResetModel();
}

void MyTableModel::removeColumn(int column)
{
  if (column < 0 || column >= m_headers.size())
  {
    return;
  }

  beginResetModel();
  m_headers.removeAt(column);
  for (auto &row : m_data)
  {
    if (column < row.size())
    {
        row.removeAt(column);
    }
  }
  endResetModel();
}

void MyTableModel::setHeader(int section, const QString &text)
{
  if (section < 0 || section >= m_headers.size())
  {
    return;
  }

  m_headers[section] = text;
  emit headerDataChanged(Qt::Horizontal, section, section);
}

void MyTableModel::sort(int column, Qt::SortOrder order)
{
  if (column < 0 || column >= m_headers.size())
  {
    return;
  }

  beginResetModel();

  std::sort(m_data.begin(), m_data.end(),
    [column, order](const QStringList &a, const QStringList &b)
    {
      QString lhs = (column < a.size()) ? a[column] : QString();
      QString rhs = (column < b.size()) ? b[column] : QString();
      if (order == Qt::AscendingOrder)
      {
        return lhs < rhs;
      }
      else
      {
        return lhs > rhs;
      }
    });

  endResetModel();
}
