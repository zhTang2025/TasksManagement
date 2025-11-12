#include <iostream>
#include "Logger.h"
#include "TaskManager.h"
#include "command.h"
#include <unordered_map>

int main(){
    Logger::getInstance().log("Hello!");
    TaskManager taskManager;
    std::unordered_map<std::string,std::unique_ptr<CommandBase>> commands;
    commands["add"]=std::make_unique<AddCommand>(taskManager);
    commands["delete"]=std::make_unique<DeleteCommand>(taskManager);
    commands["list"]=std::make_unique<ListCommand>(taskManager);
    commands["update"]=std::make_unique<UpdateCommand>(taskManager);
    std::cout<<"Welcome your use!"<<std::endl;
    std::cout<<"THIS IS GIT TEST DEMO V1.3"<<std::endl;
    std::string input;
    while(true){
        std::cout<<std::endl;
        std::getline(std::cin,input);
        if(input.empty()){
            continue;
        }
        size_t spacePos=input.find(' ');
        std::string command=input.substr(0,spacePos);
        std::string args;
        if(spacePos!=std::string::npos){
            args=input.substr(spacePos+1);
        }
        if(command=="exit"){
            std::cout<<"Have exit"<<std::endl;
            break;
        }

        auto it=commands.find(command);
        if(it!=commands.end()){
            it->second->execute(args);
        }else{
            std::cout<<"Unknown input"<<std::endl;
        }
    }
    

    return 0;
}

