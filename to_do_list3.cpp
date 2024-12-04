#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;
};

void displayMenu() {
    cout << "\nTo-Do List Manager" << endl;
    cout << "1. View tasks" << endl;
    cout << "2. Add a task" << endl;
    cout << "3. Mark task as completed" << endl;
    cout << "4. Remove a task" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\nYour to-do list is empty." << endl;
    } else {
        cout << "\nYour tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].description << " [";
            cout << (tasks[i].completed ? "Completed" : "Pending") << "]" << endl;
        }
    }
}

void addTask(vector<Task>& tasks) {
    cout << "\nEnter the task description: ";
    string description;
    cin.ignore();
    getline(cin, description);
    tasks.push_back({description, false});
    cout << "Task added." << endl;
}

void markTaskCompleted(vector<Task>& tasks) {
    viewTasks(tasks);
    if (!tasks.empty()) {
        cout << "\nEnter the task number to mark as completed: ";
        size_t taskNumber;
        cin >> taskNumber;
        if (taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks[taskNumber - 1].completed = true;
            cout << "Task marked as completed." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }
}

void removeTask(vector<Task>& tasks) {
    viewTasks(tasks);
    if (!tasks.empty()) {
        cout << "\nEnter the task number to remove: ";
        size_t taskNumber;
        cin >> taskNumber;
        if (taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks.erase(tasks.begin() + taskNumber - 1);
            cout << "Task removed." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                viewTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                cout << "\nGoodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
