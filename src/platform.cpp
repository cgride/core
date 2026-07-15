/**
 *
 *  @file platform.cpp
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
#include <cgride/core/platform.hpp>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

namespace cgride::core
{
  std::string_view to_string(Platform platform) noexcept
  {
    switch (platform)
    {
    case Platform::Unknown:
      return "Unknown";

    case Platform::Linux:
      return "Linux";

    case Platform::MacOS:
      return "MacOS";

    case Platform::Windows:
      return "Windows";

    case Platform::FreeBSD:
      return "FreeBSD";

    case Platform::OpenBSD:
      return "OpenBSD";

    case Platform::NetBSD:
      return "NetBSD";

    case Platform::Android:
      return "Android";

    case Platform::IOS:
      return "IOS";
    }

    return "Unknown";
  }

  std::string_view to_string(Architecture architecture) noexcept
  {
    switch (architecture)
    {
    case Architecture::Unknown:
      return "Unknown";

    case Architecture::X86:
      return "X86";

    case Architecture::X86_64:
      return "X86_64";

    case Architecture::ARM:
      return "ARM";

    case Architecture::ARM64:
      return "ARM64";

    case Architecture::RiscV64:
      return "RiscV64";

    case Architecture::Wasm32:
      return "Wasm32";

    case Architecture::Wasm64:
      return "Wasm64";
    }

    return "Unknown";
  }

  Platform host_platform() noexcept
  {
#if defined(_WIN32)
    return Platform::Windows;
#elif defined(__ANDROID__)
    return Platform::Android;
#elif defined(__APPLE__) && defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
    return Platform::IOS;
#elif defined(__APPLE__) && defined(TARGET_OS_MAC) && TARGET_OS_MAC
    return Platform::MacOS;
#elif defined(__linux__)
    return Platform::Linux;
#elif defined(__FreeBSD__)
    return Platform::FreeBSD;
#elif defined(__OpenBSD__)
    return Platform::OpenBSD;
#elif defined(__NetBSD__)
    return Platform::NetBSD;
#else
    return Platform::Unknown;
#endif
  }

  Architecture host_architecture() noexcept
  {
#if defined(__x86_64__) || defined(_M_X64)
    return Architecture::X86_64;
#elif defined(__i386__) || defined(_M_IX86)
    return Architecture::X86;
#elif defined(__aarch64__) || defined(_M_ARM64)
    return Architecture::ARM64;
#elif defined(__arm__) || defined(_M_ARM)
    return Architecture::ARM;
#elif defined(__riscv) && defined(__riscv_xlen) && (__riscv_xlen == 64)
    return Architecture::RiscV64;
#elif defined(__wasm64__)
    return Architecture::Wasm64;
#elif defined(__wasm32__)
    return Architecture::Wasm32;
#else
    return Architecture::Unknown;
#endif
  }

  bool is_windows(Platform platform) noexcept
  {
    return platform == Platform::Windows;
  }

  bool is_posix_like(Platform platform) noexcept
  {
    switch (platform)
    {
    case Platform::Linux:
    case Platform::MacOS:
    case Platform::FreeBSD:
    case Platform::OpenBSD:
    case Platform::NetBSD:
    case Platform::Android:
    case Platform::IOS:
      return true;

    case Platform::Windows:
    case Platform::Unknown:
      return false;
    }

    return false;
  }

  std::string_view executable_extension(Platform platform) noexcept
  {
    if (is_windows(platform))
    {
      return ".exe";
    }

    return "";
  }

  std::string_view object_file_extension(Platform platform) noexcept
  {
    if (is_windows(platform))
    {
      return ".obj";
    }

    return ".o";
  }

  std::string_view static_library_prefix(Platform platform) noexcept
  {
    if (is_windows(platform))
    {
      return "";
    }

    return "lib";
  }

  std::string_view static_library_extension(Platform platform) noexcept
  {
    if (is_windows(platform))
    {
      return ".lib";
    }

    return ".a";
  }

  std::string_view shared_library_prefix(Platform platform) noexcept
  {
    if (is_windows(platform))
    {
      return "";
    }

    return "lib";
  }

  std::string_view shared_library_extension(Platform platform) noexcept
  {
    switch (platform)
    {
    case Platform::Windows:
      return ".dll";

    case Platform::MacOS:
    case Platform::IOS:
      return ".dylib";

    case Platform::Linux:
    case Platform::FreeBSD:
    case Platform::OpenBSD:
    case Platform::NetBSD:
    case Platform::Android:
    case Platform::Unknown:
      return ".so";
    }

    return ".so";
  }

  char path_list_separator(Platform platform) noexcept
  {
    if (is_windows(platform))
    {
      return ';';
    }

    return ':';
  }

} // namespace cgride::core
