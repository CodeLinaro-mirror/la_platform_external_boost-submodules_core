// Copyright (c) 2023 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Tests that boost::swap with types in namespace boost is not
// found via ADL and does not introduce infinite recursion.

#include <boost/core/swap.hpp>
#include <boost/config.hpp>

namespace boost {

struct some_boost_type {};

}

namespace test_ns {

template< typename T >
class X
{
private:
    X(X const&);

public:
    X() {}
};

template< typename T1, typename T2 >
inline void swap(T1&, T2&)
{
}

}

int main()
{
    test_ns::X< boost::some_boost_type > x;
    boost::swap(x, x);
    return BOOST_NOEXCEPT_EXPR(boost::swap(x, x));
}
