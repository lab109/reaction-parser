/**
 * @file core.hpp
 * @author Tereshkin Vadim (tereshkinvadimst@gmail.com)
 * @brief Парсинг химических реакций
 * @version 1.0
 * @date 2024-08-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef LAB108_REACTION_PARSER_CORE_HPP__
#define LAB108_REACTION_PARSER_CORE_HPP__

#include <exception>
#include <initializer_list>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace lab109 {

/**
 * @brief Парсер химических реакций
 *
 */
class ReactionParser final {
   public:
    /// Результат парсинга химической реакции
    using ParseResultType =
        std::unordered_map<std::string, std::pair<int, int>>;

    /**
     * @brief Конструктор парсера химических реакций
     *
     * @param species_names имена компонентов смеси
     * @param eq_symbol символ химического уравнения
     */
    ReactionParser(const std::initializer_list<std::string>& species_names,
                   std::string&&                             eq_symbol);

    /**
     * @brief Конструктор парсера химических реакций
     *
     * @param species_names имена компонентов смеси
     */
    ReactionParser(const std::initializer_list<std::string>& species_names);

    /**
     * @brief Парсинг реакции
     *
     * @param reaction_str исходная строка реакции
     * @return ParseResultType
     */
    [[nodiscard]] auto ParseReaction(const std::string& reaction_str) const
        -> ParseResultType;

   private:
    static const inline std::regex  species_expression_{R"(\d?[A-Z](\S?)+)"};
    std::string                     eq_symbol_;
    std::unordered_set<std::string> species_names_;
};

/**
 * @brief Тип исключения, выбрасываемого при ошибке парсинга реакции
 *
 */
class ReactionParserError final : public std::exception {
   public:
    explicit ReactionParserError(const std::string& reaction_str,
                                 const std::string& optional_msg = "");

    /**
     * @brief Вывести сообщение об ошибке
     *
     * @return const char*
     */
    [[nodiscard]] auto what() const noexcept -> const char* override;

   private:
    std::string error_msg_;
};

}  // namespace lab109

#endif  // LAB108_REACTION_PARSER_CORE_HPP__