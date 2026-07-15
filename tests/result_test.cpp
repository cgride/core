/**
 *
 *  @file result_test.cpp
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
#include <string>

#include <cgride/core/result.hpp>

int main()
{
  {
    auto result = cgride::core::Result<int>::ok(42);

    assert(result);
    assert(result.has_value());
    assert(!result.has_error());
    assert(result.value() == 42);
  }

  {
    auto result = cgride::core::Result<std::string>::ok("cgride");

    assert(result);
    assert(result.has_value());
    assert(result.value() == "cgride");
  }

  {
    auto result = cgride::core::Result<int>::fail(
        cgride::core::Error(
            cgride::core::ErrorCode::InvalidArgument,
            "Invalid value."));

    assert(!result);
    assert(!result.has_value());
    assert(result.has_error());
    assert(result.error().code() == cgride::core::ErrorCode::InvalidArgument);
    assert(result.error().message() == "Invalid value.");
  }

  {
    auto result = cgride::core::Result<void>::ok();

    assert(result);
    assert(result.has_value());
    assert(!result.has_error());
  }

  {
    auto result = cgride::core::Result<void>::fail(
        cgride::core::Error(
            cgride::core::ErrorCode::Cancelled,
            "Operation cancelled."));

    assert(!result);
    assert(!result.has_value());
    assert(result.has_error());
    assert(result.error().code() == cgride::core::ErrorCode::Cancelled);
    assert(result.error().message() == "Operation cancelled.");
  }

  return 0;
}
