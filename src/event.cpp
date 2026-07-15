/**
 *
 *  @file event.cpp
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
#include <cgride/core/event.hpp>

namespace cgride::core
{
  std::string_view to_string(EventKind kind) noexcept
  {
    switch (kind)
    {
    case EventKind::BuildStarted:
      return "BuildStarted";

    case EventKind::BuildFinished:
      return "BuildFinished";

    case EventKind::TaskStarted:
      return "TaskStarted";

    case EventKind::TaskFinished:
      return "TaskFinished";

    case EventKind::TaskSkipped:
      return "TaskSkipped";

    case EventKind::CacheHit:
      return "CacheHit";

    case EventKind::CacheMiss:
      return "CacheMiss";

    case EventKind::DiagnosticReceived:
      return "DiagnosticReceived";

    case EventKind::ProcessOutput:
      return "ProcessOutput";

    case EventKind::Message:
      return "Message";
    }

    return "Message";
  }

  std::string_view to_string(OutputStream stream) noexcept
  {
    switch (stream)
    {
    case OutputStream::Stdout:
      return "Stdout";

    case OutputStream::Stderr:
      return "Stderr";
    }

    return "Stdout";
  }

  Event::Event(EventKind kind)
      : kind_(kind)
  {
  }

  Event::Event(EventKind kind, std::string message)
      : kind_(kind),
        message_(std::move(message))
  {
  }

  Event &Event::target(std::string value)
  {
    target_ = std::move(value);
    return *this;
  }

  Event &Event::task_id(std::string value)
  {
    task_id_ = std::move(value);
    return *this;
  }

  Event &Event::stream(OutputStream value) noexcept
  {
    stream_ = value;
    return *this;
  }

  Event &Event::diagnostic(Diagnostic value)
  {
    diagnostic_ = std::move(value);
    return *this;
  }

  EventKind Event::kind() const noexcept
  {
    return kind_;
  }

  const std::string &Event::message() const noexcept
  {
    return message_;
  }

  const std::optional<std::string> &Event::target() const noexcept
  {
    return target_;
  }

  const std::optional<std::string> &Event::task_id() const noexcept
  {
    return task_id_;
  }

  const std::optional<OutputStream> &Event::stream() const noexcept
  {
    return stream_;
  }

  const std::optional<Diagnostic> &Event::diagnostic() const noexcept
  {
    return diagnostic_;
  }

  std::chrono::system_clock::time_point Event::timestamp() const noexcept
  {
    return timestamp_;
  }

} // namespace cgride::core
