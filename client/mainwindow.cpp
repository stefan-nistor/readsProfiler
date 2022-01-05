//
// Created by stefan on 05.01.2022.
//

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) {

    this->pMainLayout   = new QHBoxLayout   (this);

    this->pMainLayout->addWidget(pFilterGroup);
    this->pMainLayout->addWidget(pTableWidget);

}



MainWindow::~MainWindow() {
    delete this->pFilterGroup;
    delete this->pTableWidget;
    delete this->pMainLayout;
}
