/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>

#include <string>
using namespace std;

// Nommons notre type pour plus de facilité d'écriture
using int_tab_t = std::vector< int >;

void print_tab(const int_tab_t &table) {
    string tab = "[ ";
    for (int i = 0; i < table.size(); i++) {
        tab = tab + std::to_string(table[i]) + " ";
    }
    std::cout << tab << "]" << std::endl;
}

void test_11() {
    std::cout << "*** test_11 ***" << std::endl;
    const int_tab_t tab{ 1, -2, 3, -4, 5, -6 };
    print_tab(tab);
}

void random_tab(int_tab_t &tab) {
    for (int i = 0; i < tab.size(); i++) {
        int random_variable = std::rand();
        int sign = std::rand() % 2;
        if (sign == 1) {
            tab[i] = random_variable % 11;
        }
        else {
            tab[i] = - random_variable % 11;
        }
    }
}

void test_12() {
    std::cout << "*** test_12 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
}

void sort_tab_1(int_tab_t &tab) {
    int n = tab.size();
    for (int i = 0; i < n-1; i++) {
        int ind_min = i;
        for (int j = i+1; j < n; j++) {
            if (tab[j] < tab[ind_min]) {
                ind_min = j;
            }
        }
        if (ind_min != i) {
            std::swap(tab[i], tab[ind_min]);
        }
    }
}

void test_13() {
    std::cout << "*** test_13 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
    sort_tab_1(tab);
    print_tab(tab);
}

bool less_f(int a, int b) {  // on ne peut pas l'appeler "less" (renvoie erreur)
    return (a < b);
}

bool greater_f(int a, int b) {  // on ne peut pas l'appeler "greater" (renvoie erreur)
    return (a > b);
}

void sort_tab_2(int_tab_t &tab, bool (*comp)(int, int)) {
    int n = tab.size();
    for (int i = 0; i < n-1; i++) {
        int ind_min = i;
        for (int j = i+1; j < n; j++) {
            if (comp(tab[j], tab[ind_min])) {
                ind_min = j;
            }
        }
        if (ind_min != i) {
            std::swap(tab[i], tab[ind_min]);
        }
    }
}

void test_14() {
    std::cout << "*** test_14 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
    sort_tab_2(tab, &less_f);
    print_tab(tab);
    sort_tab_2(tab, &greater_f);
    print_tab(tab);
}

void sort_tab_3(int_tab_t &tab, std::function<bool(const int, const int)> comp) {
    int n = tab.size();
    for (int i = 0; i < n-1; i++) {
        int ind_min = i;
        for (int j = i+1; j < n; j++) {
            if (comp(tab[j], tab[ind_min])) {
                ind_min = j;
            }
        }
        if (ind_min != i) {
            std::swap(tab[i], tab[ind_min]);
        }
    }
}

void test_15() {
    std::cout << "*** test_15 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
    auto less_lambda = [](int a, int b) { return a < b; };
    sort_tab_3(tab, less_lambda);
    print_tab(tab);
    auto greater_lambda = [](int a, int b) { return a > b; };
    sort_tab_3(tab, greater_lambda);
    print_tab(tab);
}

int main()
{
    std::srand( std::time( nullptr ));
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();
    return 0;
}

