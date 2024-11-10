#include <iostream>
#include "relationship.h"
#include <windows.h>


struct Point {
    int x, y;

    void print_point() const {
        printf("(%d, %d) ", x, y);
    }
};

bool f(const Point pt1, const Point pt2) {
    return (pt1.x * pt1.x + pt1.y * pt1.y) < (pt2.x * pt2.x + pt2.y * pt2.y);
}

vector<vector<int> > create_relationship_on_points(vector<Point> &m, bool (f)(Point pt1, Point pt2)) {
    vector<vector<int> > result;
    for (int i = 0; i < m.size(); i++) {
        vector<int> row;
        for (int j = 0; j < m.size(); j++)
            row.push_back(0);
        result.push_back(row);
    }


    for (int i = 0; i < m.size(); i++)
        for (int j = 0; j < m.size(); j++) {
            if (f(m[i], m[j])) {
                result[i][j] = 1;
            }
        }
    return result;
}


vector<vector<int> > dominante_relationship(const vector<vector<int> > &relationship) {
    const vector<vector<int> > degree = degree_relationship(relationship, 2);

    vector<vector<int> > result = different_relationship(relationship, degree);

    return result;
}


bool all_element_negative(const vector<int> &vec) {
    for (const auto x: vec)
        if (x >= 0)
            return false;
    return true;
}


vector<int> get_sum_cols(vector<vector<int> > mat) {
    vector<int> sum(mat[0].size(), 0);
    for (int i = 0; i < mat[0].size(); i++) {
        for (int j = 0; j < mat.size(); j++) {
            sum[i] += mat[j][i];
        }
    }

    return sum;
}


vector<int> topology_sort(const vector<vector<int> > &relationship) {
    int i = -1;
    vector<int> w = get_sum_cols(relationship);

    while (!all_element_negative(w)) {
        for (int j = 0; j < w.size(); j++)
            if (w[j] == 0)
                w[j] = i;

        vector<int> index;
        for (int j = 0; j < w.size(); j++)
            if (w[j] == i)
                index.push_back(j);

        for (const auto j: index) {
            for (int k = 0; k < w.size(); k++) {
                w[k] -= relationship[j][k];
            }
        }

        i -= 1;
    }

    return w;
}


vector<size_t> get_index_max_element(const vector<vector<int> > &relationship) {
    vector<size_t> result;
    const size_t relationship_len = relationship[0].size();
    auto cols_sum = vector(relationship_len, 0);

    for (size_t b = 0; b < relationship_len; b++)
        for (size_t x = 0; x < relationship_len; x++)
            cols_sum[b] += relationship[x][b];

    int max_element = -1;
    for (const auto x: cols_sum)
        if (x > max_element)
            max_element = x;

    for (size_t i = 0; i < relationship_len; i++)
        if (cols_sum[i] == max_element)
            result.push_back(i);

    return result;
}


vector<size_t> get_index_min_element(const vector<vector<int> > &relationship) {
    vector<size_t> result;
    const size_t relationship_len = relationship[0].size();
    auto rows_sum = vector(relationship_len, 0);

    for (size_t b = 0; b < relationship_len; b++)
        for (size_t x = 0; x < relationship_len; x++)
            rows_sum[b] += relationship[b][x];

    int max_element = -1;
    for (const auto x: rows_sum)
        if (x > max_element)
            max_element = x;

    for (size_t i = 0; i < relationship_len; i++)
        if (rows_sum[i] == max_element)
            result.push_back(i);

    return result;
}


void print_vector_of_points_by_index(const vector<Point> &m, const vector<size_t> &index) {
    for (const size_t i: index)
        printf("(%d, %d) ", m[i].x, m[i].y);
    std::cout << std::endl;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    using namespace std;

    vector<Point> m1 = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 0},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1},
    };


    vector<Point> m2 = {
            {-2, 0},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -2},
            {0, -1},
            {0, 0},
            {0, 1},
            {0, 2},
            {1, -1},
            {1, 0},
            {1, 1},
            {2, 0}
    };

    // 1 task
    const vector<vector<int> > relationship_m1 = create_relationship_on_points(m1, f);
    const vector<vector<int> > relationship_m2 = create_relationship_on_points(m2, f);
/*
    cout << "Properties M1" << endl;
    print_derived_properties_relationships(relationship_m1);
    cout << "Properties M2" << endl;
    print_derived_properties_relationships(relationship_m2);

    cout << "Relationship M1" << endl;
    print_matrix(relationship_m1);
    cout << "Relationship M2" << endl;
    print_matrix(relationship_m2);
*/
    // 2 task
    const vector<vector<int> > dominant_m1 = dominante_relationship(relationship_m1);
    const vector<vector<int> > dominant_m2 = dominante_relationship(relationship_m2);

    cout << "Dominant M1" << endl;
    print_matrix(dominant_m1);
    cout << "Dominant M2" << endl;
    print_matrix(dominant_m2);
/*
    // 3 task
    vector<int> w_m1 = topology_sort(dominant_m1);
    vector<int> w_m2 = topology_sort(dominant_m2);

    cout << "W M1:" << endl;
    for (const auto x: w_m1)
        cout << -x << " ";
    cout << endl;

    cout << "W M2:" << endl;
    for (const auto x: w_m2)
        cout << -x << " ";
    cout << endl << endl;


    // 5 task
    const vector<size_t> index_max_m1 = get_index_max_element(relationship_m1);
    const vector<size_t> index_min_m1 = get_index_min_element(relationship_m1);
    cout << "Max element in M1: ";
    print_vector_of_points_by_index(m1, index_max_m1);
    cout << "Min element in M1: ";
    print_vector_of_points_by_index(m1, index_min_m1);
    cout << endl;

    const vector<size_t> index_max_m2 = get_index_max_element(relationship_m2);
    const vector<size_t> index_min_m2 = get_index_min_element(relationship_m2);
    cout << "Max element in M2: ";
    print_vector_of_points_by_index(m2, index_max_m2);
    cout << "Min element in M2: ";
    print_vector_of_points_by_index(m2, index_min_m2);
    cout << endl;

*/

    return 0;
}