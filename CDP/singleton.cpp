// #include<bits/stdc++.h>
// #include <mutex>
// using namespace std;

// class Logger {
// private:
//     static Logger* instance;   // Pointer to the single instance
//     static mutex mtx;          // Mutex for thread safety

//     // Private constructor to prevent instantiation
//     Logger() {}

//     // Delete copy constructor and assignment operator
//     Logger(const Logger&) = delete;
//     Logger& operator=(const Logger&) = delete;

// public:
//     static Logger* getInstance() {
//         if (instance == nullptr) {         // First check (no lock)
//             lock_guard<mutex> lock(mtx);   // Lock only when needed
//             if (instance == nullptr) {     // Second check (with lock)
//                 instance = new Logger();
//             }
//         }
//         return instance;
//     }

//     void log(const string& message) {
//         cout << "Log: " << message << endl;
//     }
// };

// // Initialize static members
// Logger* Logger::instance = nullptr;
// mutex Logger::mtx;

// // Example usage
// int main() {
//     Logger::getInstance()->log("This is a log message");
//     Logger::getInstance()->log("Singleton works!");
//     return 0;
// }



/*
    JAVA PROGRAM IS EASY:

    public class Logger {
  private static volatile Logger instance; // volatile keyword ensures visibility across threads
  private Logger() {} // Private constructor to prevent instantiation

  public static Logger getInstance() {
    if (instance == null) { // First check (no synchronization needed here)
      synchronized (
          Logger.class) { // Synchronize only when creating the instance
        if (instance == null) { // Second check (inside synchronized block)
          instance = new Logger(); // Create the instance if it's still null
        }
      }
    }
    return instance; // Return the single instance
  }

  public void log(String message) {
    System.out.println("Log: " + message);
  }
}

*/