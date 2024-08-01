# Парсер химических реакци

## Как использовать?

```sh
git submodule add https://github.com/lab109/reaction-parser.git
```

или

```sh
git submodule add git@github.com:lab109/reaction-parser.git
```

В cmake-проект добавить

```cmake
add_subdirectory(reaction-parser)
...
target_link_libraries(project_name PRIVATE lab109::reaction_parser)
```

Пример использования кода в проекте

```cxx

#include <iostream>
#include <list>
#include <ostream>
#include <reaction_parser/core.hpp>

auto main() -> int {
    lab109::ReactionParser reaction_parser({"O2", "O"}, "->");

    std::list<std::string> reactions{"O2 + O2 -> O + O + O2",
                                     "O2 + O -> O + O + O"};

    try {
        for (const auto& reactions_str : reactions) {
            auto result{reaction_parser.ParseReaction(reactions_str)};
            std::cout << reactions_str << '\n';
            for (const auto& [name, ab] : result) {
                std::cout << name + "\t" << ab.first << '\t' << ab.second
                          << '\n';
            }
        }
    } catch (lab109::ReactionParserError& parser_error) {
        std::cerr << parser_error.what() << std::endl;
    }
}
```
