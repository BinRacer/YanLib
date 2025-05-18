//
// Created by forkernel on 2025/4/15.
//

#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H

namespace YanLib::helper {
    template <typename T, bool is_file = false> class autoclean {
    private:
        T _value;

        void cleanup();

    public:
        autoclean(const autoclean &other) = delete;

        autoclean(autoclean &&other) = delete;

        autoclean &operator=(const autoclean &other) = delete;

        autoclean &operator=(autoclean &&other) = delete;

        autoclean() = delete;

        explicit autoclean(T value);

        explicit autoclean(T &value);

        ~autoclean();

        operator T&();

        operator T*();

        autoclean &operator=(const T &other);

        autoclean &operator=(T &&other);

        [[nodiscard]] bool is_ok() const;
    };
} // namespace YanLib::helper
#endif // AUTOCLEAN_H
