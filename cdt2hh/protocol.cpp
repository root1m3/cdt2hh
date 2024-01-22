#include "protocol.h"

#define loglevel "trader/r2r/cdt2hh"
#define logclass "protocol"
#include <us/gov/logs.inc>

using namespace us::trader::r2r::cdt2hh;
using c = us::trader::r2r::cdt2hh::protocol;


c::protocol(business_t& bz): b(bz) {
}

c::~protocol() {
}

void job_t::dump(const string& prefix, ostream& os) const {
    os << prefix << "job title: " << title << '\n';
    os << prefix << "company: " << company << '\n';
}

size_t job_t::blob_size() const {
    auto sz =
    blob_writer_t::blob_size(title) +
    blob_writer_t::blob_size(company) +
    blob_writer_t::blob_size(url);
    log("blob_size", sz);
    return sz;
}

void job_t::to_blob(blob_writer_t& writer) const {
    log("to_blob", "cur", (uint64_t)(writer.cur - writer.blob.data()));
    writer.write(title);
    writer.write(company);
    writer.write(url);
}

ko job_t::from_blob(blob_reader_t& reader) {
    log("from_blob", "cur", (uint64_t)(reader.cur - reader.blob.data()));
    {
        auto r = reader.read(title);
        if (is_ko(r)) {
            return r;
        }
    }
    {
        auto r = reader.read(company);
        if (is_ko(r)) {
            return r;
        }
    }
    {
        auto r = reader.read(url);
        if (is_ko(r)) {
            return r;
        }
    }
    return ok;
}

jobs_t::jobs_t() {
}

ko jobs_t::parse(const string& lines) {
    istringstream is(lines);
    while(true) {
        string line;
        job_t job;
        getline(is, job.title);       
        if (is.fail()) break;
        if (job.title.empty()) break;
        getline(is, job.company);       
        getline(is, job.url);       
        push_back(job);
    }
    return ok;
}

void jobs_t::dump(const string& prefix, ostream& os) const {
    int n{0};
    for (auto& i: *this) {
        os << prefix << "Job #" << n++ << '\n';
        auto pfx = prefix + "  ";
        i.dump(pfx, os);
    }
}   

