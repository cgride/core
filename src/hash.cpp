/**
 *
 *  @file path.cpp
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
#include <cgride/core/path.hpp>
#include <system_error>

namespace cgride::core
{
  std::string_view to_string(PathKind kind) noexcept
  {
    switch (kind)
    {
    case PathKind::Missing:
      return "Missing";

    case PathKind::File:
      return "File";

    case PathKind::Directory:
      return "Directory";

    case PathKind::Symlink:
      return "Symlink";

    case PathKind::Other:
      return "Other";
    }

    return "Other";
  }

  std::filesystem::path normalize_path(const std::filesystem::path &path)
  {
    return path.lexically_normal();
  }

  std::filesystem::path join_path(const std::filesystem::path &base,
                                  const std::filesystem::path &child)
  {
    return (base / child).lexically_normal();
  }

  Result<std::filesystem::path> absolute_path(const std::filesystem::path &path)
  {
    std::error_code ec;
    auto absolute = std::filesystem::absolute(path, ec);

    if (ec)
    {
      return Error(
          ErrorCode::IoError,
          "Failed to create absolute path.",
          ec.message(),
          path);
    }

    return absolute.lexically_normal();
  }

  Result<std::filesystem::path> absolute_path(const std::filesystem::path &base,
                                              const std::filesystem::path &path)
  {
    if (path.is_absolute())
    {
      return absolute_path(path);
    }

    return absolute_path(base / path);
  }

  Result<std::filesystem::path> relative_path(const std::filesystem::path &from,
                                              const std::filesystem::path &to)
  {
    std::error_code ec;
    auto relative = std::filesystem::relative(to, from, ec);

    if (ec)
    {
      return Error(
          ErrorCode::IoError,
          "Failed to create relative path.",
          ec.message(),
          to);
    }

    return relative.lexically_normal();
  }

  bool path_exists(const std::filesystem::path &path)
  {
    std::error_code ec;
    return std::filesystem::exists(path, ec);
  }

  bool is_regular_file_path(const std::filesystem::path &path)
  {
    std::error_code ec;
    return std::filesystem::is_regular_file(path, ec);
  }

  bool is_directory_path(const std::filesystem::path &path)
  {
    std::error_code ec;
    return std::filesystem::is_directory(path, ec);
  }

  PathKind path_kind(const std::filesystem::path &path)
  {
    std::error_code ec;
    const auto status = std::filesystem::symlink_status(path, ec);

    if (ec || !std::filesystem::exists(status))
    {
      return PathKind::Missing;
    }

    if (std::filesystem::is_symlink(status))
    {
      return PathKind::Symlink;
    }

    if (std::filesystem::is_regular_file(status))
    {
      return PathKind::File;
    }

    if (std::filesystem::is_directory(status))
    {
      return PathKind::Directory;
    }

    return PathKind::Other;
  }

  Result<void> ensure_directory(const std::filesystem::path &path)
  {
    if (path.empty())
    {
      return Error(
          ErrorCode::InvalidArgument,
          "Directory path is empty.");
    }

    if (is_directory_path(path))
    {
      return Result<void>::ok();
    }

    if (path_exists(path))
    {
      return Error(
          ErrorCode::InvalidState,
          "Path exists but is not a directory.",
          path);
    }

    std::error_code ec;
    std::filesystem::create_directories(path, ec);

    if (ec)
    {
      return Error(
          ErrorCode::IoError,
          "Failed to create directory.",
          ec.message(),
          path);
    }

    return Result<void>::ok();
  }

  std::string portable_path_string(const std::filesystem::path &path)
  {
    return path.generic_string();
  }

  std::string native_path_string(const std::filesystem::path &path)
  {
    return path.string();
  }

} // namespace cgride::core
