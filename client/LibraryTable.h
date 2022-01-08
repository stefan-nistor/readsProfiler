//
// Created by stefan on 06.01.2022.
//

#ifndef READSPROFILER_LIBRARYTABLE_H
#define READSPROFILER_LIBRARYTABLE_H
#include "../dependencies/include.h"
#include <QTableWidget>
#include <QAbstractItemView>

class LibraryTable : public QTableWidget, public AbstractDrawable{
    Q_OBJECT
public:
    explicit LibraryTable (QWidget * parent = nullptr);

    auto createComponents()     noexcept -> LibraryTable & override;
    auto alignComponents()      noexcept -> LibraryTable & override;
    auto adjustComponents()     noexcept -> LibraryTable & override;
    auto connectComponents()    noexcept -> LibraryTable & override;
    auto styleComponents()      noexcept -> LibraryTable & override;

private:

    QStringList  tableHeader {nullptr};


};


#endif //READSPROFILER_LIBRARYTABLE_H
