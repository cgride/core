/**
 *
 *  @file cancellation.hpp
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
#ifndef CGRIDE_CORE_CANCELLATION_HPP
#define CGRIDE_CORE_CANCELLATION_HPP

#include <atomic>
#include <memory>

namespace cgride::core
{
  /**
   * @class CancellationToken
   * @brief Read-only cancellation handle shared with long-running operations.
   *
   * CancellationToken allows Cgride modules to check whether an operation
   * should stop without depending on a specific scheduler, CLI or runtime.
   */
  class CancellationToken
  {
  public:
    /**
     * @brief Construct a token with its own internal state.
     */
    CancellationToken();

    /**
     * @brief Return true if cancellation was requested.
     */
    [[nodiscard]] bool cancelled() const noexcept;

    /**
     * @brief Return true if cancellation was not requested.
     */
    [[nodiscard]] bool active() const noexcept;

  private:
    friend class CancellationSource;

    explicit CancellationToken(std::shared_ptr<std::atomic_bool> state);

    std::shared_ptr<std::atomic_bool> state_{};
  };

  /**
   * @class CancellationSource
   * @brief Mutable cancellation owner.
   *
   * CancellationSource creates tokens and can request cancellation.
   * The source is usually owned by the caller, while tokens are passed to
   * planners, executors and process runners.
   */
  class CancellationSource
  {
  public:
    /**
     * @brief Construct a cancellation source.
     */
    CancellationSource();

    /**
     * @brief Request cancellation.
     */
    void cancel() noexcept;

    /**
     * @brief Reset the source to the active state.
     */
    void reset() noexcept;

    /**
     * @brief Return true if cancellation was requested.
     */
    [[nodiscard]] bool cancelled() const noexcept;

    /**
     * @brief Return a token connected to this source.
     */
    [[nodiscard]] CancellationToken token() const noexcept;

  private:
    std::shared_ptr<std::atomic_bool> state_{};
  };

} // namespace cgride::core

#endif // CGRIDE_CORE_CANCELLATION_HPP
