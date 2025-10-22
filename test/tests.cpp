#include <gtest/gtest.h>
#include "mytablemodel.h"


class MyTableModelTest : public ::testing::Test
{
protected:
  MyTableModel model;

  void SetUp() override
  {
    model.setHeaders({"A", "B", "C"});
  }
};

TEST_F(MyTableModelTest, AddRemoveRow)
{
  EXPECT_EQ(model.rowCount(), 0);
  model.addRow();
  EXPECT_EQ(model.rowCount(), 1);
  model.removeRow(0);
  EXPECT_EQ(model.rowCount(), 0);
}

TEST_F(MyTableModelTest, AddRemoveColumn)
{
  EXPECT_EQ(model.columnCount(), 3);
  model.addColumn("D");
  EXPECT_EQ(model.columnCount(), 4);
  model.removeColumn(3);
  EXPECT_EQ(model.columnCount(), 3);
}

TEST_F(MyTableModelTest, SetGetData)
{
  model.addRow();
  auto idx = model.index(0, 1);
  EXPECT_TRUE(model.setData(idx, QString("test")));
  EXPECT_EQ(model.data(idx).toString(), "test");
}

TEST_F(MyTableModelTest, HeaderDataCheck)
{
  EXPECT_EQ(model.headerData(0, Qt::Horizontal).toString(), "A");
  model.setHeader(1, "NewHeader");
  EXPECT_EQ(model.headerData(1, Qt::Horizontal).toString(), "NewHeader");
}

TEST_F(MyTableModelTest, SortAscendingDescending)
{
  model.setHeaders({"Col1"});
  model.addRow();
  model.addRow();
  model.addRow();
  model.setData(model.index(0,0), "b");
  model.setData(model.index(1,0), "c");
  model.setData(model.index(2,0), "a");

  model.sort(0, Qt::AscendingOrder);
  EXPECT_EQ(model.data(model.index(0,0)).toString(), "a");
  EXPECT_EQ(model.data(model.index(1,0)).toString(), "b");
  EXPECT_EQ(model.data(model.index(2,0)).toString(), "c");

  model.sort(0, Qt::DescendingOrder);
  EXPECT_EQ(model.data(model.index(0,0)).toString(), "c");
  EXPECT_EQ(model.data(model.index(1,0)).toString(), "b");
  EXPECT_EQ(model.data(model.index(2,0)).toString(), "a");
}



TEST(TSVParsingTest, ParsesSampleTSV)
{
  QString content = "H1\tH2\tH3\nv11\tv12\tv13\nv21\tv22\tv23\n";
  QStringList rows = content.split('\n', Qt::SkipEmptyParts);
  rows.erase(std::remove_if(rows.begin(), rows.end(),
    [](const QString &row) { return row.trimmed().isEmpty(); }), rows.end());
  ASSERT_FALSE(rows.isEmpty());

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

  EXPECT_EQ(headers.size(), 3);
  EXPECT_EQ(headers[0], "H1");
  ASSERT_EQ(dataMatrix.size(), 2);
  EXPECT_EQ(dataMatrix[0][1], "v12");
  EXPECT_EQ(dataMatrix[1][2], "v23");

  MyTableModel model;
  model.setHeaders(headers);
  model.setDataMatrix(dataMatrix);
  EXPECT_EQ(model.headerData(0, Qt::Horizontal).toString(), "H1");
  EXPECT_EQ(model.data(model.index(0,1)).toString(), "v12");
  EXPECT_EQ(model.data(model.index(1,2)).toString(), "v23");
}


TEST(TSVSerializationTest, CorrectTSVSerialization)
{
  MyTableModel model;
  model.setHeaders({"A", "B"});
  model.addRow();
  model.setData(model.index(0,0), "1");
  model.setData(model.index(0,1), "2");

  QString tsv;
  int rowCount = model.rowCount();
  int colCount = model.columnCount();

  for (int col = 0; col < colCount; ++col)
  {
    QString header = model.headerData(col, Qt::Horizontal).toString();
    header = header.replace('\t', ' ').replace('\n', ' ');
    tsv += header;
    if (col != colCount - 1)
    {
      tsv += '\t';
    }
  }
  tsv += '\n';

  for (int row = 0; row < rowCount; ++row)
  {
    for (int col = 0; col < colCount; ++col)
    {
      QString cell = model.data(model.index(row,col)).toString();
      cell = cell.replace('\t', ' ').replace('\n', ' ');
      tsv += cell;
      if (col != colCount - 1)
      {
        tsv += '\t';
      }
    }
      tsv += '\n';
  }

  EXPECT_EQ(tsv, "A\tB\n1\t2\n");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
