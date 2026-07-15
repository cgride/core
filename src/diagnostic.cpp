/**
 *
 *  @file diagnostic.cpp
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
#include <cgride/core/diagnostic.hpp>

namespace cgride::core
{
  std::string_view to_string(DiagnosticSeverity severity) noexcept
  {
    switch (severity)
    {
    case DiagnosticSeverity::Note:
      return "Note";

    case DiagnosticSeverity::Warning:
      return "Warning";

    case DiagnosticSeverity::Error:
      return "Error";

    case DiagnosticSeverity::Fatal:
      return "Fatal";
    }

    return "Note";
  }

} // namespace cgride::core
