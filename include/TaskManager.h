#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
class Task{
public:
    int id;
    std::string description;
    int priority;
    std::string dueDate;

    std::string toString() const{
        std::ostringstream oss;
        oss<<"ID: "<<id
        <<",Descript: "<<description
        <<",Priority: "<<priority
        <<",DDL: "<<dueDate;
        return oss.str();
    }
};

class TaskManager{
public:
    TaskManager();
    void addTask(const std::string& description,int priority,const std::string& date);
    void deleteTask(int id);
    void updateTask(int id,const std::string& description,int priority,const std::string& date);
    void listTasks(int sortOption) const;//0:按ID 1：按优先级升序 2：按日期升序
    void loadTasks();
    void saveTasks() const;
    
private:
    std::vector<Task> tasks;
    int nextId;
    static bool compareByPriority(const Task& a,const Task& b);
    static bool compareByDueDate(const Task& a,const Task& b);
};