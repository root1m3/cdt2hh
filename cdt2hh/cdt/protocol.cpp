#include "protocol.h"
#include <fstream>
#include <unordered_map>

#include <us/gov/socket/datagram.h>
#include <us/gov/io/shell_args.h>
#include <us/gov/io/cfg0.h>

#include "business.h"

#define loglevel "trader/r2r/cdt2hh/cdt"
#define logclass "protocol"
#include <us/gov/logs.inc>

using namespace us::trader::r2r::cdt2hh::cdt;
using c = us::trader::r2r::cdt2hh::cdt::protocol;
using us::ko;

const char* c::rolestr() const { return "cdt"; }
const char* c::peer_rolestr() const { return "hh"; }
const char* c::get_name() const { return name; };

c::protocol(business_t& bz): b(bz) {
    log("created protocol_cdt2hh_cdt");
}

c::~protocol() {
    log("destroyed protocol_cdt2hh_cdt");
}

ko c::on_remote_(params_t* rp, ch_t& ch) {
    log("on_remote_params");
    auto r = b::on_remote_(rp, ch);
    if (is_ko(r)) {
        return r;
    }
    log("on_remote_params. returned", ch.to_string());
    return ok;
}

void c::on_file_updated(const string& path, const string& name, ch_t& ch) {
    log("on_file_updated", name);
    b::on_file_updated(path, name, ch);
}

void c::dump(ostream& os) const {
    os << "cdt";
}

void c::list_trades_bit(ostream& os) const { //protocol role
    os << "cdt2hh cdt" << ' ';
}

namespace { namespace i18n {

    using namespace std;

    struct r_en_t;
    struct r_es_t;

    struct r_t: unordered_map<uint32_t, const char*> {
        using b =  unordered_map<uint32_t, const char*>;

        using b::unordered_map;

        const char* resolve(uint32_t n) const {
            log("string-res. resolve", n);
            auto i = find(n);
            if (i == end()) return begin()->second;
            return i->second;
        }

        static r_t& resolver(const string& lang);
    };

    struct r_en_t: r_t {
        using b = r_t;

        r_en_t(): b({
            {0, "KO 30920 Use i18n package in Lower Layer."},
            {1, ""}, {2, ""},

        }) {
            //log("constructor 'en' string resources with", size(), "entries. Entry #4 is", resolve(4));
        }

    };

    struct r_es_t: r_t {
        using b = r_t;

        r_es_t(): b({
            {0, "KO 30920"},
            {1, ""}, {2, ""},
        }) {
            //log("constructor 'es' string resources with", size(), "entries. Entry #4 is", resolve(4));
        }

    };

    r_en_t r_en;
    r_es_t r_es;

    r_t& r_t::resolver(const string& lang) {
        if (lang == "es") return r_es;
        return r_en;
    }

}}

uint32_t c::trade_state_() const {
    log("trade_state_");
    return 1;
}

void c::judge(const string& lang) {
    auto st = trade_state_();
    if (st != _trade_state.first) {
        if (st == 0) {
            b::judge(lang);
            return;
        }
        auto t = i18n::r_t::resolver(lang);
        auto r = t.resolve(st);
        log("trade_state", st, r);
        _trade_state = make_pair(st, r);
        _user_hint = t.resolve(_trade_state.first + 1);
    }
}

c::chat_t::entry c::AI_chat(const chat_t& chat, peer_t&) {
    chat_t::entry response;
    if (chat.empty_me_()) {
        using us::wallet::trader::paragraphs;
        using us::wallet::trader::paragraph;
        response.emplace_back("Hi from our company!.");
    }
    return response;
}

size_t c::blob_size() const {
    size_t sz = b::blob_size();
    return sz;
}

void c::to_blob(blob_writer_t& writer) const {
    b::to_blob(writer);
}

c::factory_id_t c::factory_id() const {
    return protocol_selection_t("cdt2hh", "cdt");
}

ko c::from_blob(blob_reader_t& reader) {
    {
        auto r = b::from_blob(reader);
        if (is_ko(r)) {
            return r;
        }
    }
    return ok;
}

bool c::requires_online(const string& cmd) const {
    if (b::requires_online(cmd)) return true;
    if (cmd == "request_jobs") return true;
    return false;
}

void c::help_online(const string& indent, ostream& os) const {
    b::help_online(indent, os);
    twocol(indent, "request_jobs", "request peer to send jobs feed.", os);
}

ko c::exec_online(peer_t& peer, const string& cmd0, ch_t& ch) {
    assert(!ch.closed());
    {
        auto r = b::exec_online(peer, cmd0, ch);
        if (r != WP_29101) {
            return move(r);
        }
    }
    string cmd;
    istringstream is(cmd0);
    is >> cmd;
    if (cmd == "request_jobs") {
        return tder->call_trading_msg(peer, svc_jobs_req, blob_t());
    }
    auto r = WP_29101;
    log(r);
    return move(r);
}

us::gov::io::blob_t c::push_payload(uint16_t pc) const {
    if (pc < push_begin) {
        return b::push_payload(pc);
    }
    assert(pc < push_end);
    blob_t blob;
    switch(pc) {
        case push_jobs: {
            log("pushing catalogue");
            jobs.write(blob);
        }
        break;
    }
    return move(blob);
}

ko c::trading_msg(peer_t& peer, svc_t svc, blob_t&& blob) {
    static_assert((int)svc_begin >= (int)trader_protocol::svc_end);
    if (svc < cdt2hh::protocol::svc_begin) {
        return b::trading_msg(peer, svc, move(blob));
    }
    log("trading_msg", svc);
    assert(svc < cdt2hh::protocol::svc_end);
    switch(svc) {
        case svc_jobs: {
            log("received ico image", blob.size(), "bytes");
            jobs.clear();
            blob_reader_t reader(blob);
            auto r = reader.read(jobs);
            if (is_ko(r)) {
                return r;
            }
            schedule_push(cdt2hh::protocol::push_jobs);
            return ok;
        }
    }
    return KO_29100;
}

