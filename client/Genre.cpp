//
// Created by stefan on 06.01.2022.
//

#include "Genre.h"

Genre::Genre(QWidget *parent) {
    (void) Genre::createComponents();

}

auto Genre::createComponents() noexcept -> Genre & {
    pMainLayout = new QVBoxLayout;

    Array < String > {
        "Drama",
        "Comedy",
        "Horror",
        "Novel",
        "Police",
        "Theatre"
    }.forEach ( [this] ( auto & str ) {
        checkboxes.add ( new QCheckBox ( str, this ) );
    } );

    return * this;
}

auto Genre::alignComponents() noexcept -> Genre & {

    this->setLayout(pMainLayout);

    checkboxes.forEach( [this] ( auto & p ) {
        this->pMainLayout->addWidget( p );
    } );

    return * this;
}

auto Genre::adjustComponents() noexcept -> Genre & {
    return * this;
}

auto Genre::connectComponents() noexcept -> Genre & {
    return * this;
}

auto Genre::styleComponents() noexcept -> Genre & {
    return * this;
}
