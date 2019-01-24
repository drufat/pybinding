// Copyright (C) 2010-2016 Dzhelil S. Rufat. All Rights Reserved.
#ifndef PYBINDCPP_CAPI_STRINGER_H
#define PYBINDCPP_CAPI_STRINGER_H

#include <sstream>
#include <string>

namespace pybindcpp {

template <typename... Args> std::string stringer(Args const &... args) {
  std::ostringstream stream;
  using List = int[];
  (void)List{0, (stream << args, 0)...};

  return stream.str();
}
} // namespace pybindcpp

#endif // PYBINDCPP_CAPI_STRINGER_H