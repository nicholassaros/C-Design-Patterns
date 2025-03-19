
#include <iostream>

using namespace std;

class ILogger {
    public:
        virtual void Log(string message) = 0;
        virtual ~ILogger() {}
};

class FileLogger : public ILogger {
    public:
        FileLogger() {}
        void Log(string message) override {}

};

class ConsoleLogger : public ILogger {
    public:
        ConsoleLogger() {}
        void Log(string message) override {}
};

class DatabaseLogger : public ILogger {
    public:
        DatabaseLogger() {}
        void Log(string message) override{}
};

class JsonLogger : public ILogger {
    public: 
        JsonLogger() {}
        void Log(string message) override{}
};


/*
    In this naive implementation we use a concrete factory class which has a method that
    take in a string type and creates the corresponding object. This can be improved as
    this will eventually become un-maintainable as we add more loggers
*/
class ConcreteLoggerFactory {
    public:
        ILogger* createLogger(string type){
            if(type == "FileLogger"){
                return new FileLogger();
            } else if (type == "ConsoleLogger"){
                return new ConsoleLogger();
            } else if (type == "DatabaseLogger"){
                return new DatabaseLogger();
            } else if (type == "JsonLogger"){
                return new JsonLogger();
            }
        }
};


int main(){


}