//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_JSON_PARSE_FILE_HPP
#define BOOST_BEAST_JSON_PARSE_FILE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/_experimental/json/basic_parser.hpp>
#include <boost/beast/core/file.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/detail/clamp.hpp>

namespace boost {
namespace beast {
namespace json {

inline
void
parse_file(
    char const* path,
    basic_parser& parser,
    error_code& ec)
{
    file f;
    f.open(path, beast::file_mode::scan, ec);
    if(ec)
        return;
    flat_buffer b;
    auto remain = f.size(ec);
    if(ec)
        return;
    while(remain > 0)
    {
        auto amount = beast::detail::clamp(remain);
        auto mb = b.prepare(amount);
        b.commit(f.read(mb.data(), mb.size(), ec));
        if(ec)
            return;
        parser.write(b.data(), ec);
        if(ec)
            return;
        remain -= b.size();
        b.clear();
    }
    parser.write_eof(ec);
    if(ec)
        return;
    // finished
}

} // json
} // beast
} // boost

#endif
