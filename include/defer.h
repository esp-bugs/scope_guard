#pragma once

#include "scope_guard.h"

#include <utility>


namespace esbg::detail
{
  struct DeferHelper {
    template<typename F>
    auto operator|(F&& fn) const {
      return sg::make_scope_guard(std::forward<F>(fn));
    }
  };
} // namespace esbg::detail

#define ESBG_DEFER__(x) ESBG_DEFER__ ## x
#define ESBG_DEFER_(x) ESBG_DEFER__(x)

#define ESBG_DEFER [[maybe_unused]] const auto ESBG_DEFER_(__COUNTER__) \
  = ::esbg::detail::DeferHelper{} | [&]

#ifndef DEFER
#define DEFER ESBG_DEFER
#endif
