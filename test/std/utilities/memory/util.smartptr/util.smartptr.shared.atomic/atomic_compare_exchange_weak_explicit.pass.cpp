//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads
//
// This test uses new symbols that were not defined in the libc++ shipped on
// darwin11 and darwin12:
// XFAIL: availability=macosx10.7
// XFAIL: availability=macosx10.8

// <memory>

// shared_ptr

// template <class T>
// bool
// atomic_compare_exchange_weak_explicit(shared_ptr<T>* p, shared_ptr<T>* v,
//                                       shared_ptr<T> w, memory_order success,
//                                       memory_order failure);

// UNSUPPORTED: c++98, c++03

#include <memory>
#include <cassert>

#include "test_macros.h"

int main()
{
    {
        std::shared_ptr<int> p(new int(4));
        std::shared_ptr<int> v(new int(3));
        std::shared_ptr<int> w(new int(2));
        bool b = std::atomic_compare_exchange_weak_explicit(&p, &v, w,
                                                            std::memory_order_seq_cst,
                                                            std::memory_order_seq_cst);
        assert(b == false);
        assert(*p == 4);
        assert(*v == 4);
        assert(*w == 2);
    }
    {
        std::shared_ptr<int> p(new int(4));
        std::shared_ptr<int> v = p;
        std::shared_ptr<int> w(new int(2));
        bool b = std::atomic_compare_exchange_weak_explicit(&p, &v, w,
                                                            std::memory_order_seq_cst,
                                                            std::memory_order_seq_cst);
        assert(b == true);
        assert(*p == 2);
        assert(*v == 4);
        assert(*w == 2);
    }
}
