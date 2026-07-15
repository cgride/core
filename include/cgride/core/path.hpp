/**
 *
 *  @file path.hpp
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
#ifndef CGRIDE_CORE_PATH_HPP
#define CGRIDE_CORE_PATH_HPP

#include <filesystem>
#include <string>
#include <string_view>

#include <cgride/core/result.hpp>

namespace cgride::core
{
  /**
   * @enum PathKind
   * @brief Filesystem entry kind recognized by Cgride.
   */
  enum class PathKind
  {
    Missing,
    File,
    Directory,
    Symlink,
    Other
  };

  /**
   * @brief Convert a path kind to a stable string.
   *
   * @param kind Path kind.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(PathKind kind) noexcept;

  /**
   * @brief Return a lexically normalized path.
   *
   * This function does not access the filesystem.
   *
   * @param path Path to normalize.
   * @return Lexically normalized path.
   */
  [[nodiscard]] std::filesystem::path normalize_path(const std::filesystem::path &path);

  /**
   * @brief Join two paths and normalize the result lexically.
   *
   * This function does not access the filesystem.
   *
   * @param base Base path.
   * @param child Child path.
   * @return Joined and normalized path.
   */
  [[nodiscard]] std::filesystem::path join_path(const std::filesystem::path &base,
                                                const std::filesystem::path &child);

  /**
   * @brief Convert a path to an absolute normalized path.
   *
   * @param path Path to convert.
   * @return Absolute normalized path or a structured error.
   */
  [[nodiscard]] Result<std::filesystem::path> absolute_path(const std::filesystem::path &path);

  /**
   * @brief Convert a path to an absolute normalized path using a base directory.
   *
   * If path is already absolute, the base directory is ignored.
   *
   * @param base Base directory.
   * @param path Path to convert.
   * @return Absolute normalized path or a structured error.
   */
  [[nodiscard]] Result<std::filesystem::path> absolute_path(const std::filesystem::path &base,
                                                            const std::filesystem::path &path);

  /**
   * @brief Compute a relative path from one location to another.
   *
   * @param from Base path.
   * @param to Target path.
   * @return Relative path or a structured error.
   */
  [[nodiscard]] Result<std::filesystem::path> relative_path(const std::filesystem::path &from,
                                                            const std::filesystem::path &to);

  /**
   * @brief Return true if the path exists.
   *
   * @param path Path to inspect.
   * @return True if the path exists.
   */
  [[nodiscard]] bool path_exists(const std::filesystem::path &path);

  /**
   * @brief Return true if the path is a regular file.
   *
   * @param path Path to inspect.
   * @return True if the path is a regular file.
   */
  [[nodiscard]] bool is_regular_file_path(const std::filesystem::path &path);

  /**
   * @brief Return true if the path is a directory.
   *
   * @param path Path to inspect.
   * @return True if the path is a directory.
   */
  [[nodiscard]] bool is_directory_path(const std::filesystem::path &path);

  /**
   * @brief Detect the filesystem kind of a path.
   *
   * @param path Path to inspect.
   * @return Detected path kind.
   */
  [[nodiscard]] PathKind path_kind(const std::filesystem::path &path);

  /**
   * @brief Ensure that a directory exists.
   *
   * This function creates missing parent directories when needed.
   *
   * @param path Directory path.
   * @return Success or a structured error.
   */
  [[nodiscard]] Result<void> ensure_directory(const std::filesystem::path &path);

  /**
   * @brief Return a portable generic string form of a path.
   *
   * Generic strings use '/' as a separator.
   *
   * @param path Path to convert.
   * @return Generic string representation.
   */
  [[nodiscard]] std::string portable_path_string(const std::filesystem::path &path);

  /**
   * @brief Return the native string form of a path.
   *
   * @param path Path to convert.
   * @return Native string representation for the host platform.
   */
  [[nodiscard]] std::string native_path_string(const std::filesystem::path &path);

} // namespace cgride::core

#endif // CGRIDE_CORE_PATH_HPP
