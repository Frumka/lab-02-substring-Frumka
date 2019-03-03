// Copyright 2019 Semenov Pavel <po@shablonu.sdelal>

#include "substring.hpp"


/// Функция хеширования для алгоритма Рабина-Карпа
size_t stupid_hash(const std::string &str) {
    size_t res = 0;
    size_t len = str.length();
    std::hash<char> hashFunc;
    for (size_t ind = 0; ind < len; ind++) {
        res ^= hashFunc(str[ind]);
    }
    return res;
}

/// Функция сдвига хеша
size_t roll_hash(size_t prevHash, const char prevChar, const char nextChar) {
    prevHash ^= prevChar;
    prevHash ^= nextChar;
    return prevHash;
}


/// Поиск подстроки в тупую(Пока что абсолютно в тупую)
///TODO: Придумать что-то поинтереснее абсолютно тупого поиска
size_t str_find(const std::string &str, const std::string &substr) {
    size_t strLen = str.length();
    size_t subLen = substr.length();
    for (size_t index1 = 0; index1 < strLen; index1++) {
        if (str[index1] != substr[0]) continue;
        for (size_t ind2 = 0; ind2 < subLen; ind2++) {
            if (index1 + subLen > strLen) return static_cast<size_t>(-1);
            if (str[index1 + ind2] != substr[ind2]) break;
            else if (ind2 == subLen - 1) return index1;
        }
    }
    return static_cast<size_t>(-1);
}

///Поиск первой подстроки в строке алгоритмом Рабина—Карпа
///С использованием кольцевого хеша
size_t rk_find(const std::string &str, const std::string &substr) {
    size_t subHash = stupid_hash(substr);
    size_t subLen = substr.length();
    size_t selfLen = str.length();
    if (subLen > selfLen) return static_cast<size_t>(-1);
    size_t steps = selfLen - subLen + 1;
    size_t mainHash = stupid_hash(str.substr(0, subLen));
    for (size_t ind = 1; ind <= steps; ind++) {
        if (mainHash == subHash) {
            if (str.substr(ind - 1, subLen) == substr)
                return ind - 1;
        }
        mainHash = roll_hash(mainHash, str[ind - 1], str[ind - 1 + subLen]);
    }
    return static_cast<size_t>(-1);
}

/// Поиск подстроки в строке алгоритмом Кнута—Морриса—Пратта
size_t kmp_find(const std::string &str, const std::string &substr) {
    size_t subLen = substr.length();
    std::vector<size_t> steps(subLen);
    steps[0] = 0;
    for (size_t k = 0, i = 1; i < subLen; i++) {
        while ((k > 0) && (substr[i] != substr[k]))
            k = steps[k - 1];
        if (substr[i] == substr[k])
            k++;
        steps[i] = k;
    }
    for (size_t k = 0, i = 0; i < str.length(); i++) {
        while ((k > 0) && (substr[k] != str[i]))
            k = steps[k - 1];
        if (substr[k] == str[i])
            k++;
        if (k == subLen)
            return (i - subLen + 1);
    }
    return static_cast<size_t >(-1);
}
