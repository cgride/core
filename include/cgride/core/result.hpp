/**
 *
 *  @file result.hpp
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
#ifndef CGRIDE_CORE_RESULT_HPP
#define CGRIDE_CORE_RESULT_HPP

#include <utility>
#include <variant>

#include <cgride/core/error.hpp>

namespace cgride::core
{
  /**
   * @class Result
   * @brief Represents either a successful value or a structured error.
   *
   * Result is used by Cgride public APIs to report expected failures without
   * terminating the host process.
   *
   * Design goals:
   * - explicit success and failure states
   * - no hidden process termination
   * - suitable for embedded runtimes
   * - lightweight and dependency-free
   *
   * @tparam T Successful value type.
   */
  template <typename T>
  class Result
  {
  public:
    /**
     * @brief Construct a successful result.
     *
     * @param value Successful value.
     */
    Result(T value)
        : storage_(std::move(value))
    {
    }

    /**
     * @brief Construct a failed result.
     *
     * @param error Structured error.
     */
    Result(Error error)
        : storage_(std::move(error))
    {
    }

    /**
     * @brief Create a successful result.
     *
     * @param value Successful value.
     * @return Successful result.
     */
    [[nodiscard]] static Result ok(T value)
    {
      return Result(std::move(value));
    }

    /**
     * @brief Create a failed result.
     *
     * @param error Structured error.
     * @return Failed result.
     */
    [[nodiscard]] static Result fail(Error error)
    {
      return Result(std::move(error));
    }

    /**
     * @brief Return true when the result contains a value.
     */
    [[nodiscard]] bool has_value() const noexcept
    {
      return std::holds_alternative<T>(storage_);
    }

    /**
     * @brief Return true when the result contains an error.
     */
    [[nodiscard]] bool has_error() const noexcept
    {
      return std::holds_alternative<Error>(storage_);
    }

    /**
     * @brief Return true when the result contains a value.
     */
    [[nodiscard]] explicit operator bool() const noexcept
    {
      return has_value();
    }

    /**
     * @brief Access the successful value.
     *
     * The caller must check has_value() before calling this function.
     */
    [[nodiscard]] T &value() noexcept
    {
      return std::get<T>(storage_);
    }

    /**
     * @brief Access the successful value.
     *
     * The caller must check has_value() before calling this function.
     */
    [[nodiscard]] const T &value() const noexcept
    {
      return std::get<T>(storage_);
    }

    /**
     * @brief Access the structured error.
     *
     * The caller must check has_error() before calling this function.
     */
    [[nodiscard]] Error &error() noexcept
    {
      return std::get<Error>(storage_);
    }

    /**
     * @brief Access the structured error.
     *
     * The caller must check has_error() before calling this function.
     */
    [[nodiscard]] const Error &error() const noexcept
    {
      return std::get<Error>(storage_);
    }

  private:
    std::variant<T, Error> storage_;
  };

  /**
   * @class Result<void>
   * @brief Represents success without a value or a structured error.
   */
  template <>
  class Result<void>
  {
  public:
    /**
     * @brief Construct a successful result.
     */
    Result() = default;

    /**
     * @brief Construct a failed result.
     *
     * @param error Structured error.
     */
    Result(Error error)
        : success_(false),
          error_(std::move(error))
    {
    }

    /**
     * @brief Create a successful result.
     *
     * @return Successful result.
     */
    [[nodiscard]] static Result ok()
    {
      return Result();
    }

    /**
     * @brief Create a failed result.
     *
     * @param error Structured error.
     * @return Failed result.
     */
    [[nodiscard]] static Result fail(Error error)
    {
      return Result(std::move(error));
    }

    /**
     * @brief Return true when the operation succeeded.
     */
    [[nodiscard]] bool has_value() const noexcept
    {
      return success_;
    }

    /**
     * @brief Return true when the operation failed.
     */
    [[nodiscard]] bool has_error() const noexcept
    {
      return !success_;
    }

    /**
     * @brief Return true when the operation succeeded.
     */
    [[nodiscard]] explicit operator bool() const noexcept
    {
      return success_;
    }

    /**
     * @brief Access the structured error.
     *
     * The caller must check has_error() before calling this function.
     */
    [[nodiscard]] Error &error() noexcept
    {
      return error_;
    }

    /**
     * @brief Access the structured error.
     *
     * The caller must check has_error() before calling this function.
     */
    [[nodiscard]] const Error &error() const noexcept
    {
      return error_;
    }

  private:
    bool success_{true};
    Error error_{};
  };

} // namespace cgride::core

#endif // CGRIDE_CORE_RESULT_HPP
