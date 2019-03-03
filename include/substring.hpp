// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_SUBSTRING_HPP_
#define INCLUDE_SUBSTRING_HPP_

#include <string>
#include <functional>
#include <vector>

/// Поиск подстроки в тупую
size_t str_find(const std::string &str, const std::string &substr);

///Поиск подстроки в строке алгоритмом Рабина—Карпа
size_t rk_find(const std::string &str, const std::string &substr);

/// Поиск подстроки в строке алгоритмом Кнута—Морриса—Пратта
size_t kmp_find(const std::string &str, const std::string &substr);

#endif // INCLUDE_SUBSTRING_HPP_
