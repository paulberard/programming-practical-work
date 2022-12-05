/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>
#include <string>
using namespace std;

#include <cstdlib>
#include <ctime>

// Type liste unidirectionnelle d'entiers
using int_list_t = std::forward_list< int >;

using int_list_iter_t = int_list_t::const_iterator;

int_list_t random_list(int n) {
    if (n <= 0) {
        std::cout << "n must be >0" << std::endl;
        return {};
    }
    int_list_t list;
    for (int i = 0; i < n; i++) {
        int rand_num = std::rand()%100;
        list.push_front(rand_num);
    }
    return list;
}

void print_list(const int_list_t &list) {
    string list_str = "( ";
    for (auto i : list) {
        list_str = list_str + std::to_string(i) + " ";
    }
    std::cout << list_str << ")" << std::endl;
}

void test_21() {
    std::cout << "*** test_21 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);

}

int_list_t map_iter(const int_list_t &list, std::function<int(const int)> func) {
    int_list_t new_list;
    for (auto i : list) {
        new_list.push_front(func(i));
    }
    return new_list;
}

void test_22() {
    std::cout << "*** test_22 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    list = map_iter(list, [](int a) { return 3*a; });
    print_list(list);
}

int_list_t filter_iter(const int_list_t &list, std::function<bool(const int)> func) {
    int_list_t new_list;
    for (auto i : list) {
        if (func(i)) {
            new_list.push_front(i);
        }
    }
    return new_list;
}

void test_23() {
    std::cout << "*** test_23 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    list = map_iter(list, [](int a) { return 3*a; });
    print_list(list);
    list = filter_iter(list, [](int a) { return a%2 == 0; });
    print_list(list);
}

void test_24() {
    std::cout << "*** test_24 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int rand_mult = std::rand()%5 + 1;
    std::cout << "Random coefficient: " << rand_mult << std::endl;
    list = map_iter(list, [rand_mult](int a) { return rand_mult*a; });
    print_list(list);
    list = filter_iter(list, [](int a) { return a%2 == 0; });
    print_list(list);
}

int reduce(const int_list_t &list, int n, std::function<int(const int, const int)> func) {
    int current = n;
    for (auto i : list) {
        current = func(current, i);
    }
    return current;
}

void test_25() {
    std::cout << "*** test_25 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int min_ = reduce(list, std::numeric_limits<int>::max(), [](int a, int b) { if (a < b) { return a; } else { return b; } });
    std::cout << "Minimum element in list: " << min_ << std::endl;
    int max_ = reduce(list, std::numeric_limits<int>::min(), [](int a, int b) { if (a > b) { return a; } else { return b; } });
    std::cout << "Maximum element in list: " << max_ << std::endl;
}

int fold_left_aux(int_list_iter_t iter_current, int_list_iter_t iter_end, int current, std::function<int(const int, const int)> func) {
    if (iter_current == iter_end) {
        return current;
    }
    else {
        int new_value = func(current, *iter_current);
        return fold_left_aux(std::next(iter_current, 1), iter_end, new_value, func);
    }
}

int fold_left(const int_list_t &list, int n, std::function<int(const int, const int)> func) { 
    return fold_left_aux(list.begin(), list.end(), n, func);
}

void test_31() {
    std::cout << "*** test_31 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int min_ = fold_left(list, std::numeric_limits<int>::max(), [](int a, int b) { if (a < b) { return a; } else { return b; } });
    std::cout << "Minimum element in list: " << min_ << std::endl;
    int max_ = fold_left(list, std::numeric_limits<int>::min(), [](int a, int b) { if (a > b) { return a; } else { return b; } });
    std::cout << "Maximum element in list: " << max_ << std::endl;
}

void map_aux(int_list_t &list, int_list_iter_t iter_current, int_list_iter_t iter_end, std::function<int(const int)> func) {
    if (iter_current == iter_end) {
        return ;
    }
    else {
        list.push_front(func(*iter_current));
        map_aux(list, next(iter_current, 1), iter_end, func);
    }
}

int_list_t map(const int_list_t &list, std::function<int(const int)> func) {
    int_list_t out_list;
    map_aux(out_list, list.begin(), list.end(), func);
    return out_list;
}

void filter_aux(int_list_t &list, int_list_iter_t iter_current, int_list_iter_t iter_end, std::function<bool(const int)> func) {
    if (iter_current == iter_end) {
        return ;
    }
    else {
        if (func(*iter_current)) {
            list.push_front(*iter_current);
        }
        filter_aux(list, next(iter_current, 1), iter_end, func);
    }
}

int_list_t filter(const int_list_t &list, std::function<bool(const int)> func) {
    int_list_t out_list;
    filter_aux(out_list, list.begin(), list.end(), func);
    return out_list;
}

void test_32() {
    std::cout << "*** test_32 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int rand_mult = std::rand()%5 + 1;
    std::cout << "Random coefficient: " << rand_mult << std::endl;
    list = map(list, [rand_mult](int a) { return rand_mult*a; });
    print_list(list);
    list = filter(list, [](int a) { return a%2 == 0; });
    print_list(list);
}

void test_41() {
    std::cout << "*** test_41 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int rand_mult = std::rand()%5 + 1;
    std::cout << "Random coefficient: " << rand_mult << std::endl;
    std::multiplies< int > multiply_func;
    auto mult_lambda = [rand_mult, multiply_func](int a) { return multiply_func(rand_mult, a); };
    list = map(list, mult_lambda);
    print_list(list);
    list = filter(list, [](int a) { return a%2 == 0; });
    print_list(list);
}

int fold_right_aux(int_list_iter_t iter_current, int_list_iter_t iter_end, int current, std::function<int(const int, const int)> func) {
    if (iter_current == iter_end) {
        return current;
    }
    else {
        return fold_right_aux(std::next(iter_current, 1), iter_end, func(current, *iter_current), func);
    }
}

int fold_right(const int_list_t &list, int n, std::function<int(const int, const int)> func) { 
    return fold_right_aux(list.begin(), list.end(), n, func);
}

// Tentative test_42(). Pour vérifier que fold_left et fold_right ne donnent pas toujours le même résultat, 
// il faudrait peut-être essayer avec une autre fonction func pour la réduction.
void test_42() {
    std::cout << "*** test_42 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int min_fl = fold_left(list, std::numeric_limits<int>::max(), [](int a, int b) { if (a < b) { return a; } else { return b; } });
    std::cout << "Minimum element in list (fold_left): " << min_fl << std::endl;
    int max_fl = fold_left(list, std::numeric_limits<int>::min(), [](int a, int b) { if (a > b) { return a; } else { return b; } });
    std::cout << "Maximum element in list (fold_left): " << max_fl << std::endl;
    int min_fr = fold_right(list, std::numeric_limits<int>::max(), [](int a, int b) { if (a < b) { return a; } else { return b; } });
    std::cout << "Minimum element in list (fold_right): " << min_fr << std::endl;
    int max_fr = fold_right(list, std::numeric_limits<int>::min(), [](int a, int b) { if (a > b) { return a; } else { return b; } });
    std::cout << "Maximum element in list (fold_right): " << max_fr << std::endl;
}

int main()
{
    std::srand( std::time( nullptr ));
    test_21();
    test_22();
    test_23();
    test_24();
    test_25();
    test_31();
    test_32();
    test_41();
    test_42();
    return 0;
}

