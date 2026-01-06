#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QStackedWidget>
#include <QHash>
#include <QWidget>
#include "screenid.h"

class Controller
{
public:
    explicit Controller(QStackedWidget *stackedWidget);

    // rejestracja ekranów
    void registerScreen(ScreenId id, QWidget *screen);

    // nawigacja
    void goTo(ScreenId id);

    // info
    int pageIndex(ScreenId id) const;
    int getCurrentPageIndex() const;

private:
    QStackedWidget *m_stackedWidget;
    QHash<ScreenId, int> m_indices;
};

#endif // CONTROLLER_H
