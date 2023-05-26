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

/*stats qsortRecursive(vector<int>& obj, int size) {
    //Указатели в начало и в конец массива
    stats values{ 0,0 };
    size = obj.size();
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = obj[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (obj[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (obj[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = obj[i];
            obj[i] = obj[j];
            obj[j] = tmp;
            values.copy_count += 3;

            i++;
            j--;
        }
        ++values.comparison_count;

    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        qsortRecursive(obj, j + 1);
    }
    if (i < size) {
        //"Правый кусок"
        qsortRecursive((vector<int>&)obj[i], obj.size() - i);
    }
    return values;
}*/

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

typedef stats(*func)(std::vector<int>& a);

stats avg_stats(int count, func f) {
    stats result;
    for (int i = 0; i < 100; ++i) {
        std::vector<int> tmp;
        completion(tmp, count);
        //result += f(tmp) / 100;
    }

    return result;
}

int main() {

    std::cout << "bubble sorting:\n";
    std::cout << "average values for 100 rundom arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        stats avg_val = avg_stats(i * 1000, &insert_sort);
        std::cout << "\n" << i << "000 values: ";
        avg_val.print();
    }

    std::cout << "\nvalues for sorted arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        std::vector<int> v;
        completion(v, i * 1000);
        insert_sort(v);
        stats result = insert_sort(v);
        std::cout << "\n" << i << "000 values: ";
        result.print();
    }

    std::cout << "\nvalues for back sorted arrays: ";

    for (int i = 25; i <= 100; i *= 2) {
        std::vector<int> v;
        completion(v, i * 1000);
        back_sorting(v);
        stats result = insert_sort(v);
        std::cout << "\n" << i << "000 values: ";
        result.print();
    }

    return 0;
}

