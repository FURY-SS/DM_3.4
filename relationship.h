#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

const int M[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //


// функция всегда возвращает false
bool f_false(const int &x, const int &y) {
    return false;
}


// отношение A с условием
bool f1(const int &x, const int &y) {
    return abs(x - y) % 5 == 0;
}

// отношение B с условием
bool f2(const int &x, const int &y) {
    return (x > 2 && x < 8) || (y > 2 && y < 8);
}

// отношение C с условием
bool f3(const int &x, const int &y) {
    return (x*x + y*y) < 100;
}


// функция создания матрицы отношения
vector<vector<int>> create_matrix_relationship(bool (f)(const int&, const int&)) {
    vector<vector<int>> matrix;

    for (auto _: M) {
        vector<int> row;

        for (auto _: M)
            row.push_back(0);

        matrix.push_back(row);
    }

    for (int x: M)
        for (int y: M)
            if (f(x,y))
                matrix[x][y] = 1;

    return matrix;
}

// функция  вывода  матрицы  отношения
void print_matrix2(const vector<vector<int>>& matrix) {
    for (const auto& row: matrix) {
        for (auto val: row) {
            cout << val << " \\!&\\! ";
        }
        cout << "\b\b\b\b\b\b \\\\"<< endl;
    }

    cout << endl;
}


// функция  вывода  матрицы  отношения
void print_matrix(const vector<vector<int>>& matrix) {
    for (const auto& row: matrix) {
        for (auto val: row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << endl;
}


// Функция объединения отношений
vector<vector<int>> union_relationship(const vector<vector<int>> &relationship1,
                                       const vector<vector<int>> &relationship2) {
    vector<vector<int>> result = relationship1;
    auto relation_len = relationship1[0].size();

    for(size_t x = 0; x < relation_len; x++) {
        for(size_t y = 0; y < relation_len; y++) {
            if(result[x][y])
                continue;

            if(relationship2[x][y])
                result[x][y] = 1;
        }
    }

    return result;
}

// Функция пересечения отношений
vector<vector<int>> intersection_relationship(const vector<vector<int>> &relationship1,
                                              const vector<vector<int>> &relationship2) {
    vector<vector<int>> result = relationship1;
    auto relation_len = relationship1[0].size();

    for(size_t x = 0; x < relation_len; x++)
        for(size_t y = 0; y < relation_len; y++) {
            if(result[x][y] && relationship2[x][y])
                continue;

            result[x][y] = 0;
        }

    return result;
}

// Функция разности отношений
vector<vector<int>> different_relationship(const vector<vector<int>> &relationship1,
                                           const vector<vector<int>> &relationship2) {
    vector<vector<int>> result = relationship1;
    auto relation_len = relationship1[0].size();

    for(size_t x = 0; x < relation_len; x++) {
        for(size_t y = 0; y < relation_len; y++) {
            if(result[x][y] && relationship2[x][y])
                result[x][y] = 0;
        }
    }

    return result;
}

// Функция симметрической разности отношений
vector<vector<int>> symmetric_different_relationship(const vector<vector<int>> &relationship1,
                                                     const vector<vector<int>> &relationship2) {
    vector<vector<int>> result;
    auto relation_len = relationship1[0].size();

    for (size_t i = 0; i < relation_len; i++) {
        vector<int> row;
        for (size_t j = 0; j < relation_len; j++)
            row.push_back(0);
        result.push_back(row);
    }

    for(size_t x = 0; x < relation_len; x++)
        for(size_t y = 0; y < relation_len; y++)
            if(relationship1[x][y] && !relationship2[x][y] ||
               !relationship1[x][y] && relationship2[x][y])
                result[x][y] = 1;

    return result;
}

// Функция дополнения
vector<vector<int>> complement_relationship(const vector<vector<int>> &relationship) {
    vector<vector<int>> result;
    auto relation_len = relationship[0].size();

    for (size_t i = 0; i < relation_len; i++) {
        vector<int> row;
        for (size_t j = 0; j < relation_len; j++)
            row.push_back(0);
        result.push_back(row);
    }

    for(size_t x = 0; x < relation_len; x++)
        for(size_t y = 0; y < relation_len; y++)
            if(!relationship[x][y])
                result[x][y] = 1;

    return result;
}

// Функция обращения
vector<vector<int>> reverse_relationship(const vector<vector<int>> &relationship) {
    vector<vector<int>> result;
    auto relation_len = relationship[0].size();

    for (size_t i = 0; i < relation_len; i++) {
        vector<int> row;
        for (size_t j = 0; j < relation_len; j++)
            row.push_back(0);
        result.push_back(row);
    }

    for(size_t x = 0; x < relation_len; x++)
        for(size_t y = 0; y < relation_len; y++)
            if(relationship[y][x])
                result[x][y] = 1;

    return result;
}

// Функция композиции отношений
vector<vector<int>> compose_relationship(const vector<vector<int>> &relationship1,
                                         const vector<vector<int>> &relationship2) {
    vector<vector<int>> result;
    auto relation_len = relationship1[0].size();

    for (size_t i = 0; i < relation_len; i++) {
        vector<int> row;
        for (size_t j = 0; j < relation_len; j++)
            row.push_back(0);
        result.push_back(row);
    }

    for(size_t x = 0; x < relation_len; x++)
        for(size_t y = 0; y < relation_len; y++)
            for(size_t z = 0; z < relation_len; z++) {
                if(relationship1[x][z] && relationship2[z][y]) {
                    result[x][y] = 1;
                }
            }
    return result;
}

// Функция возведения в степень отношения
vector<vector<int>> degree_relationship(vector<vector<int>> relationship, const int degree) {
    if(degree == 1)
        return relationship;

    if(degree > 1) {
        vector<vector<int>> result = relationship;

        for(auto i = 1; i < degree; i++)
            result = compose_relationship(result, relationship);

        return result;
    }

    vector<vector<int>> empty_relationship;
    auto relation_len = relationship[0].size();

    for (size_t i = 0; i < relation_len; i++) {
        vector<int> row;
        for (size_t j = 0; j < relation_len; j++)
            row.push_back(0);
        empty_relationship.push_back(row);
    }

    return empty_relationship;
}

// Проверяет рефлексивно ли отношение
bool is_relationship_reflexive(const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for(size_t x = 0; x < relation_len; x++)
        if(!relationship[x][x]) {
            if (report)
                cout << "Отношение не рефлексивно потому, что пара (" << x << ", " << x << ") не принадлежит отношению" << endl;

            return false;
        }

    if (report)
        cout << "Отношение рефлексивно" << endl;

    return true;
}

// Проверяет антирефлексивно ли отношение
bool is_relationship_antireflexive(const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for(size_t x = 0; x < relation_len; x++) {
        if(relationship[x][x]) {
            if (report)
                cout << "Отношение не антирефлексивно потому, что пара (" << x << ", " << x << ") принадлежит отношению" << endl;

            return false;
        }
    }

    if (report)
        cout << "Отношение антирефлексивно" << endl;

    return true;
}

// Проверяет симметрично ли отношение
bool is_relationship_symmetrical(const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for(size_t x = 0; x < relation_len; x++)
        for(size_t y = 0; y < relation_len; y++) {
            if(x == y)
                continue;

            if(relationship[x][y] && !relationship[y][x]) {
                if (report){
                    cout << "Отношение не симметрично потому, что пара (" << x << ", " << y << ") принадлежит отношению, а пара ("
                         << y << ", " << x << ") - не принадлежит" << endl;
                }

                return false;
            }
        }

    if (report)
        cout << "Отношение симметрично" << endl;

    return true;
}

// Проверяет антисимметрично ли отношение
bool is_relationship_antisymmetrical(const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for(size_t x = 0; x < relation_len; x++) {
        for(size_t y = 0; y < relation_len; y++) {
            if (x == y)
                continue;

            if (relationship[x][y] && relationship[y][x]){
                if (report){
                    cout << "Отношение не антисимметрично потому, что пара (" << x << ", " << y << ") принадлежит отношению и пара ("
                         << y << ", " << x << ") тоже принадлежит отношению, а " << x << " не равно " << y << endl;
                }

                return false;
            }
        }
    }

    if (report)
        cout << "Отношение симметрично" << endl;

    return true;
}

// Проверяет транзитивно ли отношение
bool is_relationship_transitive (const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for (size_t x = 0; x < relation_len; x++){
        for (size_t y = 0; y < relation_len; y++){
            for (size_t z = 0; z < relation_len; z++){
                if (relationship[x][z] && relationship[z][y] && !relationship[x][y]){
                    if (report){
                        cout << "Отношение не транзитивно потому, что пары (" << x << ", " << z << ") и ("
                             << z << ", " << y << ") принадлежат отношению, а пара ("
                             << x << ", " << y << ") не принадлежит отношению" << endl;
                    }

                    return false;
                }
            }
        }
    }

    if (report)
        cout << "Отношение транзитивно" << endl;

    return true;
}

// Проверяет антитранзитивно ли отношение
bool is_relationship_antitransitive (const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for (size_t x = 0; x < relation_len; x++){
        for (size_t y = 0; y < relation_len; y++){
            for (size_t z = 0; z < relation_len; z++){
                if (relationship[x][z-1] && relationship[z-1][y] && relationship[x][y]){
                    if (report){
                        cout << "Отношение не антитранзитивно потому, что пары (" << x << ", " << z << "), ("
                             << z << ", " << y << "), (" << x << ", " << y << ") принадлежат отношению" << endl;
                    }

                    return false;
                }
            }
        }
    }

    if (report)
        cout << "Отношение антитранзитивно" << endl;

    return true;
}

// Проверяет полно ли отношение
bool is_relationship_complete (const vector<vector<int>> &relationship, const bool report) {
    auto relation_len = relationship[0].size();
    for (size_t x = 0; x < relation_len; x++){
        for (size_t y = 0; y < relation_len; y++){
            if (x == y)
                continue;

            if (!relationship[x][y] && !relationship[y][x]){
                if (report)
                    cout << "Отношение не полно потому, что в нем нет пар (" << x << ", " << y << ") и (" << y << ", " << x << ")" << endl;

                return false;
            }
        }
    }

    if (report)
        cout << "Отношение полно" << endl;

    return true;
}

// Проверяет отношение на произвольные свойства
void print_derived_properties_relationships(const vector<vector<int>> &relationship) {
    const bool report = false;

    const bool tolerance = is_relationship_reflexive(relationship, report) && is_relationship_symmetrical(relationship, report);
    const bool equivalence = is_relationship_reflexive(relationship, report) && is_relationship_symmetrical(relationship, report) &&
                             is_relationship_transitive(relationship, report);
    const bool order = is_relationship_antisymmetrical(relationship, report) && is_relationship_transitive(relationship, report);
    const bool non_strict_order = order && is_relationship_reflexive(relationship, report);
    const bool strict_order = order && is_relationship_antireflexive(relationship, report);
    const bool linear_order = order && is_relationship_complete(relationship, report);
    const bool non_strict_linear_order = non_strict_order && is_relationship_complete(relationship, report);
    const bool strict_linear_order = strict_order && is_relationship_complete(relationship, report);

    cout << "Имеет ли отношение свойство:" << endl;
    cout << "Толерантности: " << tolerance << endl;
    cout << "Эквивалентности: " << equivalence << endl;
    cout << "Порядка: " << order << endl;
    cout << "Нестрогого порядка: " << non_strict_order << endl;
    cout << "Строгого порядка: " << strict_order << endl;
    cout << "Линейного порядка: " << linear_order << endl;
    cout << "Нестрогого линейного порядка: " << non_strict_linear_order << endl;
    cout << "Строгого линейного порядка: " << strict_linear_order << endl;

    cout << endl;
}


bool is_enabled_relationship(const vector<vector<int>> &relationship1, const vector<vector<int>> &relationship2){
    int  count = 0;
    auto relation_len = relationship1[0].size();
    for (size_t x = 0; x < relation_len; x++)
        for (size_t y = 0; y < relation_len; y++){
            count++;
            if(relationship1[x][y] > relationship2[x][y])
                return false;
        }
    return true;
}

vector<vector<int>> get_init(size_t n) {
    vector<vector<int>> result;
    for (size_t i = 0; i < n; i++) {
        vector<int> row;
        for(size_t j = 0; j < n; j++)
            row.push_back(0);
        result.push_back(row);
    }

    for (size_t x = 0; x < n; x++) {
        result[x][x] = 1;
    }
    return result;
}

#endif //RELATIONSHIP_H
