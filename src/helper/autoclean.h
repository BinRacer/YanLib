//
// Created by forkernel on 2025/4/15.
//

#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H
#include "crypto/aes.h"

namespace YanLib::helper {
    template<class T>
    class autoclean {
    private:
        T _value;

    public:
        autoclean(const autoclean &other) = delete;

        autoclean(autoclean &&other) = delete;

        autoclean &operator=(const autoclean &other) = delete;

        autoclean &operator=(autoclean &&other) = delete;

        explicit autoclean(T value);

        ~autoclean();

        T &get() const;
    };
}
#endif //AUTOCLEAN_H
