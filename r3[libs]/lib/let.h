#ifndef LET_H
#define LET_H

#include "core.h"

template <typename T>
class let {
    public:
        T data;

        let(const T& value) : data(value) {}

        template <typename U, typename = std::enable_if_t<!std::is_same_v<std::decay_t<U>, let>>>
        let(U&& value) : data(std::forward<U>(value)) {}

        T&       operator*() { return data; }
        const T& operator*() const { return data; }

        T*       operator->() { return &data; }
        const T* operator->() const { return &data; }

        let& operator=(const T& value) {
            data = value;
            return *this;
        }
};

template <typename U>
let(U) -> let<std::decay_t<U>>;

#endif  // LET_H
