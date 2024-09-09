
#include <iostream>
using namespace std;

void Swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}


class Sort {  // Переименуем класс для избегания конфликта имен
public:
    virtual void sort(vector<int>& arr) = 0; // Изменено имя метода
};

class BubbleSort : public Sort {
public:
  // Переопределение функции
    void sort(vector<int>& arr) override {
        int size = arr.size()
        // Проходим по всему списку
        for (int i = 0; i < size - 1; i++) {
        // Проходим списку без последних элементов,
        // которые уже "всплыли"
          for (int j = 0; j < size - i - 1; j++) {
              // Если 
                if (arr[j] > arr[j + 1]) {
                    Swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

int main() {
    vector<int> vec = {2, 3, 1, 4, 5};  // Создание вектора

    BubbleSort sorter;  // Создание объекта BubbleSort
    sorter.sort(vec);   // Вызов метода сортировки

    // Вывод отсортированного вектора
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << "\n"
    return 0;
}

