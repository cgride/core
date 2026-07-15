/**
 *
 *  @file hash.cpp
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
#include <cgride/core/hash.hpp>

#include <array>
#include <fstream>

namespace cgride::core
{
  namespace
  {
    constexpr std::size_t file_buffer_size = 64 * 1024;

    HashValue update_hash(HashValue seed, const void *data, std::size_t size) noexcept
    {
      const auto *bytes = static_cast<const unsigned char *>(data);
      auto value = seed;

      for (std::size_t index = 0; index < size; ++index)
      {
        value ^= static_cast<HashValue>(bytes[index]);
        value *= fnv1a_prime;
      }

      return value;
    }

  } // namespace

  void Hasher::reset() noexcept
  {
    value_ = fnv1a_offset_basis;
  }

  Hasher &Hasher::update_bytes(const void *data, std::size_t size) noexcept
  {
    if (data == nullptr || size == 0)
    {
      return *this;
    }

    value_ = update_hash(value_, data, size);
    return *this;
  }

  Hasher &Hasher::update(std::string_view value) noexcept
  {
    return update_bytes(value.data(), value.size());
  }

  Hasher &Hasher::update_u64(std::uint64_t value) noexcept
  {
    return update_bytes(&value, sizeof(value));
  }

  HashValue Hasher::value() const noexcept
  {
    return value_;
  }

  std::string Hasher::hex() const
  {
    return hash_to_hex(value_);
  }

  HashValue hash_bytes(const void *data, std::size_t size) noexcept
  {
    if (data == nullptr || size == 0)
    {
      return fnv1a_offset_basis;
    }

    return update_hash(fnv1a_offset_basis, data, size);
  }

  HashValue hash_string(std::string_view value) noexcept
  {
    return hash_bytes(value.data(), value.size());
  }

  HashValue combine_hash(HashValue seed, HashValue value) noexcept
  {
    return update_hash(seed, &value, sizeof(value));
  }

  std::string hash_to_hex(HashValue value)
  {
    constexpr char digits[] = "0123456789abcdef";

    std::string output;
    output.resize(16);

    for (std::size_t index = 0; index < 16; ++index)
    {
      const auto shift = static_cast<unsigned int>((15 - index) * 4);
      output[index] = digits[(value >> shift) & 0x0f];
    }

    return output;
  }

  Result<HashValue> hash_file(const std::filesystem::path &path)
  {
    std::ifstream stream(path, std::ios::binary);

    if (!stream)
    {
      return Error(
          ErrorCode::IoError,
          "Failed to open file for hashing.",
          path);
    }

    Hasher hasher;
    std::array<char, file_buffer_size> buffer{};

    while (stream)
    {
      stream.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
      const auto count = stream.gcount();

      if (count > 0)
      {
        hasher.update_bytes(buffer.data(), static_cast<std::size_t>(count));
      }
    }

    if (stream.bad())
    {
      return Error(
          ErrorCode::IoError,
          "Failed to read file while hashing.",
          path);
    }

    return hasher.value();
  }

  Result<std::string> hash_file_hex(const std::filesystem::path &path)
  {
    auto result = hash_file(path);

    if (!result)
    {
      return result.error();
    }

    return hash_to_hex(result.value());
  }

} // namespace cgride::core
