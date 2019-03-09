//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

// Test that header file is self-contained.
#include <boost/beast/_experimental/json/error.hpp>

#include <boost/beast/_experimental/unit_test/suite.hpp>
#include <memory>

namespace boost {
namespace beast {
namespace json {

class error_test : public unit_test::suite
{
public:
    void check(error e)
    {
        auto const ec = make_error_code(e);
        ec.category().name();
        BEAST_EXPECT(! ec.message().empty());
    }

    void check(condition c, error e)
    {
        {
            auto const ec = make_error_code(e);
            BEAST_EXPECT(ec.category().name() != nullptr);
            BEAST_EXPECT(! ec.message().empty());
            BEAST_EXPECT(ec == c);
        }
        {
            auto ec = make_error_condition(c);
            BEAST_EXPECT(ec.category().name() != nullptr);
            BEAST_EXPECT(! ec.message().empty());
            BEAST_EXPECT(ec == c);
        }
    }

    void run() override
    {
        check(condition::parse_error, error::syntax);
        check(condition::parse_error, error::extra_data);
        check(condition::parse_error, error::mantissa_overflow);
        check(condition::parse_error, error::exponent_overflow);
    }
};

BEAST_DEFINE_TESTSUITE(beast,json,error);

} // json
} // beast
} // boost
