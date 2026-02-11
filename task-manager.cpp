#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    int id;
    string name;
    bool completed;
};

vector<Task> tasks;

void loadTasks() {
    ifstream file("tasks.dat", ios::binary);
    Task t;
    while (file.read((char*)&t, sizeof(t))) {
        tasks.push_back(t);
    }
    file.close();
}

void saveTasks() {
    ofstream file("tasks.dat", ios::binary);
    for (auto &t : tasks) {
        file.write((char*)&t, sizeof(t));
    }
    file.close();
}

void addTask() {
    Task t;
    cout << "Enter Task ID: ";
    cin >> t.id;
    cin.ignore();
    cout << "Enter Task Name: ";
    getline(cin, t.name);
    t.completed = false;
    tasks.push_back(t);
    saveTasks();
    cout << "Task added successfully!\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks available!\n";
        return;
    }

    cout << "\nID   Task Name                 Status\n";
    cout << "-----------------------------------------\n";
    for (auto &t : tasks) {
        cout << t.id << "    " << t.name;
        for (int i = t.name.length(); i < 25; i++) cout << " ";
        cout << (t.completed ? "Completed" : "Pending") << endl;
    }
}

void markCompleted() {
    int id;
    cout << "Enter Task ID to mark complete: ";
    cin >> id;
    for (auto &t : tasks) {
        if (t.id == id) {
            t.completed = true;
            saveTasks();
            cout << "Task marked as completed!\n";
            return;
        }
    }
    cout << "Task not found!\n";
}

void deleteTask() {
    int id;
    cout << "Enter Task ID to delete: ";
    cin >> id;

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            saveTasks();
            cout << "Task deleted successfully!\n";
            return;
        }
    }
    cout << "Task not found!\n";
}

int main() {
    loadTasks();

    int choice;
    do {
        cout << "\n==============================";
        cout << "\n     TASK MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Add Task";
        cout << "\n2. View Tasks";
        cout << "\n3. Mark Task Completed";
        cout << "\n4. Delete Task";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(); break;
            case 4: deleteTask(); break;
            case 5: cout << "Exiting Task Manager...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
