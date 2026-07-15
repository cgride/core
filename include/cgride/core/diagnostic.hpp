/**
 *
 *  @file diagnostic.hpp
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
#ifndef CGRIDE_CORE_DIAGNOSTIC_HPP
#define CGRIDE_CORE_DIAGNOSTIC_HPP

#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace cgride::core
{
  /**
   * @enum DiagnosticSeverity
   * @brief Severity level of a compiler, linker or engine diagnostic.
   */
  enum class DiagnosticSeverity
  {
    Note,
    Warning,
    Error,
    Fatal
  };

  /**
   * @brief Convert a diagnostic severity to a stable string.
   *
   * @param severity Diagnostic severity.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(DiagnosticSeverity severity) noexcept;

  /**
   * @class Diagnostic
   * @brief Structured diagnostic message emitted by Cgride.
   *
   * Diagnostic is intentionally independent from terminal formatting.
   * A CLI, IDE, runtime or service can decide how to present it.
   */
  class Diagnostic
  {
  public:
    /**
     * @brief Construct an empty note diagnostic.
     */
    Diagnostic() = default;

    /**
     * @brief Construct a diagnostic with severity and message.
     *
     * @param severity Diagnostic severity.
     * @param message Human-readable diagnostic message.
     */
    Diagnostic(DiagnosticSeverity severity, std::string message)
        : severity_(severity),
          message_(std::move(message))
    {
    }

    /**
     * @brief Set the related source file.
     *
     * @param file Source file path.
     * @return Reference to this diagnostic.
     */
    Diagnostic &file(std::filesystem::path file)
    {
      file_ = std::move(file);
      return *this;
    }

    /**
     * @brief Set the related line number.
     *
     * @param value One-based line number.
     * @return Reference to this diagnostic.
     */
    Diagnostic &line(std::size_t value) noexcept
    {
      line_ = value;
      return *this;
    }

    /**
     * @brief Set the related column number.
     *
     * @param value One-based column number.
     * @return Reference to this diagnostic.
     */
    Diagnostic &column(std::size_t value) noexcept
    {
      column_ = value;
      return *this;
    }

    /**
     * @brief Set a compiler-specific diagnostic code.
     *
     * @param value Diagnostic code.
     * @return Reference to this diagnostic.
     */
    Diagnostic &code(std::string value)
    {
      code_ = std::move(value);
      return *this;
    }

    /**
     * @brief Access the severity.
     */
    [[nodiscard]] DiagnosticSeverity severity() const noexcept
    {
      return severity_;
    }

    /**
     * @brief Access the message.
     */
    [[nodiscard]] const std::string &message() const noexcept
    {
      return message_;
    }

    /**
     * @brief Access the optional related file.
     */
    [[nodiscard]] const std::optional<std::filesystem::path> &file() const noexcept
    {
      return file_;
    }

    /**
     * @brief Access the optional line number.
     */
    [[nodiscard]] const std::optional<std::size_t> &line() const noexcept
    {
      return line_;
    }

    /**
     * @brief Access the optional column number.
     */
    [[nodiscard]] const std::optional<std::size_t> &column() const noexcept
    {
      return column_;
    }

    /**
     * @brief Access the optional diagnostic code.
     */
    [[nodiscard]] const std::optional<std::string> &code() const noexcept
    {
      return code_;
    }

    /**
     * @brief Return true if the diagnostic has a non-empty message.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return !message_.empty();
    }

  private:
    DiagnosticSeverity severity_{DiagnosticSeverity::Note};
    std::string message_{};
    std::optional<std::filesystem::path> file_{};
    std::optional<std::size_t> line_{};
    std::optional<std::size_t> column_{};
    std::optional<std::string> code_{};
  };

} // namespace cgride::core

#endif // CGRIDE_CORE_DIAGNOSTIC_HPP
