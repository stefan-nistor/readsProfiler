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

    pRatingLabel->setBuddy( pMinDateEdit );

    pGenreLabel->setBuddy( pGenreScrollArea );

    return * this;
}

auto Filter::connectComponents() noexcept -> Filter & {
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

    pFilterButton->setText( "Filter" );
    pRecommendButton->setText( "Recommend" );

    pMinDateEdit->setDisplayFormat( "yyyy" );
    pMaxDateEdit->setDisplayFormat( "yyyy" );

    QDate minDate;
    minDate.setDate(1970,1,1);

    pMinDateEdit->setDate(minDate);
    pMaxDateEdit->setDate(QDate::currentDate());

    return * this;
}
