#ifndef READSPROFILER_LOGINWINDOW_H
#define READSPROFILER_LOGINWINDOW_H
#include "include.h"

class LoginWindow : public QWidget, public AbstractDrawable{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget * parent = nullptr);

    auto createComponents()     noexcept -> LoginWindow & override;
    auto alignComponents()      noexcept -> LoginWindow & override;
    auto adjustComponents()     noexcept -> LoginWindow & override;
    auto connectComponents()    noexcept -> LoginWindow & override;
    auto styleComponents()      noexcept -> LoginWindow & override;

private:

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
