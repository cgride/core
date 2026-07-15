/**
 *
 *  @file error.hpp
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
#ifndef CGRIDE_CORE_ERROR_HPP
#define CGRIDE_CORE_ERROR_HPP

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace cgride::core
{
  /**
   * @enum ErrorCode
   * @brief Stable error categories used by Cgride modules.
   */
  enum class ErrorCode
  {
    Unknown,
    InvalidArgument,
    InvalidState,
    NotFound,
    IoError,
    PermissionDenied,
    UnsupportedPlatform,
    UnsupportedOperation,
    ProcessFailed,
    Timeout,
    Cancelled,
    InternalError
  };

  /**
   * @brief Convert an error code to a stable string.
   *
   * @param code Error code.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(ErrorCode code) noexcept;

  /**
   * @class Error
   * @brief Describes a recoverable Cgride operation failure.
   *
   * Error is used across public APIs instead of terminating the process.
   * It is designed to be explicit, portable and safe for embedding inside
   * another runtime.
   */
  class Error
  {
  public:
    /**
     * @brief Construct an unknown error.
     */
    Error() = default;

    /**
     * @brief Construct an error with a code and message.
     *
     * @param code Stable error category.
     * @param message Human-readable error message.
     */
    Error(ErrorCode code, std::string message)
        : code_(code),
          message_(std::move(message))
    {
    }

    /**
     * @brief Construct an error with a code, message and detail.
     *
     * @param code Stable error category.
     * @param message Human-readable error message.
     * @param detail Additional context.
     */
    Error(ErrorCode code, std::string message, std::string detail)
        : code_(code),
          message_(std::move(message)),
          detail_(std::move(detail))
    {
    }

    /**
     * @brief Construct an error with a code, message and related path.
     *
     * @param code Stable error category.
     * @param message Human-readable error message.
     * @param path Related filesystem path.
     */
    Error(ErrorCode code, std::string message, std::filesystem::path path)
        : code_(code),
          message_(std::move(message)),
          path_(std::move(path))
    {
    }

    /**
     * @brief Construct an error with all supported fields.
     *
     * @param code Stable error category.
     * @param message Human-readable error message.
     * @param detail Additional context.
     * @param path Related filesystem path.
     */
    Error(ErrorCode code,
          std::string message,
          std::string detail,
          std::filesystem::path path)
        : code_(code),
          message_(std::move(message)),
          detail_(std::move(detail)),
          path_(std::move(path))
    {
    }

    /**
     * @brief Access the stable error category.
     */
    [[nodiscard]] ErrorCode code() const noexcept
    {
      return code_;
    }

    /**
     * @brief Access the human-readable message.
     */
    [[nodiscard]] const std::string &message() const noexcept
    {
      return message_;
    }

    /**
     * @brief Access optional additional context.
     */
    [[nodiscard]] const std::optional<std::string> &detail() const noexcept
    {
      return detail_;
    }

    /**
     * @brief Access optional related filesystem path.
     */
    [[nodiscard]] const std::optional<std::filesystem::path> &path() const noexcept
    {
      return path_;
    }

    /**
     * @brief Return true if the error has a non-empty message.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return !message_.empty();
    }

  private:
    ErrorCode code_{ErrorCode::Unknown};
    std::string message_{};
    std::optional<std::string> detail_{};
    std::optional<std::filesystem::path> path_{};
  };

} // namespace cgride::core

#endif // CGRIDE_CORE_ERROR_HPP
