//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_JSON_BASIC_PARSER_HPP
#define BOOST_BEAST_JSON_BASIC_PARSER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/_experimental/json/detail/basic_parser.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdint>

#include <string>
#include <vector>

namespace boost {
namespace beast {
namespace json {

/** A parser for serialized JSON
*/
class basic_parser : private detail::parser_base
{
public:
    /// Returns `true` if the parser has completed without error
    BOOST_BEAST_DECL
    bool
    is_done() const noexcept;

    /** Reset the state, to parse a new document.
    */
    BOOST_BEAST_DECL
    void
    reset();

    template<
        class ConstBufferSequence,
        class = typename std::enable_if<
            ! std::is_convertible<
                ConstBufferSequence,
                net::const_buffer>::value>::type>
    std::size_t
    write(ConstBufferSequence const& buffers, error_code& ec);

    BOOST_BEAST_DECL
    std::size_t
    write(net::const_buffer buffer, error_code& ec);

    BOOST_BEAST_DECL
    void
    write_eof(error_code& ec);

protected:
    /** The representation of parsed numbers.
    */
    struct number
    {
        unsigned long long mant = 0;
        unsigned exp = 0;   // integer exponent
        bool neg = false;   // true if mantissa is negative
        bool pos = true;    // true if exponent is positive

        bool
        is_integral() const noexcept
        {
            return exp == 0;
        }
    };

    /// Constructor (default)
    BOOST_BEAST_DECL
    basic_parser();

    /// Returns the current key, or an empty string if no key.
    string_view
    key() const noexcept
    {
        return key_;
    }

    virtual
    void
    on_document_begin(error_code& ec) = 0;

    virtual
    void
    on_object_begin(error_code& ec) = 0;

    virtual
    void
    on_object_end(error_code& ec) = 0;

    virtual
    void
    on_array_begin(error_code& ec) = 0;

    virtual
    void
    on_array_end(error_code& ec) = 0;

    virtual
    void
    on_string_begin(error_code& ec) = 0;

    virtual
    void
    on_string_piece(string_view s, error_code& ec) = 0;

    virtual
    void
    on_string_end(error_code& ec) = 0;

    virtual
    void
    on_number(number n, error_code& ec) = 0;

    virtual
    void
    on_bool(bool b, error_code& ec) = 0;

    virtual
    void
    on_null(error_code& ec) = 0;

private:
    template<class Unsigned>
    static
    bool
    append_digit(
        Unsigned* value,
        char digit);

    enum class state : char;

    std::vector<state> stack_;
    std::string key_;
    number n_;
};

} // json
} // beast
} // boost

#include <boost/beast/_experimental/json/impl/basic_parser.hpp>
#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/json/impl/basic_parser.ipp>
#endif

#endif
