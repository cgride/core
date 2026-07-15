/**
 *
 *  @file command.cpp
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
#include <cgride/core/command.hpp>

namespace cgride::core
{
  Command::Command(std::string program)
      : program_(std::move(program))
  {
  }

  Command &Command::program(std::string program)
  {
    program_ = std::move(program);
    return *this;
  }

  Command &Command::arg(std::string value)
  {
    args_.push_back(std::move(value));
    return *this;
  }

  Command &Command::args(std::vector<std::string> values)
  {
    for (auto &value : values)
    {
      args_.push_back(std::move(value));
    }

    return *this;
  }

  Command &Command::env(std::string key, std::string value)
  {
    environment_.emplace_back(std::move(key), std::move(value));
    return *this;
  }

  Command &Command::cwd(std::filesystem::path value)
  {
    cwd_ = std::move(value);
    return *this;
  }

  Command &Command::search_in_path(bool value) noexcept
  {
    search_in_path_ = value;
    return *this;
  }

  Command &Command::inherit_environment(bool value) noexcept
  {
    inherit_environment_ = value;
    return *this;
  }

  const std::string &Command::program() const noexcept
  {
    return program_;
  }

  const std::vector<std::string> &Command::args() const noexcept
  {
    return args_;
  }

  const std::vector<std::pair<std::string, std::string>> &Command::environment() const noexcept
  {
    return environment_;
  }

  const std::optional<std::filesystem::path> &Command::cwd() const noexcept
  {
    return cwd_;
  }

  bool Command::search_in_path() const noexcept
  {
    return search_in_path_;
  }

  bool Command::inherit_environment() const noexcept
  {
    return inherit_environment_;
  }

  bool Command::valid() const noexcept
  {
    return !program_.empty();
  }

} // namespace cgride::core
