#ifndef MAKE_UNIQUE_HPP_INCLUDED
#define MAKE_UNIQUE_HPP_INCLUDED

#include <memory>

namespace std {

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}

}

#endif // MAKE_UNIQUE_HPP_INCLUDED
