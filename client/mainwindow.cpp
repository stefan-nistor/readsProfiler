//
// Created by stefan on 05.01.2022.
//

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) {

    (void) MainWindow::createComponents();

}

auto MainWindow::createComponents() noexcept -> MainWindow & {

    this->pMainLayout = new QHBoxLayout ();

    this->pFilter = new Filter( this );
    this->pLibraryTable = new LibraryTable( this );
    this->pSplitter = new QSplitter( Qt::Horizontal );

    this-> pLoginWindow = new LoginWindow ( this );

    return * this;
}

auto MainWindow::alignComponents() noexcept -> MainWindow & {

    this->setLayout(pMainLayout);
    this->pMainLayout->addWidget(pSplitter);

    this->pSplitter->addWidget( pFilter );
    this->pSplitter->addWidget( pLibraryTable );

    return * this;
}

auto MainWindow::adjustComponents() noexcept -> MainWindow & {
    this->pFilter->init();
    this->pLibraryTable->init();
    this->pLoginWindow->init();
    this->pLoginWindow->show();
    return * this;
}

auto MainWindow::connectComponents() noexcept -> MainWindow & {
    return * this;
}

auto MainWindow::styleComponents() noexcept -> MainWindow & {

    // Do not understand how the math works here, but it works
    this->pSplitter->setSizes(QList < int > {sizeHint().width() * 1/3, sizeHint().width() * 2/3 * 5});

    return * this;
}
