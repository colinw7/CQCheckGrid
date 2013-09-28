#ifndef CQCheckGrid_H
#define CQCheckGrid_H

#include <QFrame>
#include <vector>

class QGridLayout;
class QAbstractButton;
class QButtonGroup;

class CQCheckCell : public QFrame {
  Q_OBJECT

 public:
  CQCheckCell(QWidget *parent) :
   QFrame(parent) {
  }

  virtual bool isCheckable() const { return true; }

  virtual bool isAnyChecked() const = 0;
  virtual bool isAllChecked() const = 0;

  virtual void setChecked(bool checked) = 0;

  virtual int rows() const { return 1; }
  virtual int cols() const { return 1; }
};

class CQCheckBox : public CQCheckCell {
 public:
  CQCheckBox(QWidget *parent=0, const QString &name="", bool abstract=false);

  QAbstractButton *button() const { return button_; }

  bool isAnyChecked() const;
  bool isAllChecked() const;

  void setChecked(bool checked);

 private:
  QAbstractButton *button_;
};

class CQCheckSpacer : public CQCheckCell {
 public:
  CQCheckSpacer(QWidget *parent=0) : CQCheckCell(parent) { }

  bool isCheckable() const { return false; }

  bool isAnyChecked() const { return false; }
  bool isAllChecked() const { return false; }

  void setChecked(bool /*checked*/) { }
};

class CQCheckGrid : public CQCheckCell {
  Q_OBJECT

  Q_PROPERTY(QString title     READ title   WRITE setTitle  )
  Q_PROPERTY(int     columns   READ columns WRITE setColumns)
  Q_PROPERTY(bool    exclusive READ exclusive)

 public:
  CQCheckGrid(QWidget *parent=0, int cols=5);

  QAbstractButton *addCheck(const QString &name);

  void addSpacer();

  CQCheckGrid *createGroup(const QString &name);

  void addGroup(CQCheckGrid *grid);

  const QString &title() const { return title_; }
  void setTitle(const QString &title);

  int columns() const { return cols_; }
  void setColumns(int cols);

  bool exclusive() const { return exclusive_; }
  void setExclusive(bool value=true);

  bool isAnyChecked() const;
  bool isAllChecked() const;

  void setChecked(bool checked);

  int rows() const;
  int cols() const;

 public slots:
  void selectAll();
  void selectNone();

 private:
  void paintEvent(QPaintEvent *);

  void contextMenuEvent(QContextMenuEvent *);

 private:
  typedef std::vector<CQCheckCell *> Cells;

  QString       title_;
  QGridLayout  *layout_;
  int           cols_;
  bool          exclusive_;
  QButtonGroup *group_;
  int           row_;
  int           col_;
  Cells         cells_;
};

#endif
