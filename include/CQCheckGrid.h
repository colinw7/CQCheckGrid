#ifndef CQCheckGrid_H
#define CQCheckGrid_H

#include <QFrame>
#include <vector>

class QGridLayout;
class QAbstractButton;
class QButtonGroup;

class CQGridCheckCell : public QFrame {
  Q_OBJECT

 public:
  CQGridCheckCell(QWidget *parent) :
   QFrame(parent) {
  }

  virtual bool isCheckable() const { return true; }

  virtual bool isAnyChecked() const = 0;
  virtual bool isAllChecked() const = 0;

  virtual void setChecked(bool checked) = 0;

  virtual int rows() const { return 1; }
  virtual int cols() const { return 1; }
};

class CQGridCheckBox : public CQGridCheckCell {
 public:
  CQGridCheckBox(QWidget *parent=nullptr, const QString &name="", bool abstract=false);

  QAbstractButton *button() const { return button_; }

  bool isAnyChecked() const override;
  bool isAllChecked() const override;

  void setChecked(bool checked) override;

 private:
  QAbstractButton *button_;
};

class CQGridCheckSpacer : public CQGridCheckCell {
 public:
  CQGridCheckSpacer(QWidget *parent=nullptr) : CQGridCheckCell(parent) { }

  bool isCheckable() const override { return false; }

  bool isAnyChecked() const override { return false; }
  bool isAllChecked() const override { return false; }

  void setChecked(bool /*checked*/) override { }
};

class CQCheckGrid : public CQGridCheckCell {
  Q_OBJECT

  Q_PROPERTY(QString title     READ title   WRITE setTitle  )
  Q_PROPERTY(int     columns   READ columns WRITE setColumns)
  Q_PROPERTY(bool    exclusive READ exclusive)

 public:
  CQCheckGrid(QWidget *parent=nullptr, int cols=5);

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

  bool isAnyChecked() const override;
  bool isAllChecked() const override;

  void setChecked(bool checked) override;

  int rows() const override;
  int cols() const override;

 public slots:
  void selectAll();
  void selectNone();

 private:
  void paintEvent(QPaintEvent *) override;

  void contextMenuEvent(QContextMenuEvent *) override;

 private:
  using Cells = std::vector<CQGridCheckCell *>;

  QString       title_;
  QGridLayout  *layout_    { nullptr };
  int           cols_      { 0 };
  bool          exclusive_ { false };
  QButtonGroup *group_     { nullptr };
  int           row_       { 0 };
  int           col_       { 0 };
  Cells         cells_;
};

#endif
