


#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include <random>

// Функция для генерации массива случайных чисел
std::vector<int> generateArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    return arr;
}

// Пузырьковая сортировка
void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Сортировка вставками
void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Обертка для замера времени сортировки
void sortAndMeasureTime(const std::string& sortName, std::vector<int> arr, void(*sortFunc)(std::vector<int>&)) {
    auto start = std::chrono::high_resolution_clock::now();
    
    sortFunc(arr);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    std::cout << sortName << " завершена за " << duration.count() << " секунд.\n";
}

int main() {
    const int arraySize = 100000;

    // Генерируем массивы
    std::vector<int> arr1 = generateArray(arraySize);
    std::vector<int> arr2 = arr1;  // Копия для другой сортировки
    std::vector<int> arr3 = arr1;  // Копия для третьей сортировки

    // Запуск сортировок в разных потоках
    std::thread thread1(sortAndMeasureTime, "Пузырьковая сортировка", arr1, bubbleSort);
    std::thread thread2(sortAndMeasureTime, "Сортировка вставками", arr2, insertionSort);
    
    std::thread thread3(sortAndMeasureTime, "Сортировка вставками", arr3, insertionSort);


    // Ожидание завершения всех потоков
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}




/*
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void DoWork(){

  setlocale(LC_ALL, "ru");

  for (int i = 0; i < 10; i++){
    cout << "id потока " << this_thread::get_id()<< "\t dowork \n";
    this_thread::sleep_for(chrono::milliseconds(1000));
  }

}

void DoWork2(){

for (int i = 0; i < 10; i++){
  cout << "id потока " << this_thread::get_id() << "\t dowork 2 \n";
  this_thread::sleep_for(chrono::milliseconds(750));
}

}

int main(){
  setlocale(LC_ALL, "ru");

  thread th(DoWork);
  thread th2(DoWork2);
  //DoWork();

  for (int i = 0; i < 10; i++){
    cout << "id потока " << this_thread::get_id()<< "\t main \n";
    this_thread::sleep_for(chrono::milliseconds(500));
  }

  th.join();
  th2.join();
  return 0;
}
*/
