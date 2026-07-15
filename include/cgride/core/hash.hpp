/**
 *
 *  @file hash.hpp
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
#ifndef CGRIDE_CORE_HASH_HPP
#define CGRIDE_CORE_HASH_HPP

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>

#include <cgride/core/result.hpp>

namespace cgride::core
{
  /**
   * @brief 64-bit hash value used by Cgride core utilities.
   */
  using HashValue = std::uint64_t;

  /**
   * @brief Initial value used by the stable FNV-1a hash implementation.
   */
  inline constexpr HashValue fnv1a_offset_basis = 14695981039346656037ull;

  /**
   * @brief Prime value used by the stable FNV-1a hash implementation.
   */
  inline constexpr HashValue fnv1a_prime = 1099511628211ull;

  /**
   * @class Hasher
   * @brief Incremental stable hash builder.
   *
   * Hasher is used for deterministic internal hashes such as cache keys,
   * command fingerprints and content identifiers.
   *
   * It is not a cryptographic hash.
   */
  class Hasher
  {
  public:
    /**
     * @brief Construct a hasher initialized with the default seed.
     */
    Hasher() = default;

    /**
     * @brief Reset the hasher to its initial state.
     */
    void reset() noexcept;

    /**
     * @brief Add raw bytes to the hash.
     *
     * @param data Pointer to bytes.
     * @param size Number of bytes.
     * @return Reference to this hasher.
     */
    Hasher &update_bytes(const void *data, std::size_t size) noexcept;

    /**
     * @brief Add a string view to the hash.
     *
     * @param value String value.
     * @return Reference to this hasher.
     */
    Hasher &update(std::string_view value) noexcept;

    /**
     * @brief Add a single unsigned 64-bit value to the hash.
     *
     * @param value Integer value.
     * @return Reference to this hasher.
     */
    Hasher &update_u64(std::uint64_t value) noexcept;

    /**
     * @brief Access the current hash value.
     */
    [[nodiscard]] HashValue value() const noexcept;

    /**
     * @brief Return the current hash value as lowercase hexadecimal.
     */
    [[nodiscard]] std::string hex() const;

  private:
    HashValue value_{fnv1a_offset_basis};
  };

  /**
   * @brief Hash raw bytes using the stable FNV-1a implementation.
   *
   * @param data Pointer to bytes.
   * @param size Number of bytes.
   * @return Hash value.
   */
  [[nodiscard]] HashValue hash_bytes(const void *data, std::size_t size) noexcept;

  /**
   * @brief Hash a string using the stable FNV-1a implementation.
   *
   * @param value String value.
   * @return Hash value.
   */
  [[nodiscard]] HashValue hash_string(std::string_view value) noexcept;

  /**
   * @brief Combine two hash values deterministically.
   *
   * @param seed Existing hash value.
   * @param value Hash value to combine.
   * @return Combined hash value.
   */
  [[nodiscard]] HashValue combine_hash(HashValue seed, HashValue value) noexcept;

  /**
   * @brief Convert a hash value to lowercase hexadecimal.
   *
   * @param value Hash value.
   * @return Lowercase hexadecimal string.
   */
  [[nodiscard]] std::string hash_to_hex(HashValue value);

  /**
   * @brief Hash the content of a file.
   *
   * @param path File path.
   * @return File hash or a structured error.
   */
  [[nodiscard]] Result<HashValue> hash_file(const std::filesystem::path &path);

  /**
   * @brief Hash the content of a file and return lowercase hexadecimal.
   *
   * @param path File path.
   * @return File hash as hexadecimal or a structured error.
   */
  [[nodiscard]] Result<std::string> hash_file_hex(const std::filesystem::path &path);

} // namespace cgride::core

#endif // CGRIDE_CORE_HASH_HPP
