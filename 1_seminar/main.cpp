#include <iostream>
using namespace std;

void Swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}


class Sort {  // Переименуем класс для избегания конфликта имен
public:
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

/*
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
*/
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

    // Копирования массива для сортировки пузырьком
    int bubble_arr[length_arr];
    for (int i = 0; i < length_arr; i++){
      bubble_arr[i] = arr[i];
    }

    // Вывод массива до сортировки
    for (int i = 0; i < length_arr; i++)
        cout << bubble_arr[i] << " ";
    cout << "\n";

    // Создание объекта BubbleSort 
    BubbleSort sorter_bubble;
    // Вызов метода сортировки
    sorter_bubble.sort(bubble_arr, length_arr);

    cout << "Сортировка пузырьком\n";
    // Вывод отсортированного вектора
    for (int i = 0; i < length_arr; i++)
        cout << bubble_arr[i] << " ";
    cout << "\n";

    /*
    //ShakerSort-------------------------------------------
    int arr_2[5]{6, 10, 1, 3, 2};  // Создание вектора

    
    // Вывод вектора о сортировки
    for (int i = 0; i < length_arr; i++)
        cout << arr_1[i] << " ";
    cout << "\n";

    ShakerSort sorter_shaker;  // Создание объекта BubbleSort
    sorter_shaker.sort(arr_1, length_arr);   // Вызов метода сортировки

    // Вывод отсортированного вектора
    for (int i = 0; i < length_arr; i++)
        cout << arr_1[i] << " ";
    cout << "\n";
    */
    return 0;
}

