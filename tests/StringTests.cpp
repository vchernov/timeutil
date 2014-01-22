#include <UnitTest++.h>

#include "../timeutil/Timestamp.h"

using namespace timeutil;

SUITE(String) {

struct StringFixture {
    StringFixture() {
        t1 = Timestamp(1, 2);
        t2 = Timestamp(3, 4);
        zero = Timestamp::null;
        now = Timestamp::now();
    }

    Timestamp t1;
    Timestamp t2;
    Timestamp zero;
    Timestamp now;
};

TEST_FIXTURE(StringFixture, ToString) {
    CHECK_EQUAL(std::string("00:00:00.000000"), zero.toStrTimeGM());
    CHECK_EQUAL(std::string("1970.01.01 00:00:00.000000"), zero.toStrDateTimeGM());
    CHECK_EQUAL(std::string("00:00:01.000002"), t1.toStrTimeGM());
    CHECK_EQUAL(std::string("3.000004"), Timestamp(3, 4).toStr());
}

TEST_FIXTURE(StringFixture, FromString) {
    Timestamp tmp;

    CHECK(Timestamp::parse("1988.01.18 12:34:56.789000", tmp));
    CHECK(Timestamp::parse("0000.00.00 00:00:00", tmp));
    CHECK(!Timestamp::parse("fake", tmp));

    CHECK(Timestamp::parse(now.toStrDateTime(), tmp));
    CHECK(now == tmp);
}

}
