// #include <iostream>
// #include <mutex>

// using namespace std;

// class Singleton {
// private:
//     static Singleton* instance;
//     static mutex mtx;

//     Singleton() {
//         cout << "Singleton constructor called. New object created." << endl;
//     }

//     // Prevent copying
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;

// public:
//     static Singleton* getInstance() {
//         if (instance == nullptr) {
//             lock_guard<mutex> lock(mtx);

//             if (instance == nullptr) {
//                 instance = new Singleton();
//             }
//         }
//         return instance;
//     }
                                                            
//     void showMessage() {
//         cout << "Singleton object is being used." << endl;
//     }
// };

// // Initialize static members
// Singleton* Singleton::instance = nullptr;
// mutex Singleton::mtx;

// int main() {
//     Singleton* s1 = Singleton::getInstance();
//     Singleton* s2 = Singleton::getInstance();

//     s1->showMessage();
//     s2->showMessage();

//     if (s1 == s2) {
//         cout << "Both pointers point to the same instance." << endl;
//     }

//     return 0;
// }