#include <vector>
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
        int size = arr.size();
        // Проходим по всему списку
        for (int i = 0; i < size - 1; i++){
          // Проходим по списку до отсортированной части, 
          // до чисел, которые уже "всплыли"
          for (int j = 0; j < size - i - 1; j++){
            // Если впереди стоящее число меньше,
            // числа меняюся местами
            if (arr[j] > arr[j + 1]) {
              Swap(arr[j], arr[j + 1]);
            }
          }
        }
      }
};


class ShakerSort : public Sort{
  public:
    void sort(vector<int>& arr) override{
      int size = arr.size();
      int left_pose = 1;
      int right_pose = size - 1;
      while (left_pose <= right_pose){
        for (int i = right_pose; i >= left_pose; i--){
          if (arr[i - 1] > arr[i]){
              Swap(arr[i], arr[i + 1]);
          }
          left_pose++;
        }
        for (int i = left_pose; i <= right_pose; i++){
          if (arr[i - 1] > arr[i]){
            Swap(arr[i], arr[i + 1]);
          }
          right_pose--;
        }
      }
    }
};

int main() {

    setlocale(LC_ALL,"Rus");

    vector<int> vec = {6, 10, 1, 3, 2};  // Создание вектора
    // Вывод вектора о сортировки
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << "\n";

    BubbleSort sorter_bubble;  // Создание объекта BubbleSort
    sorter_bubble.sort(vec);   // Вызов метода сортировки
    
    cout << "Сортировка пузырьком\n";
    // Вывод отсортированного вектора
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << "\n";

    //ShakerSort-------------------------------------------
    vec = {6, 10, 1, 3, 2};  // Создание вектора

    // Вывод вектора о сортировки
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << "\n";

    ShakerSort sorter_shaker;  // Создание объекта BubbleSort
    sorter_shaker.sort(vec);   // Вызов метода сортировки

    // Вывод отсортированного вектора
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << "\n";

    return 0;
}

