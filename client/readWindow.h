//
// Created by stefan on 10.01.2022.
//

#ifndef READSPROFILER_READWINDOW_H
#define READSPROFILER_READWINDOW_H
#define CDS_QT
#include <QWidget>
#include "AbstractDrawable.h"
#include <CDS/Pointer>
#include <QTextEdit>
#include <QPushButton>
#include <QLayout>

using namespace cds;

class ReadWindow : public QWidget, public AbstractDrawable{
    Q_OBJECT
public:

    explicit ReadWindow (QWidget * parent = nullptr);

    auto createComponents()     noexcept -> ReadWindow & override;
    auto alignComponents()      noexcept -> ReadWindow & override;
    auto adjustComponents()     noexcept -> ReadWindow & override;
    auto connectComponents()    noexcept -> ReadWindow & override;
    auto styleComponents()      noexcept -> ReadWindow & override;

    inline auto setText(String const & text) noexcept -> void {
        this->text = text;
    }

    inline auto setTitle(String const & title) noexcept -> void {
        this->title = title;
    }

    inline auto setAuthor(String const & author) noexcept -> void {
        this->author = author;
    }

private:

    String text {};
    String title {};
    String author {};

    UniquePointer < QTextEdit > pTextViewer {nullptr};
    UniquePointer < QLayout >  pMainLayout {nullptr};

};


#endif //READSPROFILER_READWINDOW_H
