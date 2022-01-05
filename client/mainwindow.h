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

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);

    ~MainWindow();

private:

    QHBoxLayout * pMainLayout       {nullptr};
    QTableWidget * pTableWidget     {nullptr};
    QGroupBox * pFilterGroup        {nullptr};
    QMenuBar * pMenuBar             {nullptr};


//    QGroupBox * libGroup            {nullptr};
//    QGroupBox * loginGroup          {nullptr};
//
//    QMenuBar * menuBar              {nullptr};
//
//    QHBoxLayout * libraryLayout     {nullptr};
//    QGroupBox * filterGroup         {nullptr};
//
//    QVBoxLayout * layoutPage        {nullptr};
//    QComboBox   * comboBoxPage      {nullptr};
//    QLabel *    labelPage           {nullptr};
//
//    QVBoxLayout * layoutItemsPage   {nullptr};
//    QComboBox * comboBoxItemsPage   {nullptr};
//    QLabel * labelItemsPage         {nullptr};
//
//    QVBoxLayout * layoutAuthorTitle {nullptr};
//    QVBoxLayout * layoutAuthor      {nullptr};
//    QLabel *    labelAuthor         {nullptr};
//    QLineEdit * lineEditAuthor      {nullptr};
//
//    QLabel * labelTitle             {nullptr};



};


#endif //READSPROFILER_MAINWINDOW_H
