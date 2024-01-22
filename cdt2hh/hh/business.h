#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <sstream>
#include <mutex>
#include <chrono>
#include <vector>
#include <fstream>

#include <us/gov/engine/signed_data.h>
#include <us/gov/socket/datagram.h>
#include <us/trader/r2r/cdt2hh/business.h>
#include <us/wallet/trader/trader_t.h>

#include "protocol.h"

namespace us::trader::r2r::cdt2hh::hh {

    struct business_t: us::trader::r2r::cdt2hh::business_t {
        using b = us::trader::r2r::cdt2hh::business_t;
        using hash_t = us::gov::crypto::ripemd160::value_type;
        using datagram = us::gov::socket::datagram;
        using protocol = us::trader::r2r::cdt2hh::hh::protocol;

    public:
        business_t();
        ~business_t() override;

    public:
        protocol_factory_id_t protocol_factory_id() const;
        void register_factories(protocol_factories_t&) override;

    public:
        ko init(const string& r2rhome, protocol_factories_t&) override;
        string homedir() const override;

        pair<ko, trader_protocol*> create_protocol() override;
        void list_protocols(ostream&) const override; //human format
        void published_protocols(protocols_t&, bool inverse) const override; //serialization format

    };

}


