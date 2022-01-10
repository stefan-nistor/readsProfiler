#ifndef READSPROFILER_GENRE_H
#define READSPROFILER_GENRE_H
#include "../dependencies/include.h"
#include <CDS/Array>
#include <QCheckBox>
using namespace cds;

class Genre : public QWidget, public AbstractDrawable{
    Q_OBJECT
public:

    explicit Genre (QWidget * parent = nullptr);

    auto createComponents()     noexcept -> Genre & override;
    auto alignComponents()      noexcept -> Genre & override;
    auto adjustComponents()     noexcept -> Genre & override;
    auto connectComponents()    noexcept -> Genre & override;
    auto styleComponents()      noexcept -> Genre & override;

    auto getGenre() noexcept -> String;
    auto uncheckBoxes () noexcept -> void;


private:

    UniquePointer < QLayout > pMainLayout {nullptr};

    Array < UniquePointer < QCheckBox > > checkboxes;

};


#endif //READSPROFILER_GENRE_H
