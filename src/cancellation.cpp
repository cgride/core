/**
 *
 *  @file cancellation.cpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/cgride/cgride
 *
 *  Use of this source code is governed by an MIT license
 *  that can be found in the LICENSE file.
 *
 *  Cgride
 *
 */
#include <cgride/core/cancellation.hpp>

namespace cgride::core
{
  CancellationToken::CancellationToken()
      : state_(std::make_shared<std::atomic_bool>(false))
  {
  }

  CancellationToken::CancellationToken(std::shared_ptr<std::atomic_bool> state)
      : state_(std::move(state))
  {
  }

  bool CancellationToken::cancelled() const noexcept
  {
    return state_ && state_->load(std::memory_order_acquire);
  }

  bool CancellationToken::active() const noexcept
  {
    return !cancelled();
  }

  CancellationSource::CancellationSource()
      : state_(std::make_shared<std::atomic_bool>(false))
  {
  }

  void CancellationSource::cancel() noexcept
  {
    state_->store(true, std::memory_order_release);
  }

  void CancellationSource::reset() noexcept
  {
    state_->store(false, std::memory_order_release);
  }

  bool CancellationSource::cancelled() const noexcept
  {
    return state_->load(std::memory_order_acquire);
  }

  CancellationToken CancellationSource::token() const noexcept
  {
    return CancellationToken(state_);
  }

} // namespace cgride::core
