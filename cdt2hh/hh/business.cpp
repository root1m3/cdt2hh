#include "business.h"
#include <fstream>

#include <us/gov/io/shell_args.h>
#include <us/gov/io/cfg0.h>

#define loglevel "us::trader::r2r::cdt2hh/hh"
#define logclass "business_t"
#include <us/gov/logs.inc>

using namespace us::trader::r2r::cdt2hh;
using c = us::trader::r2r::cdt2hh::hh::business_t;

c::business_t() {
    name = "hh (cdt2hh)";
}

c::~business_t() {
    log("destroyed cdt2hh hh", home);
}

ko c::init(const string& r2rhome, protocol_factories_t& f) {
    auto r = b::init(r2rhome, f);
    if (is_ko(r)) {
        return r;
    }
    log("cdt2hh hh init. homebase", home);
    assert(!home.empty());
    log("cdt2hh hh initiated @", home);
    return ok;
}

c::protocol_factory_id_t c::protocol_factory_id() const {
    return protocol_factory_id_t(c::protocol::name, "hh");
}

void c::register_factories(protocol_factories_t& protocol_factories) {
    struct my_protocol_factory_t: protocol_factory_t {

        my_protocol_factory_t(c* bz): bz(bz) {}

        pair<ko, value_type*> create() override {
            auto a = new business_t::protocol(*bz);
            log("created protocol", protocol::name, "instance at", a);
            return make_pair(ok, a);
        }

        c* bz;
    };
    protocol_factories.register_factory(protocol_factory_id(), new my_protocol_factory_t(this));
    assert(protocol_factories.find(protocol_factory_id()) != protocol_factories.end());
}

string c::homedir() const {
    ostringstream os;
    os << r2rhome << '/' << protocol::name << "/hh";
    log("homedir", os.str());
    return os.str();
}

pair<us::ko, us::wallet::trader::trader_protocol*> c::create_protocol() {
    auto a = new c::protocol(*this);
    log("protocol instance at", a, 3);
    return make_pair(ok, a);
}

void c::list_protocols(ostream& os) const {
    os << c::protocol::name << " hh\n";
}

void c::published_protocols(protocols_t& protocols, bool inverse) const {
    protocols.emplace_back(c::protocol::name, inverse ? "cdt" : "hh");
}


