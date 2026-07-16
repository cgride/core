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
- Vix CLI
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

## Build

From the module directory, use the Vix workflow:

```bash
vix build
```

For a release build:

```bash
vix build --preset release
```

## Run tests

```bash
vix check --tests
```

## Install

```bash
vix install
```

The install step exposes the `cgride::core` integration target, public headers, and package metadata.

## Integration

C++ integrations can use the installed module target from their project build configuration.


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
