//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_JSON_KIND_HPP
#define BOOST_BEAST_JSON_KIND_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/static_const.hpp>

namespace boost {
namespace beast {
namespace json {

enum class kind
{
    object,
    array,
    string,
    signed64,
    unsigned64,
    floating,       // double (scientific?)
    boolean,
    null
};

struct object_t
{
};

BOOST_BEAST_INLINE_VARIABLE(object, object_t);

struct array_t
{
};

BOOST_BEAST_INLINE_VARIABLE(array, array_t);

struct null_t
{
};

BOOST_BEAST_INLINE_VARIABLE(null, null_t);

} // json
} // beast
} // boost

#endif
