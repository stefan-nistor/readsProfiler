//
// Created by stefan on 10.01.2022.
//

#include "readWindow.h"

ReadWindow::ReadWindow(QWidget *parent) {
    (void) ReadWindow::createComponents();
}

auto ReadWindow::createComponents() noexcept -> ReadWindow & {
    pMainLayout = new QVBoxLayout ();
    pTextViewer = new QTextEdit (this);
    return * this;
}

auto ReadWindow::alignComponents() noexcept -> ReadWindow & {
    setLayout(pMainLayout);
    pMainLayout->addWidget(pTextViewer);
    return * this;
}

auto ReadWindow::adjustComponents() noexcept -> ReadWindow & {
    pTextViewer->setReadOnly(true);

    return * this;
}

auto ReadWindow::connectComponents() noexcept -> ReadWindow & {
    return * this;
}

auto ReadWindow::styleComponents() noexcept -> ReadWindow & {
    pTextViewer->setText(text);
    return * this;
}
