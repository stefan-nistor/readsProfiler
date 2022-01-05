//
// Created by stefan on 06.01.2022.
//

#ifndef READSPROFILER_ABSTRACTDRAWABLE_H
#define READSPROFILER_ABSTRACTDRAWABLE_H

class AbstractDrawable {
public:
    virtual auto createComponents() noexcept -> AbstractDrawable & = 0;
    virtual auto alignComponents() noexcept -> AbstractDrawable & = 0;
    virtual auto adjustComponents() noexcept -> AbstractDrawable & = 0;
    virtual auto connectComponents() noexcept -> AbstractDrawable & = 0;
    virtual auto styleComponents() noexcept -> AbstractDrawable & = 0;

    virtual auto init () noexcept -> AbstractDrawable & {
        return this
        ->adjustComponents()
        .alignComponents()
        .connectComponents()
        .styleComponents();
    }
};

#endif //READSPROFILER_ABSTRACTDRAWABLE_H
