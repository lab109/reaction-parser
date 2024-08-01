#ifndef LAB108_REACTION_PARSER_CORE_HPP__
#define LAB108_REACTION_PARSER_CORE_HPP__

#include <exception>
#include <initializer_list>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace lab109 {

class ReactionParser final {
   public:
    using ParseResultType =
        std::unordered_map<std::string, std::pair<int, int>>;

    ReactionParser(const std::initializer_list<std::string>& species_names,
                   std::string&&                             eq_symbol);
    ReactionParser(const std::initializer_list<std::string>& species_names);

    auto ParseReaction(const std::string& reaction_str) const
        -> ParseResultType;

   private:
    static const inline std::regex species_expression_{R"(\d?[A-Z](\S?)+)"};
    const std::string              eq_symbol_;
    const std::unordered_set<std::string> species_names_;
};

class ReactionParserError final : public std::exception {
   public:
    explicit ReactionParserError(const std::string& reaction_str,
                                 const std::string& optional_msg = "");

    [[nodiscard]] auto what() const noexcept -> const char* override;

   private:
    std::string error_msg_;
};

}  // namespace lab109

#endif  // LAB108_REACTION_PARSER_CORE_HPP__