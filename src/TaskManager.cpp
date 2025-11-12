#include "TaskManager.h"
#include "Logger.h"
#include <iostream>

TaskManager::TaskManager():nextId(1){
    loadTasks();
}


void TaskManager::addTask(const std::string& description,int priority,const std::string& dueDate){
    Task task;
    task.id=nextId++;
    task.description=description;
    task.priority=priority;
    task.dueDate=dueDate;
    tasks.push_back(task);
    Logger::getInstance().log("Task added: "+task.toString());
    saveTasks();
}


void TaskManager::deleteTask(int id){
    auto it=std::find_if(tasks.begin(),tasks.end(),[id](const Task& task){
        return task.id==id;
    });//找到后边lambda表达式返回为真的第一个元素，返回其位置的迭代器。没找到就指向task.end()
    if(it!=tasks.end()){
        tasks.erase(it);
        Logger::getInstance().log("Task delete: "+it->toString());
        saveTasks();
    }else{
        std::cout<<"Task not found"<<std::endl;
    }
}


void TaskManager::updateTask(int id,const std::string& description,int priority,const std::string& date){
    auto it=std::find_if(tasks.begin(),tasks.end(),[id](const Task& task){
        return task.id==id;
    });
    if(it!=tasks.end()){
        it->description=description;
        it->priority=priority;
        it->dueDate=date;
        Logger::getInstance().log("Task update: "+it->toString());
        saveTasks();
    }else{
        std::cout<<"Task not found"<<std::endl;
    }
}


void TaskManager::saveTasks() const{
    std::ofstream outFile("D:\\vscodeproject\\Tasks Management\\task.txt");
    if(!outFile.is_open()){
        Logger::getInstance().log("Failed to open tasks file for writing");
        return;
    }
    for(const auto& task:tasks){
        outFile<<task.id<<","<<task.description<<","<<task.priority<<","<<task.dueDate<<std::endl;
    }
    outFile.close();
    Logger::getInstance().log("Tasks saved successfully");
}



void TaskManager::listTasks(int sortOption) const{
    std::vector<Task> sortedTasks=tasks;
    switch(sortOption){
        case1:
            std::sort(sortedTasks.begin(),sortedTasks.end(),compareByPriority);
            break;
        case2:
            std::sort(sortedTasks.begin(),sortedTasks.end(),compareByDueDate);
            break;
        default://不排序，直接输出原始顺序
            break;
    }
    std::cout<<"Task num:"<<sortedTasks.size()<<std::endl;
    for(auto ltask:sortedTasks){
        std::cout<<ltask.toString()<<std::endl;
    }
}



void TaskManager::loadTasks(){
    std::ifstream inFile("D:\\vscodeproject\\Tasks Management\\task.txt");
    if(!inFile.is_open()){
        Logger::getInstance().log("Failed to open tasks file");
        return;
    }

    std::string line;
    while(std::getline(inFile,line)){
        std::istringstream iss(line);
        Task task;
        char delimiter;
        iss>>task.id>>delimiter;
        std::getline(iss,task.description,',');
        iss>>task.priority;
        iss>>task.dueDate;
        tasks.push_back(task);
        if(task.id>=nextId){
            nextId=task.id+1;
        }

        inFile.close();
        Logger::getInstance().log("Tasks loaded successfully");
    }
}


bool TaskManager::compareByPriority(const Task& a,const Task& b){
    return a.priority<b.priority;
}

bool TaskManager::compareByDueDate(const Task& a,const Task& b){
    return a.dueDate<b.dueDate;
}
