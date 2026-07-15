/**
 *
 *  @file error_test.cpp
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
#include <cassert>
#include <filesystem>
#include <string_view>
#include <string>

#include <cgride/core/error.hpp>

int main()
{
  {
    using cgride::core::ErrorCode;
    using cgride::core::to_string;

    assert(to_string(ErrorCode::Unknown) == std::string_view("Unknown"));
    assert(to_string(ErrorCode::InvalidArgument) == std::string_view("InvalidArgument"));
    assert(to_string(ErrorCode::InvalidState) == std::string_view("InvalidState"));
    assert(to_string(ErrorCode::NotFound) == std::string_view("NotFound"));
    assert(to_string(ErrorCode::IoError) == std::string_view("IoError"));
    assert(to_string(ErrorCode::PermissionDenied) == std::string_view("PermissionDenied"));
    assert(to_string(ErrorCode::UnsupportedPlatform) == std::string_view("UnsupportedPlatform"));
    assert(to_string(ErrorCode::UnsupportedOperation) == std::string_view("UnsupportedOperation"));
    assert(to_string(ErrorCode::ProcessFailed) == std::string_view("ProcessFailed"));
    assert(to_string(ErrorCode::Timeout) == std::string_view("Timeout"));
    assert(to_string(ErrorCode::Cancelled) == std::string_view("Cancelled"));
    assert(to_string(ErrorCode::InternalError) == std::string_view("InternalError"));
  }

  {
    cgride::core::Error error;

    assert(error.code() == cgride::core::ErrorCode::Unknown);
    assert(error.message().empty());
    assert(!error.detail().has_value());
    assert(!error.path().has_value());
    assert(!error.valid());
  }

  {
    cgride::core::Error error(
        cgride::core::ErrorCode::InvalidArgument,
        "Invalid argument.");

    assert(error.code() == cgride::core::ErrorCode::InvalidArgument);
    assert(error.message() == "Invalid argument.");
    assert(!error.detail().has_value());
    assert(!error.path().has_value());
    assert(error.valid());
  }

  {
    cgride::core::Error error(
        cgride::core::ErrorCode::IoError,
        "Failed to read file.",
        std::string("Permission denied."));

    assert(error.code() == cgride::core::ErrorCode::IoError);
    assert(error.message() == "Failed to read file.");
    assert(error.detail().has_value());
    assert(error.detail().value() == "Permission denied.");
    assert(!error.path().has_value());
    assert(error.valid());
  }

  {
    const std::filesystem::path path = "src/main.cpp";

    cgride::core::Error error(
        cgride::core::ErrorCode::NotFound,
        "Source file not found.",
        path);

    assert(error.code() == cgride::core::ErrorCode::NotFound);
    assert(error.message() == "Source file not found.");
    assert(!error.detail().has_value());
    assert(error.path().has_value());
    assert(error.path().value() == path);
    assert(error.valid());
  }

  {
    const std::filesystem::path path = "build/app";

    cgride::core::Error error(
        cgride::core::ErrorCode::ProcessFailed,
        "Process failed.",
        std::string("Compiler returned a non-zero exit code."),
        path);

    assert(error.code() == cgride::core::ErrorCode::ProcessFailed);
    assert(error.message() == "Process failed.");
    assert(error.detail().has_value());
    assert(error.detail().value() == "Compiler returned a non-zero exit code.");
    assert(error.path().has_value());
    assert(error.path().value() == path);
    assert(error.valid());
  }

  return 0;
}
