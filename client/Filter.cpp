#include "Filter.h"


Filter::Filter(QWidget *parent) {
    (void) Filter::createComponents();
}

auto Filter::createComponents() noexcept -> Filter & {
    pMainLayout = new QVBoxLayout();

    pTitleLineEdit = new QLineEdit(this);
    pAuthorLineEdit = new QLineEdit(this);

    pTitleLabel = new QLabel(this);
    pAuthorLabel = new QLabel (this);

    pMinDateEdit = new QDateEdit (this);
    pMaxDateEdit = new QDateEdit (this);
    pRatingBox = new QSpinBox (this);

    pMinDateLabel = new QLabel(this);
    pMaxDateLabel = new QLabel(this);
    pRatingLabel = new QLabel(this);

    pGenreScrollArea = new QScrollArea(this);
    pGenreLabel = new QLabel (this);
    pGenres = new Genre ();

    pGenres->init();


    pFilterButton = new QPushButton(this);
    pRecommendButton = new QPushButton (this);

    return * this;
}

auto Filter::alignComponents() noexcept -> Filter & {

    this->setLayout(pMainLayout);

    pMainLayout->addWidget( pTitleLabel );
    pMainLayout->addWidget( pTitleLineEdit );

    pMainLayout->addWidget( pAuthorLabel );
    pMainLayout->addWidget( pAuthorLineEdit );

    pMainLayout->addWidget( pMinDateLabel );
    pMainLayout->addWidget( pMinDateEdit );

    pMainLayout->addWidget( pMaxDateLabel );
    pMainLayout->addWidget( pMaxDateEdit );

    pMainLayout->addWidget( pRatingLabel );
    pMainLayout->addWidget( pRatingBox );

    pMainLayout->addWidget( pGenreLabel );
    pMainLayout->addWidget( pGenres );

    pMainLayout->addWidget( pGenreScrollArea );
    pGenreScrollArea->setWidget(pGenres);


    pMainLayout->addWidget( pFilterButton );
    pMainLayout->addWidget( pRecommendButton) ;

    return * this;
}

auto Filter::adjustComponents() noexcept -> Filter & {

    pTitleLabel->setBuddy( pTitleLineEdit );
    pAuthorLabel->setBuddy( pAuthorLineEdit );

    pMinDateLabel->setBuddy( pMinDateEdit );
    pMaxDateLabel->setBuddy( pMaxDateEdit );

    pRatingLabel->setBuddy( pRatingBox );

    pGenreLabel->setBuddy( pGenreScrollArea );

    return * this;
}

auto Filter::connectComponents() noexcept -> Filter & {

    connect(pFilterButton, SIGNAL(clicked()), this, SLOT(filterPressed()));

    return * this;
}

auto Filter::styleComponents() noexcept -> Filter & {

    setMinimumWidth(300);

    pTitleLabel->setText( "Title" );
    pAuthorLabel->setText( "Author" );
    pMinDateLabel->setText( "After" );
    pMaxDateLabel->setText( "Before" );
    pRatingLabel->setText( "Rating" );
    pGenreLabel->setText( "Genre" );

    pFilterButton->setText( "Get Books" );
    pRecommendButton->setText( "Recommend" );

    pMinDateEdit->setDisplayFormat( "yyyy" );
    pMaxDateEdit->setDisplayFormat( "yyyy" );

    QDate minDate, maxDate;
    minDate.setDate(1970,1,1);
    maxDate.setDate(2022,1,1);
    pMinDateEdit->setDate(minDate);
    pMaxDateEdit->setDate(maxDate);
    pRatingBox->setMinimum(1);
    pRatingBox->setMaximum(5);

    return * this;
}

void Filter::filterPressed() {

    JSON bookList;
    auto list = RequestHandler :: makeFilterBooksRequest(this->getFilters());
    bookList.put("books", JSON::Array :: parse(list) );

    filteredBookList = bookList.toString();

    emit listReceived(filteredBookList);
}

auto Filter::getFilters() noexcept -> String {
    JSON result;
    JSON filters;

    result.put("title", pTitleLineEdit->text().toStdString());
    result.put("author", pAuthorLineEdit->text().toStdString());
    result.put("after", Int::parse(pMinDateEdit->text().toStdString()));
    result.put("before", Int::parse(pMaxDateEdit->text().toStdString()));
    result.put("rating", Int::parse (pRatingBox->text().toStdString()));
    result.put("genre",  JSON::Array::parse(this->pGenres->getGenre()));

    auto gen = this->pGenres->getGenre();

    filters.put("filter", result);

    return filters.toString();
}