#ifndef READSPROFILER_MAINWINDOW_H
#define READSPROFILER_MAINWINDOW_H
#include <QMainWindow>
#include <CDS/String>
#include <CDS/Thread>
#include <CDS/Mutex>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QTableWidget>
#include <QSplitter>
#include "Filter.h"
#include "Genre.h"
#include "LibraryTable.h"


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
};


#endif //READSPROFILER_MAINWINDOW_H
