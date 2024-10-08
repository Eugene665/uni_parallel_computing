#include <time.h>
#include <iostream>
using namespace std;

// Функция для обмена значений без затирки
void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void out_arr_before(int* arr, int length_arr, string name_sort){
    // Вывод массива до сортировки
    cout << "Массив до сортировки " << name_sort << "\n";
    for (int i = 0; i < length_arr; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void out_arr_after(int* arr, int length_arr, string name_sort){
    // Вывод массива после сортировки
    cout << "Массив после сортировки " << name_sort << "\n";
    for (int i = 0; i < length_arr; i++)
        cout << arr[i] << " ";
    cout << "\n";
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
      for (int j = 0; j < length_arr - i - 1; j++) {
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
    void sort(int* arr, int length_arr) override {
      // Вводим переменные позиций на левый и правый 
      // участок неотсортированного массив
      int left_pose = 0;
      int right_pose = length_arr - 1;
      while (left_pose <= right_pose) {
        for (int i = right_pose; i > left_pose; i--) {
          if (arr[i - 1] > arr[i]) {
              Swap(arr[i - 1], arr[i]);
          }
        }
        left_pose++;
        for (int i = left_pose; i < right_pose; i++) {
          if (arr[i] > arr[i + 1]){
            Swap(arr[i], arr[i + 1]);
          }
        }
        right_pose--;
      }
    }
};

class SelectionSort : public Sort{
  public:
    void sort(int* arr, int length_arr) override {
      for (int i = 0; i < length_arr - 1; i++) {
        int smallest_pose = i;
        for (int j = i + 1; j < length_arr; j++) {
          if (arr[j] < arr[smallest_pose]) {
            smallest_pose = j;
          }
        }
        if (smallest_pose != i) {
          Swap(arr[i], arr[smallest_pose]);
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
    int length_arr = 50;
    //int arr[length_arr]{6, 10, 1, 3, 2};
    int arr[length_arr];

    for (int i = 0; i < length_arr; i++){
      int num = 1 + rand() % 20;
      arr[i] = num;
    }

    string flag_out_arr;
    cout << "Хотите выводить массивы до и после сортировки(да/нет): ";
    cin >> flag_out_arr;

    if (flag_out_arr == "да"){
    // Вывод исходного массива
      cout << "Исходный массив\n";
      for (int i = 0; i < length_arr; i++) {
        cout << arr[i] << " ";
      }
    }
    cout << "\n\n\n";

    //BubbleSort---------------------------------------
    // Копирования массива для сортировки пузырьком
    int bubble_arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
      bubble_arr[i] = arr[i];
    }

    if (flag_out_arr == "да"){
      // Вывод массива до сортировки
      out_arr_before(bubble_arr, length_arr, "пузырьком");
    }

    // Создание объекта BubbleSort 
    BubbleSort sorter_bubble;
    // Начало измерения времини
    clock_t start_bubble_sort = clock();
    // Вызов метода сортировки
    sorter_bubble.sort(bubble_arr, length_arr);
    // Окончание измерения времени
    clock_t end_bubble_sort = clock();
    double seconds_bubble_sort = (double)(end_bubble_sort - start_bubble_sort) / CLOCKS_PER_SEC;
    cout << "Затрачено секунд на сортироку пузырьком\n" << seconds_bubble_sort << "\n";
    
    if (flag_out_arr == "да"){
      // Вывод отсортированного массива
      out_arr_after(bubble_arr, length_arr, "пузырьком");
    }
    cout << "\n\n\n";

    //ShakerSort-------------------------------------------
    // Копирования массива для сортировки шейкером
    int shaker_arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
      shaker_arr[i] = arr[i];
    }

    if (flag_out_arr == "да"){
      // Вывод массива до сортировки
      out_arr_before(shaker_arr, length_arr, "шейкером");
    }

    // Создание объекта ShakerSort
    ShakerSort sorter_shaker;
    // Начало измерения времини
    clock_t start_shaker_sort = clock();
    // Вызов метода сортировки
    sorter_shaker.sort(shaker_arr, length_arr);
    // Окончание измерения времени
    clock_t end_shaker_sort = clock();
    double seconds_shaker_sort = (double)(end_shaker_sort - start_shaker_sort) / CLOCKS_PER_SEC;
    cout << "Затрачено секунд на сортироку шейкером\n" << seconds_shaker_sort << "\n";

    if (flag_out_arr == "да"){
      // Вывод отсортированного массива
      out_arr_after(shaker_arr, length_arr, "шейкером");
    }
    cout << "\n\n\n";

    //SelectionSort----------------------------------------
    // Копирования массива для сортировки выбором
    int  selection_arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
      selection_arr[i] = arr[i];
    }

    if (flag_out_arr == "да"){
      // Вывод массива до сортировки
      out_arr_before(selection_arr, length_arr, "выбором");
    }

    // Создание объекта SelectionSort
    SelectionSort sorter_selection;
    // Начало измерения времини
    clock_t start_selection_sort = clock();
    // Вызов метода сортировки
    sorter_selection.sort(selection_arr, length_arr);
    // Окончание измерения времени
    clock_t end_selection_sort = clock();
    double seconds_selection_sort = (double)(end_selection_sort - start_selection_sort) / CLOCKS_PER_SEC;
    cout << "Затрачено секунд на сортироку выбором\n" << seconds_selection_sort << "\n";

    if (flag_out_arr == "да"){
      // Вывод отсортированного массива
      if (flag_out_arr == "да"){
        out_arr_after(selection_arr, length_arr, "выбором");
      }
    }
    cout << "\n\n";
    return 0;
}

