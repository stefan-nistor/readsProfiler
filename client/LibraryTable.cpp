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

    tableHeader.append("ISBN");
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

    setFocusPolicy( Qt::NoFocus );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );



    return * this;
}
