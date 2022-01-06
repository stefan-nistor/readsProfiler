//
// Created by stefan on 06.01.2022.
//

#include "LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) {
    (void) LoginWindow::createComponents();
}

auto LoginWindow::createComponents() noexcept -> LoginWindow & {

    pMainLayout = new QVBoxLayout();
    pCredentialLayout = new QHBoxLayout();
    pInputLayout = new QVBoxLayout();
    pLabelLayout = new QVBoxLayout();

    pUserLabel = new QLabel ( this );
    pPassLabel = new QLabel ( this );
    pCreateLabel = new QLabel ( this );
    pInfoLabel = new QLabel ( this );

    pUserEdit = new QLineEdit ( this );
    pPassEdit = new QLineEdit ( this );

    pLoginButton = new QPushButton ( this );
    pCreateButton = new QPushButton ( this );

    return * this;
}

auto LoginWindow::alignComponents() noexcept -> LoginWindow & {

    this->setLayout( pMainLayout );

    pMainLayout->addWidget( pInfoLabel );
    pMainLayout->addItem( pCredentialLayout );
    pMainLayout->addWidget( pLoginButton );
    pMainLayout->addWidget( pCreateLabel );
    pMainLayout->addWidget( pCreateButton );

    pCredentialLayout->addItem( pLabelLayout );
    pCredentialLayout->addItem( pInputLayout );

    pInputLayout->addWidget(pUserEdit);
    pInputLayout->addWidget(pPassEdit);

    pLabelLayout->addWidget( pUserLabel );
    pLabelLayout->addWidget( pPassLabel );

    return * this;
}

auto LoginWindow::adjustComponents() noexcept -> LoginWindow & {

    pUserLabel->setBuddy( pUserEdit );
    pPassLabel->setBuddy( pPassEdit );

    return * this;
}

auto LoginWindow::connectComponents() noexcept -> LoginWindow & {
    return * this;
}

auto LoginWindow::styleComponents() noexcept -> LoginWindow & {

    pInfoLabel->setText("Login");
    pUserLabel->setText("Username: ");
    pPassLabel->setText("Password: ");

    pCreateLabel->setText("Do not have an account?");

    pLoginButton->setText("Login");
    pCreateButton->setText("Create account");

    pPassEdit->setEchoMode(QLineEdit::Password);

    return * this;
}
