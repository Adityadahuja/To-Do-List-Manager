#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// Structure to hold task information
struct Task {
    string description;
    bool completed;
};

// Function prototypes
void displayMenu();
void addTask(vector<Task>& tasks);
void removeTask(vector<Task>& tasks);
void updateTask(vector<Task>& tasks);
void listTasks(const vector<Task>& tasks);
void saveTasks(const vector<Task>& tasks);
void loadTasks(vector<Task>& tasks);
void clearScreen();

int main() {
    vector<Task> tasks;
    loadTasks(tasks);
    
    int choice;
    bool running = true;
    
    while (running) {
        clearScreen();
        cout << "\033[1;36m" << "===================================" << endl;
        cout << "        TO-DO LIST MANAGER" << endl;
        cout << "===================================" << "\033[0m" << endl;
        
        displayMenu();
        cout << "\nEnter your choice (1-5): ";
        cin >> choice;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                removeTask(tasks);
                break;
            case 3:
                updateTask(tasks);
                break;
            case 4:
                listTasks(tasks);
                break;
            case 5:
                running = false;
                cout << "\033[1;32m" << "Saving tasks and exiting..." << "\033[0m" << endl;
                break;
            default:
                cout << "\033[1;31m" << "Invalid choice! Please try again." << "\033[0m" << endl;
                break;
        }
        
        if (running) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
    
    saveTasks(tasks);
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu() {
    cout << "\033[1;33m" << "1. Add Task" << "\033[0m" << endl;
    cout << "\033[1;33m" << "2. Remove Task" << "\033[0m" << endl;
    cout << "\033[1;33m" << "3. Update Task" << "\033[0m" << endl;
    cout << "\033[1;33m" << "4. List Tasks" << "\033[0m" << endl;
    cout << "\033[1;33m" << "5. Exit" << "\033[0m" << endl;
}

void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "\nEnter task description: ";
    getline(cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "\033[1;32m" << "Task added successfully!" << "\033[0m" << endl;
}

void removeTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\033[1;31m" << "No tasks to remove!" << "\033[0m" << endl;
        return;
    }
    
    listTasks(tasks);
    int index;
    cout << "\nEnter task number to remove: ";
    cin >> index;
    
    if (index > 0 && index <= static_cast<int>(tasks.size())) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "\033[1;32m" << "Task removed successfully!" << "\033[0m" << endl;
    } else {
        cout << "\033[1;31m" << "Invalid task number!" << "\033[0m" << endl;
    }
}

void updateTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\033[1;31m" << "No tasks to update!" << "\033[0m" << endl;
        return;
    }
    
    listTasks(tasks);
    int index;
    cout << "\nEnter task number to update: ";
    cin >> index;
    
    if (index > 0 && index <= static_cast<int>(tasks.size())) {
        cin.ignore();
        cout << "Enter new task description: ";
        getline(cin, tasks[index - 1].description);
        cout << "\033[1;32m" << "Task updated successfully!" << "\033[0m" << endl;
    } else {
        cout << "\033[1;31m" << "Invalid task number!" << "\033[0m" << endl;
    }
}

void listTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\033[1;31m" << "No tasks in the list!" << "\033[0m" << endl;
        return;
    }
    
    cout << "\n\033[1;35m" << "Current Tasks:" << "\033[0m" << endl;
    cout << "\033[1;35m" << "-----------------------------------" << "\033[0m" << endl;
    
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << "\033[1;33m" << i + 1 << ". " << "\033[0m";
        if (tasks[i].completed) {
            cout << "\033[1;32m" << "[✓] " << "\033[0m";
        } else {
            cout << "\033[1;31m" << "[ ] " << "\033[0m";
        }
        cout << tasks[i].description << endl;
    }
}

void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.description << "|" << task.completed << endl;
        }
        file.close();
    }
}

void loadTasks(vector<Task>& tasks) {
    ifstream file("tasks.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                Task task;
                task.description = line.substr(0, pos);
                task.completed = (line.substr(pos + 1) == "1");
                tasks.push_back(task);
            }
        }
        file.close();
    }
} 