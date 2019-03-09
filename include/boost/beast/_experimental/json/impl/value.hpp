//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_JSON_IMPL_VALUE_HPP
#define BOOST_BEAST_JSON_IMPL_VALUE_HPP

namespace boost {
namespace beast {
namespace json {

template<class T, class>
value::
value(T&& t)
{
    v_.assign(std::forward<T>(t), *store_);
}

template<class T, class>
value&
value::operator=(T&& t)
{
    v_.assign(std::forward<T>(t), *store_);
    return *this;
}

} // json
} // beast
} // boost

#endif
