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

auto Genre::getGenre() noexcept -> String {
    JSON::Array checkedGenres;
    int size = 0;
    for (auto const & item : checkboxes) {
        if (item->isChecked()) {
            checkedGenres.put(size, item->text().toStdString());
            size++;
//            std::cout << item->text().toStdString() << '\n';
        }
    }
    return checkedGenres.toString();
}

auto Genre::uncheckBoxes() noexcept -> void {
    checkboxes.forEach( [this] ( auto & p ) {
        p->setCheckState(Qt::Unchecked);
    } );
}
