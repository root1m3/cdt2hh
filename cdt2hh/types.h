#pragma once
#ifdef DEBUG
   #include <type_traits>
   struct assert_is_root_namespace;
   static_assert(std::is_same<assert_is_root_namespace, ::assert_is_root_namespace>::value, "Not root namespace. Check includes.");
#endif
#include <us/gov/types.h>
#include <us/gov/ko.h>
#include <us/gov/crypto/types.h>
#include <us/gov/io/types.h>

namespace us {

}

namespace us::trader::r2r::cdt2hh {

    using namespace us;
    using namespace us::gov;

}


