/**
 *
 *  @file path_test.cpp
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
#include <fstream>
#include <string_view>

#include <cgride/core/path.hpp>

int main()
{
  {
    using cgride::core::PathKind;
    using cgride::core::to_string;

    assert(to_string(PathKind::Missing) == std::string_view("Missing"));
    assert(to_string(PathKind::File) == std::string_view("File"));
    assert(to_string(PathKind::Directory) == std::string_view("Directory"));
    assert(to_string(PathKind::Symlink) == std::string_view("Symlink"));
    assert(to_string(PathKind::Other) == std::string_view("Other"));
  }

  {
    const auto path = cgride::core::normalize_path("a/b/../c/./file.cpp");

    assert(path.generic_string() == "a/c/file.cpp");
  }

  {
    const auto path = cgride::core::join_path("a/b", "../c/file.cpp");

    assert(path.generic_string() == "a/c/file.cpp");
  }

  {
    auto result = cgride::core::absolute_path(".");

    assert(result);
    assert(result.value().is_absolute());
  }

  {
    auto result = cgride::core::absolute_path("base", "child/file.cpp");

    assert(result);
    assert(result.value().is_absolute());
    assert(result.value().generic_string().find("base/child/file.cpp") != std::string::npos);
  }

  {
    const auto root = std::filesystem::temp_directory_path() / "cgride_core_path_test";
    const auto nested = root / "a" / "b" / "c";
    const auto file = nested / "main.cpp";

    std::filesystem::remove_all(root);

    auto directory_result = cgride::core::ensure_directory(nested);

    assert(directory_result);
    assert(cgride::core::path_exists(nested));
    assert(cgride::core::is_directory_path(nested));
    assert(cgride::core::path_kind(nested) == cgride::core::PathKind::Directory);

    {
      std::ofstream output(file);
      output << "int main() { return 0; }\n";
    }

    assert(cgride::core::path_exists(file));
    assert(cgride::core::is_regular_file_path(file));
    assert(cgride::core::path_kind(file) == cgride::core::PathKind::File);

    auto relative = cgride::core::relative_path(root, file);

    assert(relative);
    assert(relative.value().generic_string() == "a/b/c/main.cpp");

    std::filesystem::remove_all(root);
  }

  {
    const auto root = std::filesystem::temp_directory_path() / "cgride_core_path_conflict_test";
    const auto file = root / "entry";

    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root);

    {
      std::ofstream output(file);
      output << "file\n";
    }

    auto result = cgride::core::ensure_directory(file);

    assert(!result);
    assert(result.error().code() == cgride::core::ErrorCode::InvalidState);

    std::filesystem::remove_all(root);
  }

  {
    const std::filesystem::path path = "a/b/c.cpp";

    assert(cgride::core::portable_path_string(path) == "a/b/c.cpp");
    assert(!cgride::core::native_path_string(path).empty());
  }

  return 0;
}
