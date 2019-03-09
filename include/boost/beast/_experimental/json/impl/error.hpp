//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_JSON_IMPL_ERROR_HPP
#define BOOST_BEAST_JSON_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::json::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::json::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace json {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // json
} // beast
} // boost

#endif
