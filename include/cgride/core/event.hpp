/**
 *
 *  @file event.hpp
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
#ifndef CGRIDE_CORE_EVENT_HPP
#define CGRIDE_CORE_EVENT_HPP

#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include <cgride/core/diagnostic.hpp>

namespace cgride::core
{
  /**
   * @enum EventKind
   * @brief Type of structured event emitted by Cgride.
   */
  enum class EventKind
  {
    BuildStarted,
    BuildFinished,
    TaskStarted,
    TaskFinished,
    TaskSkipped,
    CacheHit,
    CacheMiss,
    DiagnosticReceived,
    ProcessOutput,
    Message
  };

  /**
   * @enum OutputStream
   * @brief Output stream associated with process output events.
   */
  enum class OutputStream
  {
    Stdout,
    Stderr
  };

  /**
   * @brief Convert an event kind to a stable string.
   *
   * @param kind Event kind.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(EventKind kind) noexcept;

  /**
   * @brief Convert an output stream to a stable string.
   *
   * @param stream Output stream.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(OutputStream stream) noexcept;

  /**
   * @class Event
   * @brief Structured runtime event emitted by Cgride.
   *
   * Event is independent from terminal formatting. A CLI, IDE, runtime or
   * service can decide how to present it.
   */
  class Event
  {
  public:
    /**
     * @brief Construct a message event.
     */
    Event() = default;

    /**
     * @brief Construct an event with a kind.
     *
     * @param kind Event kind.
     */
    explicit Event(EventKind kind);

    /**
     * @brief Construct an event with a kind and message.
     *
     * @param kind Event kind.
     * @param message Human-readable message.
     */
    Event(EventKind kind, std::string message);

    /**
     * @brief Set the target name associated with the event.
     *
     * @param value Target name.
     * @return Reference to this event.
     */
    Event &target(std::string value);

    /**
     * @brief Set the task identifier associated with the event.
     *
     * @param value Task identifier.
     * @return Reference to this event.
     */
    Event &task_id(std::string value);

    /**
     * @brief Set the process output stream associated with the event.
     *
     * @param value Output stream.
     * @return Reference to this event.
     */
    Event &stream(OutputStream value) noexcept;

    /**
     * @brief Attach a structured diagnostic to the event.
     *
     * @param value Diagnostic value.
     * @return Reference to this event.
     */
    Event &diagnostic(Diagnostic value);

    /**
     * @brief Access the event kind.
     */
    [[nodiscard]] EventKind kind() const noexcept;

    /**
     * @brief Access the event message.
     */
    [[nodiscard]] const std::string &message() const noexcept;

    /**
     * @brief Access the optional target name.
     */
    [[nodiscard]] const std::optional<std::string> &target() const noexcept;

    /**
     * @brief Access the optional task identifier.
     */
    [[nodiscard]] const std::optional<std::string> &task_id() const noexcept;

    /**
     * @brief Access the optional output stream.
     */
    [[nodiscard]] const std::optional<OutputStream> &stream() const noexcept;

    /**
     * @brief Access the optional diagnostic.
     */
    [[nodiscard]] const std::optional<Diagnostic> &diagnostic() const noexcept;

    /**
     * @brief Access the event creation time.
     */
    [[nodiscard]] std::chrono::system_clock::time_point timestamp() const noexcept;

  private:
    EventKind kind_{EventKind::Message};
    std::string message_{};
    std::optional<std::string> target_{};
    std::optional<std::string> task_id_{};
    std::optional<OutputStream> stream_{};
    std::optional<Diagnostic> diagnostic_{};
    std::chrono::system_clock::time_point timestamp_{std::chrono::system_clock::now()};
  };

} // namespace cgride::core

#endif // CGRIDE_CORE_EVENT_HPP
