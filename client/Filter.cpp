//
// Created by stefan on 06.01.2022.
//

#include "Filter.h"


Filter::Filter(QWidget *parent) {
    (void) Filter::createComponents();
}

auto Filter::createComponents() noexcept -> Filter & {
    pMainLayout = new QVBoxLayout(this);

    pTitleLineEdit = new QLineEdit(this);
    pAuthorLineEdit = new QLineEdit(this);

    pTitleLabel = new QLabel(this);
    pAuthorLabel = new QLabel (this);

    pMinDateEdit = new QDateEdit (this);
    pRatingBox = new QSpinBox (this);

    pMinDateLabel = new QLabel(this);
    pRatingLabel = new QLabel(this);

    pGenreScrollArea = new QScrollArea(this);
    pGenreLabel = new QLabel (this);

    pFilterButton = new QPushButton(this);
    pRecommendButton = new QPushButton (this);

    return * this;
}

auto Filter::alignComponents() noexcept -> Filter & {

    pMainLayout->addWidget(pTitleLineEdit);



    return * this;
}
