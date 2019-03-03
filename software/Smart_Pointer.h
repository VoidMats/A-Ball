#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include <memory>

template <class T>
using u_Ptr = std::unique_ptr<T>;
template <class T2>
using s_Ptr = std::shared_ptr<T2>;
template <class T3>
using w_Ptr = std::weak_ptr<T3>;

#endif
