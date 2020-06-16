#include <cassert>
#include <sstream>

#include "full-enum.hpp"

DEF_ENUM(Day, mon, tue, wed, thu, fri, sat, sun)

int main() {
    Day d = Day::mon;

    assert(d.size() == 7);
    assert(d.toString() == std::string("mon"));

    d = Day::fromString("fri").value();

    assert(d == Day::fri);

    std::stringstream ss;
    ss << d;
    assert(ss.str() == "fri");

    ss.str("");
    ss << "wed";
    ss >> d;
    assert(d == Day::wed);

    Day d1 = Day::wed;

    assert(d == d1);

    return 0;
}