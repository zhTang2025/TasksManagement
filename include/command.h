#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <TaskManager.h>
#include <Logger.h>
class CommandBase{
public:
    virtual void execute(const std::string& args)=0;
};

template<typename Derived>//编译期多态
class Command:public CommandBase{
public:
    void execute(const std::string& args){
        static_cast<Derived*>(this)->executeImpl(args);//把基类指针强转成子类指针 static_cast是强制类型转换方法
    }
};

class AddCommand:public Command<AddCommand>{
public:
    AddCommand(TaskManager& manager):taskManager(manager){}

    void executeImpl(const std::string& args){
        size_t pos1=args.find(',');
        size_t pos2=args.find(',',pos1+1);
        if(pos1==std::string::npos || pos2==std::string::npos){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }
        std::string description=args.substr(0,pos1);
        int priority=std::stoi(args.substr(pos1+1,pos2-pos1-1));
        std::string dueDate=args.substr(pos2+1);
        taskManager.addTask(description,priority,dueDate);
        std::cout<<"Task add successfully"<<std::endl;
    }
private:
    TaskManager& taskManager;
};


class DeleteCommand:public Command<DeleteCommand>{
public:
    DeleteCommand(TaskManager& manager):taskManager(manager){}

    void executeImpl(const std::string& args){
        try{
            size_t pos;
            int id=std::stoi(args,&pos);
            if(pos!=args.length()){
                std::cout<<"para mode error"<<std::endl;
                Logger::getInstance().log("para mode error");
                return;
            }
            taskManager.deleteTask(id);
            std::cout<<"Task delete successfully"<<std::endl;
        }catch(const std::invalid_argument& e){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }catch(const std::out_of_range& e){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }
    }

private:
    TaskManager& taskManager;
};


class ListCommand:public Command<ListCommand>{
public:
    ListCommand(TaskManager& manager):taskManager(manager){}

    void executeImpl(const std::string& args){
        try{
            int sortOption=0;
            size_t pos;
            
            sortOption=std::stoi(args,&pos);
            if(pos!=args.length()){
                std::cout<<"para mode error"<<std::endl;
                std::cout<<"please use list <sort option>"<<std::endl;
                Logger::getInstance().log("para mode error");
                return;
            }
            std::cout<<"Task list:"<<std::endl;
            taskManager.listTasks(sortOption);
        }catch(const std::invalid_argument& e){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }
        catch(const std::out_of_range& e){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }
    }

private:
    TaskManager& taskManager;
};


class UpdateCommand:public Command<UpdateCommand>{
public:
    UpdateCommand(TaskManager& manager):taskManager(manager){}

    void executeImpl(const std::string& args){
        try{
            size_t pos1=args.find(',');
            size_t pos2=args.find(',',pos1+1);
            size_t pos3=args.find(',',pos2+1);
            if(pos1==std::string::npos || pos2==std::string::npos || pos3==std::string::npos){
                std::cout<<"para mode error"<<std::endl;
                std::cout<<"please use undate <ID>,<des>,<pri>,<duedate>"<<std::endl;
                Logger::getInstance().log("para mode error");
                return;
            }
            int id=std::stoi(args.substr(0,pos1));
            std::string description=args.substr(pos1+1,pos2-pos1-1);
            int priority=std::stoi(args.substr(pos2+1,pos3-pos2-1));
            std::string dueDate=args.substr(pos3+1);
            taskManager.updateTask(id,description,priority,dueDate);
            std::cout<<"Task update successfully"<<std::endl;

            
        }catch(const std::invalid_argument& e){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }
        catch(const std::out_of_range& e){
            std::cout<<"para mode error"<<std::endl;
            Logger::getInstance().log("para mode error");
            return;
        }
    }

private:
    TaskManager& taskManager;
};


