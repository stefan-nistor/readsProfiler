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
    tableHeader.removeFirst();

    this->setColumnCount( tableHeader.count() );
    this->setHorizontalHeaderLabels( tableHeader );

    return * this;
}

auto LibraryTable::connectComponents() noexcept -> LibraryTable & {

    return * this;
}

auto LibraryTable::styleComponents() noexcept -> LibraryTable & {


    horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeMode::Stretch );

    setHorizontalHeaderLabels(tableHeader);

    setFocusPolicy( Qt::NoFocus );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );
    verticalHeader()->setVisible(false);
    return * this;
}
#include "RequestHandler.h"
auto LibraryTable::addEntry(String const & jsonEntry) noexcept -> void {
    JSON bookData = JSON :: parse ( jsonEntry );

    int rowIndex = rowCount();
    setRowCount( rowIndex + 1 );

    setItem( rowIndex, ISBN_COL, new QTableWidgetItem (String(bookData.getInt("ISBN"))));
    setItem( rowIndex, TITLE_COL, new QTableWidgetItem ( bookData.getString("title") ) );
    setItem( rowIndex, AUTHOR_COL, new QTableWidgetItem ( bookData.getString("author") ) );
    setItem( rowIndex, GENRE_COL, new QTableWidgetItem ( bookData.getString("genre") ) );
    setItem( rowIndex, YEAR_COL, new QTableWidgetItem ( String(bookData.getInt("year")) ) );
    setItem( rowIndex, RATING_COL, new QTableWidgetItem ( String( bookData.getInt("rating")) ) );

    auto readButton = new QPushButton("Read");
    connect ( readButton, & QPushButton :: clicked, [this, rowIndex] {
        readPressed(rowIndex);
    });

    auto downloadButton = new QPushButton("Download");
    connect( downloadButton, & QPushButton :: clicked, [this, rowIndex] {
        downloadPressed(rowIndex);
    });

    setCellWidget(rowIndex, READ_COL, readButton);
    setCellWidget(rowIndex, DOWNLOAD_COL, downloadButton);
}

#include "readWindow.h"

void LibraryTable::readPressed(int rowIndex) {
    auto entry = item(rowIndex, 0)->text().toStdString();

    auto * readWindow = new ReadWindow();

    readWindow->setText(RequestHandler ::makeReadRequest(Int::parse(entry)));
    readWindow->resize(800, 600);
    readWindow->init();
    readWindow->show();
}

void LibraryTable::downloadPressed(int rowIndex) {
    auto entry = item(rowIndex, 0)->text().toStdString();
    RequestHandler::makeDownloadRequest(Int::parse(entry));
}
