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

#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

#include <cgride/core/error.hpp>

#define CGRIDE_CHECK(expression) \
  do                             \
  {                              \
    if (!(expression))           \
    {                            \
      std::cerr                  \
          << "CHECK failed: "    \
          << #expression         \
          << '\n'                \
          << "  at "             \
          << __FILE__            \
          << ':'                 \
          << __LINE__            \
          << '\n';               \
      return 1;                  \
    }                            \
  } while (false)

int main()
{
  {
    using cgride::core::ErrorCode;
    using cgride::core::to_string;

    CGRIDE_CHECK(
        to_string(ErrorCode::Unknown) ==
        std::string_view("Unknown"));

    CGRIDE_CHECK(
        to_string(ErrorCode::InvalidArgument) ==
        std::string_view("InvalidArgument"));

    CGRIDE_CHECK(
        to_string(ErrorCode::InvalidState) ==
        std::string_view("InvalidState"));

    CGRIDE_CHECK(
        to_string(ErrorCode::NotFound) ==
        std::string_view("NotFound"));

    CGRIDE_CHECK(
        to_string(ErrorCode::IoError) ==
        std::string_view("IoError"));

    CGRIDE_CHECK(
        to_string(ErrorCode::PermissionDenied) ==
        std::string_view("PermissionDenied"));

    CGRIDE_CHECK(
        to_string(ErrorCode::UnsupportedPlatform) ==
        std::string_view("UnsupportedPlatform"));

    CGRIDE_CHECK(
        to_string(ErrorCode::UnsupportedOperation) ==
        std::string_view("UnsupportedOperation"));

    CGRIDE_CHECK(
        to_string(ErrorCode::ProcessFailed) ==
        std::string_view("ProcessFailed"));

    CGRIDE_CHECK(
        to_string(ErrorCode::Timeout) ==
        std::string_view("Timeout"));

    CGRIDE_CHECK(
        to_string(ErrorCode::Cancelled) ==
        std::string_view("Cancelled"));

    CGRIDE_CHECK(
        to_string(ErrorCode::InternalError) ==
        std::string_view("InternalError"));
  }

  {
    cgride::core::Error error;

    CGRIDE_CHECK(
        error.code() ==
        cgride::core::ErrorCode::Unknown);

    CGRIDE_CHECK(error.message().empty());
    CGRIDE_CHECK(!error.detail().has_value());
    CGRIDE_CHECK(!error.path().has_value());
    CGRIDE_CHECK(!error.valid());
  }

  {
    cgride::core::Error error(
        cgride::core::ErrorCode::InvalidArgument,
        "Invalid argument.");

    CGRIDE_CHECK(
        error.code() ==
        cgride::core::ErrorCode::InvalidArgument);

    CGRIDE_CHECK(error.message() == "Invalid argument.");
    CGRIDE_CHECK(!error.detail().has_value());
    CGRIDE_CHECK(!error.path().has_value());
    CGRIDE_CHECK(error.valid());
  }

  {
    cgride::core::Error error(
        cgride::core::ErrorCode::IoError,
        "Failed to read file.",
        std::string("Permission denied."));

    CGRIDE_CHECK(
        error.code() ==
        cgride::core::ErrorCode::IoError);

    CGRIDE_CHECK(error.message() == "Failed to read file.");
    CGRIDE_CHECK(error.detail().has_value());
    CGRIDE_CHECK(
        error.detail().value() ==
        "Permission denied.");
    CGRIDE_CHECK(!error.path().has_value());
    CGRIDE_CHECK(error.valid());
  }

  {
    const std::filesystem::path path = "src/main.cpp";

    cgride::core::Error error(
        cgride::core::ErrorCode::NotFound,
        "Source file not found.",
        path);

    CGRIDE_CHECK(
        error.code() ==
        cgride::core::ErrorCode::NotFound);

    CGRIDE_CHECK(error.message() == "Source file not found.");
    CGRIDE_CHECK(!error.detail().has_value());
    CGRIDE_CHECK(error.path().has_value());
    CGRIDE_CHECK(error.path().value() == path);
    CGRIDE_CHECK(error.valid());
  }

  {
    const std::filesystem::path path = "build/app";

    cgride::core::Error error(
        cgride::core::ErrorCode::ProcessFailed,
        "Process failed.",
        std::string("Compiler returned a non-zero exit code."),
        path);

    CGRIDE_CHECK(
        error.code() ==
        cgride::core::ErrorCode::ProcessFailed);

    CGRIDE_CHECK(error.message() == "Process failed.");
    CGRIDE_CHECK(error.detail().has_value());

    CGRIDE_CHECK(
        error.detail().value() ==
        "Compiler returned a non-zero exit code.");

    CGRIDE_CHECK(error.path().has_value());
    CGRIDE_CHECK(error.path().value() == path);
    CGRIDE_CHECK(error.valid());
  }

  return 0;
}

#undef CGRIDE_CHECK
