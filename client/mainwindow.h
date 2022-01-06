#ifndef READSPROFILER_MAINWINDOW_H
#define READSPROFILER_MAINWINDOW_H

#include "include.h"
#include "Filter.h"
#include "Genre.h"
#include "LibraryTable.h"
#include "LoginWindow.h"

class MainWindow : public QWidget, public AbstractDrawable{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);

    auto createComponents()     noexcept -> MainWindow & override;
    auto alignComponents()      noexcept -> MainWindow & override;
    auto adjustComponents()     noexcept -> MainWindow & override;
    auto connectComponents()    noexcept -> MainWindow & override;
    auto styleComponents()      noexcept -> MainWindow & override;

private:
    UniquePointer < Filter > pFilter {nullptr};
    UniquePointer < QLayout > pMainLayout {nullptr};
    UniquePointer < LibraryTable > pLibraryTable {nullptr};
    UniquePointer < QSplitter > pSplitter {nullptr};

    UniquePointer < LoginWindow > pLoginWindow {nullptr};

};


#endif //READSPROFILER_MAINWINDOW_H
