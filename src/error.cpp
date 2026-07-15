/**
 *
 *  @file error.cpp
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
#include <cgride/core/error.hpp>

namespace cgride::core
{
  std::string_view to_string(ErrorCode code) noexcept
  {
    switch (code)
    {
    case ErrorCode::Unknown:
      return "Unknown";

    case ErrorCode::InvalidArgument:
      return "InvalidArgument";

    case ErrorCode::InvalidState:
      return "InvalidState";

    case ErrorCode::NotFound:
      return "NotFound";

    case ErrorCode::IoError:
      return "IoError";

    case ErrorCode::PermissionDenied:
      return "PermissionDenied";

    case ErrorCode::UnsupportedPlatform:
      return "UnsupportedPlatform";

    case ErrorCode::UnsupportedOperation:
      return "UnsupportedOperation";

    case ErrorCode::ProcessFailed:
      return "ProcessFailed";

    case ErrorCode::Timeout:
      return "Timeout";

    case ErrorCode::Cancelled:
      return "Cancelled";

    case ErrorCode::InternalError:
      return "InternalError";
    }

    return "Unknown";
  }

} // namespace cgride::core
