/**
 *
 *  @file platform.hpp
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
#ifndef CGRIDE_CORE_PLATFORM_HPP
#define CGRIDE_CORE_PLATFORM_HPP

#include <string_view>

namespace cgride::core
{
  /**
   * @enum Platform
   * @brief Operating-system platform recognized by Cgride.
   */
  enum class Platform
  {
    Unknown,
    Linux,
    MacOS,
    Windows,
    FreeBSD,
    OpenBSD,
    NetBSD,
    Android,
    IOS
  };

  /**
   * @enum Architecture
   * @brief CPU architecture recognized by Cgride.
   */
  enum class Architecture
  {
    Unknown,
    X86,
    X86_64,
    ARM,
    ARM64,
    RiscV64,
    Wasm32,
    Wasm64
  };

  /**
   * @brief Convert a platform value to a stable string.
   *
   * @param platform Platform value.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(Platform platform) noexcept;

  /**
   * @brief Convert an architecture value to a stable string.
   *
   * @param architecture Architecture value.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(Architecture architecture) noexcept;

  /**
   * @brief Detect the platform used to build the current process.
   *
   * @return Host platform.
   */
  [[nodiscard]] Platform host_platform() noexcept;

  /**
   * @brief Detect the architecture used to build the current process.
   *
   * @return Host architecture.
   */
  [[nodiscard]] Architecture host_architecture() noexcept;

  /**
   * @brief Return true if the platform is Windows.
   *
   * @param platform Platform value.
   * @return True when the platform is Windows.
   */
  [[nodiscard]] bool is_windows(Platform platform) noexcept;

  /**
   * @brief Return true if the platform is POSIX-like for Cgride process handling.
   *
   * @param platform Platform value.
   * @return True when the platform is POSIX-like.
   */
  [[nodiscard]] bool is_posix_like(Platform platform) noexcept;

  /**
   * @brief Return the executable file extension for a platform.
   *
   * @param platform Platform value.
   * @return Executable extension, including the leading dot when present.
   */
  [[nodiscard]] std::string_view executable_extension(Platform platform) noexcept;

  /**
   * @brief Return the object file extension for a platform.
   *
   * @param platform Platform value.
   * @return Object file extension, including the leading dot.
   */
  [[nodiscard]] std::string_view object_file_extension(Platform platform) noexcept;

  /**
   * @brief Return the static library filename prefix for a platform.
   *
   * @param platform Platform value.
   * @return Static library prefix.
   */
  [[nodiscard]] std::string_view static_library_prefix(Platform platform) noexcept;

  /**
   * @brief Return the static library file extension for a platform.
   *
   * @param platform Platform value.
   * @return Static library extension, including the leading dot.
   */
  [[nodiscard]] std::string_view static_library_extension(Platform platform) noexcept;

  /**
   * @brief Return the shared library filename prefix for a platform.
   *
   * @param platform Platform value.
   * @return Shared library prefix.
   */
  [[nodiscard]] std::string_view shared_library_prefix(Platform platform) noexcept;

  /**
   * @brief Return the shared library file extension for a platform.
   *
   * @param platform Platform value.
   * @return Shared library extension, including the leading dot.
   */
  [[nodiscard]] std::string_view shared_library_extension(Platform platform) noexcept;

  /**
   * @brief Return the path-list separator for a platform.
   *
   * This is ';' on Windows and ':' on POSIX-like systems.
   *
   * @param platform Platform value.
   * @return Path-list separator.
   */
  [[nodiscard]] char path_list_separator(Platform platform) noexcept;

} // namespace cgride::core

#endif // CGRIDE_CORE_PLATFORM_HPP
