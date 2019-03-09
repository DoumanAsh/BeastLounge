//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

// Test that header file is self-contained.
#include <boost/beast/_experimental/json/basic_parser.hpp>

#include <boost/beast/_experimental/unit_test/suite.hpp>

#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/asio/buffer.hpp>

namespace boost {
namespace beast {
namespace json {

class basic_parser_test : public beast::unit_test::suite
{
public:
    struct test_parser : basic_parser
    {
        test_parser() = default;

        void
        on_document_begin(error_code&) override
        {
        }

        void
        on_object_begin(error_code&) override
        {
        }

        void
        on_object_end(error_code&) override
        {
        }

        void
        on_array_begin(error_code&) override
        {
        }

        void
        on_array_end(error_code&) override
        {
        }

        void
        on_string_begin(error_code&) override
        {
        }

        void
        on_string_piece(string_view, error_code&) override
        {
        }

        void
        on_string_end(error_code&) override
        {
        }

        void
        on_number(number, error_code&) override
        {
        }

        void
        on_bool(bool, error_code&) override
        {
        }

        void
        on_null(error_code&) override
        {
        }
    };

    void
    good(string_view s)
    {
        error_code ec;
        test_parser p;
        auto const used = p.write(
            boost::asio::const_buffer(
                s.data(), s.size()), ec);
        if(BEAST_EXPECT(! ec))
        {
            if(BEAST_EXPECT(used == s.size()))
            {
                p.write_eof(ec);
                if(BEAST_EXPECT(! ec))
                    return;
            }
        }
        log << "fail: \"" << s << "\"\n";
    }

    void
    bad(string_view s)
    {
        error_code ec;
        test_parser p;
        auto const used = p.write(
            boost::asio::const_buffer(
                s.data(), s.size()), ec);
        if(! ec)
        {
            if(p.is_done())
            {
                if(BEAST_EXPECT(used != s.size()))
                    return;
            }
            else
            {
                p.write_eof(ec);
                if(BEAST_EXPECT(ec))
                    return;
            }
        }
        else
        {
            pass();
            return;
        }
        log << "fail: \"" << s << "\"\n";
    }

    void
    testObject()
    {
        good("{}");
        good("{ }");
        good("{ \t }");
        good("{ \"x\" : null }");
        good("{ \"x\" : {} }");
        good("{ \"x\" : { \"y\" : null } }");

        bad ("{");
        bad ("{{}}");
    }

    void
    testArray()
    {
        good("[]");
        good("[ ]");
        good("[ \t ]");
        good("[ \"\" ]");
        good("[ \" \" ]");
        good("[ \"x\" ]");
        good("[ \"x\", \"y\" ]");
        bad ("[");
        bad ("[ \"x\", ]");
    }

    void
    testString()
    {
        good("\""   "x"         "\"");
        good("\""   "xy"        "\"");
        good("\""   "x y"       "\"");

        bad ("\""   "\t"        "\"");
    }

    void
    testNumber()
    {
        good("0");
        good("0.0");
        good("0.10");
        good("0.01");
        good("1");
        good("10");
        good("1.5");
        good("10.5");
        good("10.25");
        good("10.25e0");
        good("1e1");
        good("1e10");
        good("1e+0");
        good("1e+1");
        good("0e+10");
        good("0e-0");
        good("0e-1");
        good("0e-10");
        good("1E+1");
        good("-0");
        good("-1");
        good("-1e1");

        bad ("");
        bad ("-");
        bad ("00");
        bad ("00.");
        bad ("00.0");
        bad ("1a");
        bad (".");
        bad ("1.");
        bad ("1+");
        bad ("0.0+");
        bad ("0.0e+");
        bad ("0.0e-");
        bad ("0.0e0-");
        bad ("0.0e");

    }

    void
    testMonostates()
    {
        good("true");
        good(" true");
        good("true ");
        good("\ttrue");
        good("true\t");
        good("\r\n\t true\r\n\t ");
        bad ("truu");
        bad ("tu");
        bad ("t");

        good("false");
        bad ("fals");
        bad ("fel");
        bad ("f");

        good("null");
        bad ("nul");
        bad ("no");
        bad ("n");
    }

    void run() override
    {
        testObject();
        testArray();
        testString();
        testNumber();
        testMonostates();
    }
};

BEAST_DEFINE_TESTSUITE(beast,json,basic_parser);

} // json
} // beast
} // boost
