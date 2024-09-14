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

int main(){
  setlocale(LC_ALL, "ru");

  thread th(DoWork);

  //DoWork();

  for (int i = 0; i < 10; i++){
    cout << "id потока " << this_thread::get_id()<< "\t main \n";
    this_thread::sleep_for(chrono::milliseconds(500));
  }

  th.join();

  return 0;
}
