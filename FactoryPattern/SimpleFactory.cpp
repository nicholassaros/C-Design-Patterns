
#include <iostream>

using namespace std;

class ILoggerFactor {
    virtual void Log() = 0;
    virtual ~ILoggerFactor();
};

class FileLogger : public ILoggerFactor {

};

class ConsoleLogger : public ILoggerFactor {

};

class DatabaseLogger : public ILoggerFactor {

};

class JsonLogger : public ILoggerFactor {

};



int main(){


}