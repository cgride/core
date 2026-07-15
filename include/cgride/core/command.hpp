/**
 *
 *  @file command.hpp
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
#ifndef CGRIDE_CORE_COMMAND_HPP
#define CGRIDE_CORE_COMMAND_HPP

#include <filesystem>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace cgride::core
{
  /**
   * @class Command
   * @brief Describes a process command without invoking a shell.
   *
   * Command stores:
   * - program path or executable name
   * - arguments
   * - environment overrides
   * - optional working directory
   *
   * Design goals:
   * - explicit and readable
   * - no hidden shell parsing
   * - portable across POSIX and Windows
   * - safe to pass between Cgride modules
   */
  class Command
  {
  public:
    /**
     * @brief Construct an empty command.
     */
    Command() = default;

    /**
     * @brief Construct a command from a program path or executable name.
     *
     * @param program Executable path or program name.
     */
    explicit Command(std::string program);

    /**
     * @brief Set the program path or executable name.
     *
     * @param program Executable path or program name.
     * @return Reference to this command.
     */
    Command &program(std::string program);

    /**
     * @brief Add one argument.
     *
     * @param value Argument value.
     * @return Reference to this command.
     */
    Command &arg(std::string value);

    /**
     * @brief Add many arguments.
     *
     * @param values Arguments to append.
     * @return Reference to this command.
     */
    Command &args(std::vector<std::string> values);

    /**
     * @brief Add one environment override.
     *
     * @param key Environment variable name.
     * @param value Environment variable value.
     * @return Reference to this command.
     */
    Command &env(std::string key, std::string value);

    /**
     * @brief Set the working directory for the command.
     *
     * @param value Working directory path.
     * @return Reference to this command.
     */
    Command &cwd(std::filesystem::path value);

    /**
     * @brief Control whether executable lookup may use PATH.
     *
     * @param value True to search in PATH, false otherwise.
     * @return Reference to this command.
     */
    Command &search_in_path(bool value) noexcept;

    /**
     * @brief Control whether the parent environment is inherited.
     *
     * @param value True to inherit, false otherwise.
     * @return Reference to this command.
     */
    Command &inherit_environment(bool value) noexcept;

    /**
     * @brief Access the configured program.
     */
    [[nodiscard]] const std::string &program() const noexcept;

    /**
     * @brief Access the configured argument list.
     */
    [[nodiscard]] const std::vector<std::string> &args() const noexcept;

    /**
     * @brief Access the configured environment overrides.
     */
    [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &environment() const noexcept;

    /**
     * @brief Access the optional working directory.
     */
    [[nodiscard]] const std::optional<std::filesystem::path> &cwd() const noexcept;

    /**
     * @brief Return true if executable lookup may use PATH.
     */
    [[nodiscard]] bool search_in_path() const noexcept;

    /**
     * @brief Return true if the parent environment should be inherited.
     */
    [[nodiscard]] bool inherit_environment() const noexcept;

    /**
     * @brief Return true if the command has a non-empty program.
     */
    [[nodiscard]] bool valid() const noexcept;

  private:
    std::string program_{};
    std::vector<std::string> args_{};
    std::vector<std::pair<std::string, std::string>> environment_{};
    std::optional<std::filesystem::path> cwd_{};
    bool search_in_path_{true};
    bool inherit_environment_{true};
  };

} // namespace cgride::core

#endif // CGRIDE_CORE_COMMAND_HPP
