#include "business.h"
#include "protocol.h"

#define loglevel "trader/r2r/cdt2hh"
#define logclass "business_t"
#include <us/gov/logs.inc>

using namespace us::trader::r2r::cdt2hh;
using c = us::trader::r2r::cdt2hh::business_t;

c::business_t() {
}

c::~business_t() {
}

bool c::invert(protocol_selection_t& i) const {
    if (i.first != protocol::name) return false;
    if (i.second == "hh") {
        i.second = "cdt";
        return true;
    }
    if (i.second == "cdt") {
        i.second = "hh";
        return true;
    }
    return false;
}


