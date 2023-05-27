#include <iostream>
#include <vector>

using namespace std;

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;

    void print() {
        std::cout << "\nNumber of copies: " << copy_count
            << "\nNumber of comparisons: " << comparison_count << std::endl;
    }

    stats operator+=(const stats& right) {
        comparison_count += right.comparison_count;
        copy_count += right.copy_count;

        return *this;
    }

    stats operator/(int val) {
        comparison_count /= val;
        copy_count /= val;

        return *this;
    }
};

stats insert_sort(vector<int>& obj) {
    stats values{ 0,0 };
    for (int i = 1; i < obj.size(); ++i) {
        int j = i;
        while ((j > 0) && (obj[j - 1] > obj[j])) {
            int tmp = obj[j];
            obj[j] = obj[j - 1];
            obj[j - 1] = tmp;
            j--;
            values.copy_count += 3;
        }
        ++values.comparison_count;
    }
    return values;
}

void quick_sort(vector<int>& arr, size_t left, size_t right) {
    int i = left, j = right;
    stats values{ 0,0 };
    int pivot = arr[(left + right) / 2];

    /* partition */
    do {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            values.copy_count += 3;
            i++;
            j--;
        }
        ++values.comparison_count;
    } while (i <= j);

    /* recursion */
    if (left < j)
        quick_sort(arr, left, j);
    if (i < right)
        quick_sort(arr, i, right);

}

void back_sorting(std::vector<int>& obj) {
    for (int i = 1; i < obj.size(); ++i) {
        int j = i;
        while ((j > 0) && (obj[j - 1] < obj[j])) {
            int tmp = obj[j];
            obj[j] = obj[j - 1];
            obj[j - 1] = tmp;
            j--;
        }
    }
    return;
}

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void completion(std::vector<int>& obj, int count) {
    for (int i = 0; i < count; ++i) {
        obj.push_back(lcg());
    }
}

stats avg_stats_insert(int count) {
    stats result;
    for (int i = 0; i < 100; ++i) {
        std::vector<int> tmp;
        completion(tmp, count);
        result += insert_sort(tmp) / 100;
    }

    return result;
}

stats avg_stats_quick(int count) {
    stats result;
    for (int i = 0; i < 100; ++i) {
        std::vector<int> tmp;
        completion(tmp, count);
        int quantity = count - 1;
        //result += quick_sort(tmp, 0, static_cast<size_t>(count) - 1) / 100;
    }

    return result;
}

int main() {
    std::vector<int> temp;
    completion(temp, 10);
    for (int i = 0; i < temp.size(); ++i) {
        cout << temp[i] << " ";
    }
    cout << "\n";
    quick_sort(temp, 0, 9);
    for (int i = 0; i < temp.size(); ++i) {
        cout << temp[i] << " ";
    }
    /*std::cout << "Sorting by inserts:\n";
    std::cout << "Average values for 100 random arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        stats avg_values = avg_stats_insert(i * 1000);
        std::cout << "\n" << i << "000 values: ";
        avg_values.print();
    }

    std::cout << "\nValues for sorted arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        std::vector<int> v;
        completion(v, i * 1000);
        insert_sort(v);
        stats result = insert_sort(v);
        std::cout << "\n" << i << "000 values: ";
        result.print();
    }

    std::cout << "\nValues for back sorted arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        std::vector<int> v;
        completion(v, i * 1000);
        back_sorting(v);
        stats result = insert_sort(v);
        std::cout << "\n" << i << "000 values: ";
        result.print();
    }

    std::cout << "Quick sort:\n";
    std::cout << "Average values for 100 random arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        //stats avg_values = avg_stats(i * 1000);
        std::cout << "\n" << i << "000 values: ";
        avg_values.print();
    }

    std::cout << "\nValues for sorted arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        std::vector<int> v;
        completion(v, i * 1000);
        quick_sort(v);
        //stats result = quick_sort(v, 0, static_cast<size_t>(i) * 1000 - 1);
        std::cout << "\n" << i << "000 values: ";
        result.print();
    }

    std::cout << "\nValues for back sorted arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        std::vector<int> v;
        completion(v, i * 1000);
        back_sorting(v);
        //stats result = quick_sort(0, static_cast<size_t>(i) * 1000 - 1);
        std::cout << "\n" << i << "000 values: ";
        result.print();
    }*/

    return 0;
}

