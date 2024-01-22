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
#include <us/wallet/trader/trader_t.h>
#include <us/wallet/trader/business.h>
#include <us/wallet/trader/params_t.h>
#include <us/trader/r2r/cdt2hh/protocol.h>
#include <us/trader/r2r/cdt2hh/types.h>

namespace us::trader::r2r::cdt2hh::hh {

    struct business_t;

    struct protocol: cdt2hh::protocol {
        using b = cdt2hh::protocol;
        using business_t = us::trader::r2r::cdt2hh::hh::business_t;

    public:
        protocol(business_t&);
        ~protocol() override;

    public:
        size_t blob_size() const override;
        void to_blob(blob_writer_t&) const override;
        ko from_blob(blob_reader_t&) override;
        factory_id_t factory_id() const override;

    public:
        void dump(ostream&) const override;
        void list_trades_bit(ostream&) const override;
        const char* rolestr() const override;
        const char* peer_rolestr() const override;
        const char* get_name() const override;
        chat_t::entry AI_chat(const chat_t&, peer_t&) override;
        ko on_remote_(params_t*, ch_t&) override;
        uint32_t trade_state_() const;
        void judge(const string& lang) override;
        void on_file_updated(const string& path, const string& name, ch_t&) override;

    public:
        ko trading_msg(peer_t&, svc_t, blob_t&&) override;
        bool requires_online(const string& cmd) const override;
        void help_online(const string& indent, ostream&) const override;
        ko exec_online(peer_t&, const string& cmd, ch_t&) override;

    private:
        ko send_jobs(peer_t&, ch_t&);
        ko invoke_api(jobs_t&, ch_t&);

    };

}


