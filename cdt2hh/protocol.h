#pragma once
#include <string>

#include <us/gov/io/seriable.h>
#include <us/gov/io/seriable_vector.h>

#include <us/wallet/trader/trader_t.h>
#include <us/wallet/wallet/local_api.h>
#include <us/wallet/trader/chat_t.h>

#include "types.h"

namespace us::trader::r2r::cdt2hh {


    struct job_t: us::gov::io::seriable {

        size_t blob_size() const override;
        void to_blob(blob_writer_t&) const override;
        ko from_blob(blob_reader_t&) override;

        void dump(const string& prefix, ostream&) const;

        string title;
        string company;
        string url;
    };

    struct jobs_t: us::gov::io::seriable_vector<job_t> {
        jobs_t();
        ko parse(const string&);
        void dump(const string& prefix, ostream&) const;
    };



    struct protocol: us::wallet::trader::trader_protocol {
        using b = us::wallet::trader::trader_protocol;
        using business_t = us::wallet::trader::business_t;

        static constexpr const char* name{"cdt2hh"};

    public:
        protocol(business_t&);
        ~protocol() override;

    public:
        enum push_code_t { //communications node-HMI
            push_begin = trader_protocol::push_r2r_begin,
            push_jobs,
            push_end
        };

        enum service_t { //communications node-node
            svc_begin = trader_protocol::svc_r2r_begin,
            svc_jobs_req,
            svc_jobs,
            svc_end
        };
    };

}


