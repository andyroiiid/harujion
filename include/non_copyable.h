//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_NON_COPYABLE_H
#define HARUJION_NON_COPYABLE_H

class NonCopyable {
public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable &) = delete;

    NonCopyable &operator=(const NonCopyable &) = delete;
};

#endif //HARUJION_NON_COPYABLE_H
