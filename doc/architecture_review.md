# Architecture Review

## Current Architecture Status
The current architecture follows a basic Monolithic CLI structure with partial modularity achieved through the `IApplication` interface. `CoreCLI` acts as the central controller, managing the lifecycle of various "Applications" (modules).

### Strengths
1.  **Simple Entry Point**: `CoreCLI` provides a unified entry point and prompt loop.
2.  **Basic Modularity**: New functionality can be added by implementing `IApplication`.
3.  **Library Reuse**: Common libraries like `spdlog` and `readline` are integrated.

### Weaknesses
1.  **Tight Coupling**: `CoreCLI` needs to know about concrete application classes (`svdParser_IApp`, `mainApp`) to instantiate them in `start()`. This violates the Open/Closed Principle.
2.  **State Management**: `CoreCLI` uses global/static state (`currentApp`, `crntCommandList`) which makes testing and parallel execution difficult.
3.  **Command Handling**: Use of `readline` is good, but the command parsing logic in `executeCommand` is manual and brittle.
4.  **Dependency Injection**: Dependencies are manually managed, leading to hard-to-test components.
5.  **Interface Pollution**: `IApplication` mixes lifecycle methods (`init`, `run`) with command registration, making it a "heavy" interface.

## Code Quality Observations
- **Header Guards**: `#pragma once` is used consistently.
- **Includes**: Some headers include implementation details that cause warnings (like virtual function overrides not marked `override`).
- **Mixed C++ Standards**: Codebase seems to be transitioning between older C++ (usage of raw pointers) and newer C++ (smart pointers in some places). `CMakeLists.txt` was just updated to C++17.

## Recommendations
- **Decouple App Registration**: Implement a factory or registry pattern so `CoreCLI` doesn't need to depend on concrete app classes.
- **Modernize C++**: Enforce `override` keyword usage and move fully to smart pointers.
- **Refactor CLI Loop**: Separate the "Prompt/Readline" logic from the "Command Dispatch" logic.
