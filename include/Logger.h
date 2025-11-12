#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>
#include <atomic>
#include <sstream>
#include <vector>
#include <stdexcept>

class Logger{
public:
    //获取单例 可以理解为日志打印器
    static Logger& getInstance();
    //禁止拷贝和赋值
    Logger(const Logger&)=delete;
    Logger& operator=(const Logger&)=delete;
    //记录日志
    void log(const std::string& message);
    ~Logger();
private:
    Logger();
    std::ofstream logFile;//定义一个文件输出流
    std::mutex mutex;//定义一个锁保证线程安全
};
