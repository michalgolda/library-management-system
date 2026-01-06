#include "controller.h"

Controller::Controller(QStackedWidget *stackedWidget)
    : m_stackedWidget(stackedWidget)
{
}

void Controller::registerScreen(ScreenId id, QWidget *screen)
{
    const int index = m_stackedWidget->addWidget(screen);
    m_indices[id] = index;
}

void Controller::goTo(ScreenId id)
{
    if (!m_indices.contains(id))
        return;

    m_stackedWidget->setCurrentIndex(m_indices.value(id));
}

int Controller::pageIndex(ScreenId id) const
{
    return m_indices.value(id, -1);
}

int Controller::getCurrentPageIndex() const
{
    return m_stackedWidget->currentIndex();
}
