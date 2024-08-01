

#include "reaction_parser/core.hpp"

#include <format>
#include <list>

namespace {

auto FindStoichCoefficient(const std::string& raw_species_name) noexcept
    -> std::pair<std::string, int> {
    if (!std::isdigit(static_cast<unsigned char>(raw_species_name[0]))) {
        return {raw_species_name, 1};
    }

    const auto stoichometric_coefficient{
        std::stoi(raw_species_name.substr(0, 1))};
    return {raw_species_name.substr(1), stoichometric_coefficient};
}

struct ReactionToSplit final {
    std::string reaction_str;
    std::string eq_symbol;
};

auto SplitReactionStr(const ReactionToSplit& reaction_to_split) noexcept
    -> std::pair<std::string, std::string> {
    if (reaction_to_split.eq_symbol.empty()) {
        return {reaction_to_split.reaction_str, ""};
    }

    auto eq_symbol_position{
        reaction_to_split.reaction_str.find(reaction_to_split.eq_symbol)};
    auto eq_symbol_size{reaction_to_split.eq_symbol.size()};

    if (eq_symbol_position == std::string::npos) {
        return {reaction_to_split.reaction_str, ""};
    }

    return {reaction_to_split.reaction_str.substr(0, eq_symbol_position),
            reaction_to_split.reaction_str.substr(eq_symbol_position +
                                                  eq_symbol_size)};
}

auto FindAllSpecies(const std::string& reaction_str,
                    const std::regex&  species_expression) noexcept
    -> std::list<std::string> {
    return {std::sregex_token_iterator{
                reaction_str.cbegin(), reaction_str.cend(), species_expression},
            std::sregex_token_iterator{}};
}

}  // namespace

lab109::ReactionParser::ReactionParser(
    const std::initializer_list<std::string>& species_names,
    std::string&&                             eq_symbol)
    : species_names_{species_names}, eq_symbol_{eq_symbol} {}

lab109::ReactionParser::ReactionParser(
    const std::initializer_list<std::string>& species_names)
    : species_names_{species_names}, eq_symbol_{"<=>"} {}

auto lab109::ReactionParser::ParseReaction(
    const std::string& reaction_str) const -> ParseResultType {
    ParseResultType parse_result{};

    auto [lhs_reaction_str, rhs_reaction_str] =
        SplitReactionStr(ReactionToSplit(reaction_str, eq_symbol_));

    if (rhs_reaction_str.empty()) {
        throw lab109::ReactionParserError(
            reaction_str,
            std::format(R"(Can not find eq_symbol "{}")", eq_symbol_));
    }

    auto lhs_raw_species_names{
        FindAllSpecies(lhs_reaction_str, species_expression_)};

    auto rhs_raw_species_names{
        FindAllSpecies(rhs_reaction_str, species_expression_)};

    for (const auto& s_name : species_names_) {
        parse_result[s_name] = {0, 0};
    }

    for (const auto& raw_species_name : lhs_raw_species_names) {
        auto [s_name, s_coefficient] = FindStoichCoefficient(raw_species_name);

        if (species_names_.find(s_name) != species_names_.end()) {
            parse_result.at(s_name).first += s_coefficient;
        } else {
            throw lab109::ReactionParserError(
                reaction_str,
                std::format(
                    R"(Can not find species with name "{}" in initial species list)",
                    s_name));
        }
    }

    for (const auto& raw_species_name : rhs_raw_species_names) {
        auto [s_name, s_coefficient] = FindStoichCoefficient(raw_species_name);

        if (species_names_.find(s_name) != species_names_.end()) {
            parse_result.at(s_name).second += s_coefficient;
        } else {
            throw lab109::ReactionParserError(
                reaction_str,
                std::format(
                    R"(Can not find species with name "{}" in initial species list)",
                    s_name));
        }
    }
    return parse_result;
}

lab109::ReactionParserError::ReactionParserError(
    const std::string& reaction_str, const std::string& optional_msg)
    : error_msg_{std::format(R"(Error while parsing reaction "{}. {}")",
                             reaction_str,
                             optional_msg)} {}

auto lab109::ReactionParserError::what() const noexcept -> const char* {
    return error_msg_.c_str();
}