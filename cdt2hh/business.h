#pragma once
#include <string>

#include <us/gov/io/factory.h>
#include <us/wallet/trader/ch_t.h>
#include <us/wallet/trader/business.h>
#include <us/wallet/trader/protocol_selection_t.h>
#include <us/wallet/wallet/local_api.h>

#include "types.h"

#include "protocol.h"

namespace us::trader::r2r::cdt2hh {

    struct business_t: us::wallet::trader::business_t {
        using b = us::wallet::trader::business_t;
        using ch_t = us::wallet::trader::ch_t;

    public:
        business_t();
        ~business_t() override;

    public:

        bool invert(protocol_selection_t&) const override;

    };

}

