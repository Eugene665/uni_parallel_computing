#include <iostream>
using namespace std;

// Функция для обмена значений без затирки
void Swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}


class Sort {
public:
  //Виртуальный метод, который в последствии будет переопределён
    virtual void sort(int* arr, int length_arr) = 0;
};

class BubbleSort : public Sort {
public:
  // Переопределение функции
  void sort(int* arr, int length_arr) override {
    // Проходим по всему списку
    for (int i = 0; i < length_arr - 1; i++){
      // Проходим по списку до отсортированной части, 
      // до чисел, которые уже "всплыли"
      for (int j = 0; j < length_arr - i - 1; j++){
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
    void sort(int* arr, int length_arr) override{
      int left_pose = 1;
      int right_pose = length_arr - 1;
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
    
    /*
    // Обозначение переменной для длины массива и её ввод от пользователя
    int length_arr;
    cout << "Введите длину массива: ";
    cin >> length_arr;

    // Обозначение массива и ввод содержимого от пользователя
    int arr[length_arr];
    cout << "Введите числа для массива через пробел: ";
    for (int i = 0; i < length_arr; i++){
      cin >> arr[i];
    }
    */

    // Исходный массив
    int length_arr = 5;
    int arr[length_arr]{6, 10, 1, 3, 2};

    // Вывод исходного массива
    cout << "Исходный массив\n";
    for (int i = 0; i < length_arr; i++){
      cout << arr[i] << " ";
    }
    cout << "\n\n";

    //BubbleSort---------------------------------------
    // Копирования массива для сортировки пузырьком
    int bubble_arr[length_arr];
    for (int i = 0; i < length_arr; i++){
      bubble_arr[i] = arr[i];
    }

    // Вывод массива до сортировки
    cout << "Массив до сортировки пузырьком\n";
    for (int i = 0; i < length_arr; i++)
        cout << bubble_arr[i] << " ";
    cout << "\n";

    // Создание объекта BubbleSort 
    BubbleSort sorter_bubble;
    // Вызов метода сортировки
    sorter_bubble.sort(bubble_arr, length_arr);

    // Вывод отсортированного массива
    cout << "После сортировки пузырьком\n";
    for (int i = 0; i < length_arr; i++)
        cout << bubble_arr[i] << " ";
    cout << "\n\n";

    //ShakerSort-------------------------------------------
    // Копирования массива для сортировки шейкером
    int shaker_arr[length_arr];
    for (int i = 0; i < length_arr; i++){
      shaker_arr[i] = arr[i];
    }

    // Вывод массива до сортировки
    cout << "До сортировки шейкером\n";
    for (int i = 0; i < length_arr; i++)
        cout << shaker_arr[i] << " ";
    cout << "\n";

    // Создание объекта ShakerSort
    ShakerSort sorter_shaker;
    // Вызов метода сортировки
    sorter_shaker.sort(shaker_arr, length_arr);

    // Вывод отсортированного вектора
    cout << "После сортировки шейкером\n";
    for (int i = 0; i < length_arr; i++)
        cout << bubble_arr[i] << " ";
    cout << "\n\n";
    
    return 0;
}

