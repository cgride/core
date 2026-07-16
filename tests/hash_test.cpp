/**
 *
 *  @file hash_test.cpp
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
#include <string>

#include <cgride/core/hash.hpp>

int main()
{
  {
    assert(cgride::core::hash_string("") == cgride::core::fnv1a_offset_basis);
    assert(cgride::core::hash_to_hex(cgride::core::fnv1a_offset_basis) == "cbf29ce484222325");
  }

  {
    const auto value = cgride::core::hash_string("hello");
    (void)value;

    assert(value == 0xa430d84680aabd0bULL);
    assert(cgride::core::hash_to_hex(value) == "a430d84680aabd0b");
  }

  {
    cgride::core::Hasher hasher;

    hasher.update("hello");

    assert(hasher.value() == cgride::core::hash_string("hello"));
    assert(hasher.hex() == "a430d84680aabd0b");

    hasher.reset();

    assert(hasher.value() == cgride::core::fnv1a_offset_basis);
    assert(hasher.hex() == "cbf29ce484222325");
  }

  {
    cgride::core::Hasher hasher;

    hasher
        .update("hello")
        .update(" ")
        .update("cgride");

    const auto direct = cgride::core::hash_string("hello cgride");
    (void)direct;

    assert(hasher.value() == direct);
  }

  {
    const auto first = cgride::core::hash_string("core");
    const auto second = cgride::core::hash_string("engine");

    const auto combined_a = cgride::core::combine_hash(first, second);
    const auto combined_b = cgride::core::combine_hash(first, second);
    const auto combined_c = cgride::core::combine_hash(second, first);
    (void)combined_a;
    (void)combined_b;
    (void)combined_c;

    assert(combined_a == combined_b);
    assert(combined_a != combined_c);
  }

  {
    const auto root = std::filesystem::temp_directory_path() / "cgride_core_hash_test";
    const auto file = root / "input.txt";

    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root);

    {
      std::ofstream output(file, std::ios::binary);
      output << "hello";
    }

    auto result = cgride::core::hash_file(file);

    assert(result);
    assert(result.value() == cgride::core::hash_string("hello"));

    auto hex_result = cgride::core::hash_file_hex(file);

    assert(hex_result);
    assert(hex_result.value() == "a430d84680aabd0b");

    std::filesystem::remove_all(root);
  }

  {
    const auto missing = std::filesystem::temp_directory_path() / "cgride_core_hash_missing.txt";

    std::filesystem::remove(missing);

    auto result = cgride::core::hash_file(missing);

    assert(!result);
    assert(result.has_error());
    assert(result.error().code() == cgride::core::ErrorCode::IoError);
  }

  return 0;
}
