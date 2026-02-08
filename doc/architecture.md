# System Architecture

## Overview
The system is designed as a CLI (Command Line Interface) tool that manages multiple sub-applications. The core component, `CoreCLI`, handles the main prompt loop and delegates execution to registered applications based on user input.

## Diagrams

### Component Diagram

```mermaid
graph TD
    User[User] --> CLI[CoreCLI]
    CLI -->|Manages| AppMgr[Application Manager]
    AppMgr -->|Runs| SVD[SVD Parser App]
    AppMgr -->|Runs| Main[Main App]
    AppMgr -->|Runs| Net[Network App]
    
    subgraph Libraries
        SPD[spdlog]
        RL[readline]
        XML[TinyXML2]
    end
    
    SVD --> XML
    CLI --> RL
    CLI --> SPD
```

### Class Diagram

```mermaid
classDiagram
    class CoreCLI {
        -currentApp : IApplication*
        -crntCommandList : vector<string>
        -apps : vector<unique_ptr<IApplication>>
        +start()
        +runPromptLoop(prompt)
        +executeCommand(command)
        +registerCommand(command)
    }

    class IApplication {
        <<abstract>>
        -name : string
        -commands : vector<command*>
        +init()*
        +run(arguments)*
        +finalize()*
        +executeCommand(cmd, args)
        +setCommandRegistrar(func)
    }

    class svdParser_IApp {
        +init()
        +run()
        +finalize()
    }
    
    class mainApp {
        +init()
        +run()
        +finalize()
    }

    class netIApp {
        +init()
        +run()
        +finalize()
    }

    CoreCLI "1" *-- "*" IApplication : manages
    IApplication <|-- svdParser_IApp
    IApplication <|-- mainApp
    IApplication <|-- netIApp
```

### Sequence Diagram - Application Execution

```mermaid
sequenceDiagram
    participant User
    participant CLI as CoreCLI
    participant App as IApplication
    
    User->>CLI: Enter "svd"
    CLI->>CLI: Parse command
    CLI->>App: init()
    CLI->>App: run(args)
    App-->>CLI: Control returned
    CLI->>App: finalize()
    CLI-->>User: Show prompt
```
