#include <CQCheckGrid.h>

#include <QGridLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPainter>
#include <QMenu>
#include <QContextMenuEvent>

CQCheckGrid::
CQCheckGrid(QWidget *parent, int cols) :
 CQGridCheckCell(parent), cols_(cols)
{
  setObjectName("grid");

  layout_ = new QGridLayout(this);
  layout_->setSpacing(2); layout_->setMargin(2);

  setContextMenuPolicy(Qt::DefaultContextMenu);

  group_ = new QButtonGroup(this);

  group_->setExclusive(false);
}

void
CQCheckGrid::
setExclusive(bool exclusive)
{
  exclusive_ = exclusive;

  group_->setExclusive(exclusive_);
}

QAbstractButton *
CQCheckGrid::
addCheck(const QString &name)
{
  auto *box = new CQGridCheckBox(this, name, exclusive());

  group_->addButton(box->button());

  if (exclusive() && cells_.empty())
    box->button()->setChecked(true);

  if (col_ > 0 && col_ + 1 > cols_) {
    col_ = 0;
    ++row_;
  }

  layout_->addWidget(box, row_, col_, 1, 1);

  ++col_;

  cells_.push_back(box);

  return box->button();
}

void
CQCheckGrid::
addSpacer()
{
  auto *spacer = new CQGridCheckSpacer(this);

  if (col_ > 0 && col_ + 1 > cols_) {
    col_ = 0;
    ++row_;
  }

  layout_->addWidget(spacer, row_, col_, 1, 1);

  ++col_;

  cells_.push_back(spacer);
}

CQCheckGrid *
CQCheckGrid::
createGroup(const QString &name)
{
  auto *grid = new CQCheckGrid(this);

  grid->setTitle(name);

  return grid;
}

void
CQCheckGrid::
addGroup(CQCheckGrid *grid)
{
  int cols = grid->cols();

  if (col_ > 0 && col_ + cols > cols_) {
    col_ = 0;
    ++row_;
  }

  layout_->addWidget(grid, row_, col_, 1, cols);

  col_ += cols;

  cells_.push_back(grid);
}

void
CQCheckGrid::
setColumns(int cols)
{
  if (cols_ == cols)
    return;

  QLayoutItem *child;

  while ((child = layout_->takeAt(0)) != 0)
    delete child;

  for (uint i = 0; i < cells_.size(); ++i) {
    int row = i / cols_;
    int col = i % cols_;

    layout_->addWidget(cells_[i], row, col);
  }
}

void
CQCheckGrid::
setTitle(const QString &title)
{
  title_ = title;

  if (title_.length()) {
    QFontMetrics fm(font());

    setContentsMargins(4, fm.height() + 4, 4, 4);
  }
  else
    setContentsMargins(0, 0, 0, 0);
}

void
CQCheckGrid::
paintEvent(QPaintEvent *)
{
  if (title_.length()) {
    QColor bg = palette().background().color();

    QPainter p(this);

    QFontMetrics fm(font());

    QRect r = rect().adjusted(2, (fm.height() + 4)/2, -2, -2);

    p.setPen(bg.darker(150));

    p.drawRect(r);

    r = fm.boundingRect(title_);

    r.adjust(8, 2 + fm.ascent(), 8, 2 + fm.ascent());

    p.fillRect(r, QBrush(bg));

    p.setPen(QColor(0,0,0));

    p.drawText(8, 2 + fm.ascent(), title_);
  }
}

void
CQCheckGrid::
contextMenuEvent(QContextMenuEvent *e)
{
  if (! exclusive()) {
    auto *menu = new QMenu;

    auto *allAction  = menu->addAction("Select All" );
    auto *noneAction = menu->addAction("Select None");

    allAction ->setEnabled(! isAllChecked());
    noneAction->setEnabled(isAnyChecked());

    connect(allAction , SIGNAL(triggered()), this, SLOT(selectAll()));
    connect(noneAction, SIGNAL(triggered()), this, SLOT(selectNone()));

    (void) menu->exec(e->globalPos());

    delete menu;
  }
}

bool
CQCheckGrid::
isAnyChecked() const
{
  for (uint i = 0; i < cells_.size(); ++i) {
    if (! cells_[i]->isCheckable()) continue;

    if (cells_[i]->isAnyChecked())
      return true;
  }

  return false;
}

bool
CQCheckGrid::
isAllChecked() const
{
  for (uint i = 0; i < cells_.size(); ++i) {
    if (! cells_[i]->isCheckable()) continue;

    if (! cells_[i]->isAllChecked())
      return false;
  }

  return true;
}

void
CQCheckGrid::
selectAll()
{
  setChecked(true);
}

void
CQCheckGrid::
selectNone()
{
  setChecked(false);
}

void
CQCheckGrid::
setChecked(bool checked)
{
  if (exclusive()) return;

  for (uint i = 0; i < cells_.size(); ++i) {
    if (! cells_[i]->isCheckable()) continue;

    cells_[i]->setChecked(checked);
  }
}

int
CQCheckGrid::
rows() const
{
  int rows = cells_.size()/columns();

  if (cells_.size() % columns())
    ++rows;

  return rows;
}

int
CQCheckGrid::
cols() const
{
  if (int(cells_.size()) < columns())
    return cells_.size();
  else
    return columns();
}

//------

CQGridCheckBox::
CQGridCheckBox(QWidget *parent, const QString &name, bool exclusive) :
 CQGridCheckCell(parent)
{
  setObjectName(name);

  auto *layout = new QHBoxLayout(this);
  layout->setSpacing(0); layout->setMargin(0);

  if (exclusive)
    button_ = new QRadioButton(this);
  else
    button_ = new QCheckBox(this);

  button_->setText(name);

  layout->addWidget(button_);
}

bool
CQGridCheckBox::
isAnyChecked() const
{
  return button_->isChecked();
}

bool
CQGridCheckBox::
isAllChecked() const
{
  return isAnyChecked();
}

void
CQGridCheckBox::
setChecked(bool checked)
{
  button_->setChecked(checked);
}
