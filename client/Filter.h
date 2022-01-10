#ifndef READSPROFILER_FILTER_H
#define READSPROFILER_FILTER_H
#include "../dependencies/include.h"
#include "Genre.h"
#include <CDS/Pointer>
#include "RequestHandler.h"


using namespace cds;

class Filter : public QWidget, public AbstractDrawable{
    Q_OBJECT
public:

    explicit Filter (QWidget * parent = nullptr);

    auto createComponents()     noexcept -> Filter & override;
    auto alignComponents()      noexcept -> Filter & override;
    auto adjustComponents()     noexcept -> Filter & override;
    auto connectComponents()    noexcept -> Filter & override;
    auto styleComponents()      noexcept -> Filter & override;

    auto getFilters() noexcept -> String;



public slots:
    void filterPressed();

signals:
    void listReceived(String const & list);

private:

    UniquePointer < QLayout >       pMainLayout        {nullptr};

    UniquePointer < QLineEdit >     pTitleLineEdit     {nullptr};
    UniquePointer < QLineEdit >     pAuthorLineEdit    {nullptr};

    UniquePointer < QLabel >        pTitleLabel        {nullptr};
    UniquePointer < QLabel >        pAuthorLabel       {nullptr};

    UniquePointer < QDateEdit >     pMaxDateEdit       {nullptr};
    UniquePointer < QDateEdit >     pMinDateEdit       {nullptr};
    UniquePointer < QSpinBox >      pRatingBox         {nullptr};

    UniquePointer < QLabel >        pMaxDateLabel      {nullptr};
    UniquePointer < QLabel >        pMinDateLabel      {nullptr};
    UniquePointer < QLabel >        pRatingLabel       {nullptr};

    UniquePointer < QScrollArea >   pGenreScrollArea   {nullptr};
    UniquePointer < QLabel >        pGenreLabel        {nullptr};
    UniquePointer < Genre >         pGenres            {nullptr};

    UniquePointer < QPushButton >   pFilterButton      {nullptr};
    UniquePointer < QPushButton >   pRecommendButton   {nullptr};

    String filteredBookList {};

};


#endif //READSPROFILER_FILTER_H
