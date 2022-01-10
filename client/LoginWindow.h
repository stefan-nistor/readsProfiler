#ifndef READSPROFILER_LOGINWINDOW_H
#define READSPROFILER_LOGINWINDOW_H
#include "../dependencies/include.h"

class LoginWindow : public QWidget, public AbstractDrawable{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget * parent = nullptr);

    auto createComponents()     noexcept -> LoginWindow & override;
    auto alignComponents()      noexcept -> LoginWindow & override;
    auto adjustComponents()     noexcept -> LoginWindow & override;
    auto connectComponents()    noexcept -> LoginWindow & override;
    auto styleComponents()      noexcept -> LoginWindow & override;

    auto closeEvent( QCloseEvent * ) noexcept -> void override;

    constexpr auto getLoggedStatus () const noexcept -> bool {return this->isConnected;}

    ~LoginWindow() noexcept override {

        pMainLayout->removeWidget( pInfoLabel );
        pMainLayout->removeItem( pCredentialLayout );
        pMainLayout->removeWidget( pLoginButton );
        pMainLayout->removeWidget( pCreateLabel );
        pMainLayout->removeWidget( pCreateButton );

        pCredentialLayout->removeItem( pLabelLayout );
        pCredentialLayout->removeItem( pInputLayout );

        pInputLayout->removeWidget(pUserEdit);
        pInputLayout->removeWidget(pPassEdit);

        pLabelLayout->removeWidget( pUserLabel );
        pLabelLayout->removeWidget( pPassLabel );
    }

public slots:
    void loginPressed();
    void createAccountPressed();

signals:
    void closed();

private:

    bool isConnected {false};

    UniquePointer < QLayout > pMainLayout       {nullptr};
    UniquePointer < QLayout > pCredentialLayout {nullptr};
    UniquePointer < QLayout > pInputLayout      {nullptr};
    UniquePointer < QLayout > pLabelLayout      {nullptr};

    UniquePointer < QLabel > pInfoLabel     {nullptr};
    UniquePointer < QLabel > pUserLabel     {nullptr};
    UniquePointer < QLabel > pPassLabel     {nullptr};
    UniquePointer < QLabel > pCreateLabel   {nullptr};

    UniquePointer < QLineEdit > pUserEdit {nullptr};
    UniquePointer < QLineEdit > pPassEdit {nullptr};

    UniquePointer < QPushButton > pLoginButton {nullptr};
    UniquePointer < QPushButton > pCreateButton {nullptr};

};


#endif //READSPROFILER_LOGINWINDOW_H
