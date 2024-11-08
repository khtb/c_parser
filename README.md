# C parser 

A brief description of what this project does and who it's for.

## Installation

install clang using wget
```sh
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 14
```

or
```sh  
sudo apt install llvm-14-dev libclang-14-dev
```









| **Component**           | **Convention**                | **Example**                    |
|-------------------------|-------------------------------|--------------------------------|
| **Local Variables**     | `camelCase`                   | `itemCount`, `userName`        |
| **Member Variables**    | `camelCase` with `_` suffix   | `itemCount_`, `userName_`      |
| **Global Variables**    | `g_` prefix                   | `g_maxUsers`, `g_configPath`   |
| **Constants**           | `UPPER_CASE` with underscores | `MAX_BUFFER_SIZE`, `PI`        |
| **Functions/Methods**   | `camelCase`                   | `calculateArea()`, `getUser()` |
| **Classes**             | `PascalCase`                  | `UserProfile`, `AccountManager`|
| **Structs**             | `PascalCase` or `camelCase`   | `UserInfo`, `pointData`        |
| **Enums**               | `PascalCase` (scoped)         | `Color::Red`, `Status::OK`     |
|                         | `UPPER_CASE` (unscoped)       | `NORTH`, `SOUTH`               |
| **Namespaces**          | `lowercase` or `snake_case`   | `my_project::core`             |
| **Template Parameters** | `PascalCase` with `T` prefix  | `TKey`, `TValue`               |
| **Macros**              | `UPPER_CASE` with underscores | `MAX_ARRAY_SIZE`, `DEBUG_LOG`  |
| **Header Files**        | `PascalCase` or `snake_case`  | `UserProfile.h`, `user_info.h` |

