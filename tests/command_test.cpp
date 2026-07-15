/**
 *
 *  @file command_test.cpp
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
#include <string>

#include <cgride/core/command.hpp>

int main()
{
  {
    cgride::core::Command command;

    assert(command.program().empty());
    assert(command.args().empty());
    assert(command.environment().empty());
    assert(!command.cwd().has_value());
    assert(command.search_in_path());
    assert(command.inherit_environment());
    assert(!command.valid());
  }

  {
    cgride::core::Command command("clang++");

    assert(command.program() == "clang++");
    assert(command.args().empty());
    assert(command.valid());
  }

  {
    cgride::core::Command command("c++");

    command
        .arg("-std=c++23")
        .arg("-Wall")
        .arg("-c")
        .arg("main.cpp");

    assert(command.args().size() == 4);
    assert(command.args()[0] == "-std=c++23");
    assert(command.args()[1] == "-Wall");
    assert(command.args()[2] == "-c");
    assert(command.args()[3] == "main.cpp");
  }

  {
    cgride::core::Command command("c++");

    command.args({
        "-O2",
        "-DNDEBUG",
        "main.cpp",
    });

    assert(command.args().size() == 3);
    assert(command.args()[0] == "-O2");
    assert(command.args()[1] == "-DNDEBUG");
    assert(command.args()[2] == "main.cpp");
  }

  {
    cgride::core::Command command("cgride");

    command
        .env("CGRIDE_PROFILE", "debug")
        .env("CGRIDE_COLOR", "never");

    assert(command.environment().size() == 2);
    assert(command.environment()[0].first == "CGRIDE_PROFILE");
    assert(command.environment()[0].second == "debug");
    assert(command.environment()[1].first == "CGRIDE_COLOR");
    assert(command.environment()[1].second == "never");
  }

  {
    const std::filesystem::path path = "build/debug";

    cgride::core::Command command("c++");
    command.cwd(path);

    assert(command.cwd().has_value());
    assert(command.cwd().value() == path);
  }

  {
    cgride::core::Command command("tool");

    command.search_in_path(false);
    assert(!command.search_in_path());

    command.search_in_path(true);
    assert(command.search_in_path());
  }

  {
    cgride::core::Command command("tool");

    command.inherit_environment(false);
    assert(!command.inherit_environment());

    command.inherit_environment(true);
    assert(command.inherit_environment());
  }

  {
    cgride::core::Command command("old");
    command.program("new");

    assert(command.program() == "new");
    assert(command.valid());
  }

  return 0;
}
