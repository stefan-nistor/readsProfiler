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

    auto addEntry (String const &) noexcept -> void;

public slots:
    void readPressed(int rowIndex);
    void downloadPressed(int rowIndex);

private:

    QStringList  tableHeader {nullptr};

    enum{
        ISBN_COL,
        TITLE_COL,
        AUTHOR_COL,
        GENRE_COL,
        YEAR_COL,
        RATING_COL,
        READ_COL,
        DOWNLOAD_COL
    };
};


#endif //READSPROFILER_LIBRARYTABLE_H
