#ifndef SCREENBASE_H
#define SCREENBASE_H

#include <QWidget>

class ScreenBase : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenBase(QWidget *parent = nullptr) : QWidget(parent) {}

    void setPageIndex(int pageIndex) { this->pageIndex = pageIndex; }
    int getPageIndex() const { return pageIndex; }

private:
    int pageIndex = -1;
};

#endif
