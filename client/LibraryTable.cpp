//
// Created by stefan on 06.01.2022.
//

#include "LibraryTable.h"
#include <QHeaderView>

LibraryTable::LibraryTable(QWidget *parent) : QTableWidget( parent ){
    ( void ) LibraryTable::createComponents();
}

auto LibraryTable::createComponents() noexcept -> LibraryTable & {

    return * this;
}

auto LibraryTable::alignComponents() noexcept -> LibraryTable & {
    return * this;
}

auto LibraryTable::adjustComponents() noexcept -> LibraryTable & {

    //tableHeader.append("ISBN");
    tableHeader.append("Title");
    tableHeader.append("Author");
    tableHeader.append("Genre");
    tableHeader.append("Publish Year");
    tableHeader.append("Rating");
    tableHeader.append("Read");
    tableHeader.append("Download");

    this->setColumnCount( tableHeader.count() );
    this->setHorizontalHeaderLabels( tableHeader );

    return * this;
}

auto LibraryTable::connectComponents() noexcept -> LibraryTable & {
    return * this;
}

auto LibraryTable::styleComponents() noexcept -> LibraryTable & {

    setColumnHidden(0, true);

    horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeMode::Stretch );

    setHorizontalHeaderLabels(tableHeader);

    setFocusPolicy( Qt::NoFocus );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );

    return * this;
}

auto LibraryTable::addEntry(String const & jsonEntry) noexcept -> void {
    JSON bookData = JSON :: parse ( jsonEntry );

    int rowIndex = rowCount();
    setRowCount( rowIndex + 1 );

    setItem( rowIndex, TITLE_COL, new QTableWidgetItem ( bookData.getString("title") ) );
    setItem( rowIndex, AUTHOR_COL, new QTableWidgetItem ( bookData.getString("author") ) );
    setItem( rowIndex, GENRE_COL, new QTableWidgetItem ( bookData.getString("genre") ) );
    setItem( rowIndex, YEAR_COL, new QTableWidgetItem ( String(bookData.getInt("year")) ) );
    setItem( rowIndex, RATING_COL, new QTableWidgetItem ( String( bookData.getInt("rating")) ) );

    setCellWidget(rowIndex, READ_COL, new QPushButton("Read"));
    setCellWidget(rowIndex, DOWNLOAD_COL, new QPushButton("Download"));

}
