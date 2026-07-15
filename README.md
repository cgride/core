# Cgride Core

Core types, results, errors, events, paths and utilities for Cgride.

Cgride Core is the foundation module used by the other Cgride modules. It contains the common public types needed to build the engine without coupling higher-level modules to the CLI, terminal output or platform-specific implementation details.

## Purpose

This module provides the shared primitives used across Cgride:

- result and error handling
- structured diagnostics
- structured events
- command representation
- platform and architecture detection
- path utilities
- stable hashing helpers
- cancellation primitives

Cgride Core does not contain build planning, toolchain discovery, task execution or CLI logic.

## Requirements

- C++23
- CMake 3.22 or newer
- Vix.cpp

## Build

```bash
vix build --build-target all
```

## Run tests

```bash
vix tests
```

## Release build

```bash
vix build --preset release --build-target all
```

## Install

```bash
vix build --build-target all
sudo cmake --install build-ninja --prefix /usr/local
```

## CMake usage

```cmake
find_package(cgride-core CONFIG REQUIRED)

target_link_libraries(my_tool PRIVATE cgride::core)
```

## Module boundary

Cgride Core may be used by:

- `cgride::project`
- `cgride::graph`
- `cgride::toolchains`
- `cgride::executor`
- `cgride::cache`
- `cgride::engine`
- `cgride::config`
- `cgride::cli`

Cgride Core must not depend on any higher-level Cgride module.

## License

MIT
