
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