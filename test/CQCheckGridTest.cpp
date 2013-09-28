#include <CQCheckGridTest.h>
#include <CQCheckGrid.h>
#include <QApplication>
#include <QVBoxLayout>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQCheckGridTest *test = new CQCheckGridTest;

  test->show();

  return app.exec();
}

CQCheckGridTest::
CQCheckGridTest(QWidget *parent) :
 QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(0); layout->setSpacing(0);

  CQCheckGrid *grid = new CQCheckGrid(this, 4);

  CQCheckGrid *g1 = grid->createGroup("Group 1");
  CQCheckGrid *g2 = grid->createGroup("Group 2");

  g2->setExclusive();

  g1->addCheck("One" ); g1->addCheck("Two"); g1->addCheck("Three" ); g1->addCheck("Four" );

  g2->addCheck("Five"); g2->addCheck("Six"); g2->addCheck("Seven" ); g2->addCheck("Eight" );

  grid->addGroup(g1);
  grid->addGroup(g2);

  grid->addCheck("Nine"); grid->addCheck("Ten"); grid->addCheck("Eleven"); grid->addCheck("Twelve");

  layout->addWidget(grid);
  layout->addStretch(1);
}
