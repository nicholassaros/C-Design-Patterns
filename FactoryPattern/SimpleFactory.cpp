
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ILogger {
    public:
        virtual void Log(string message) = 0;
        virtual ~ILogger() {}
};

class FileLogger : public ILogger {
    private:
        string m_logLevel;
        string m_filePath;

    public:
        FileLogger(string filePath)
            : m_filePath(filePath), m_logLevel("INFO") {}

        void Log(string message) override {

            ofstream logFile(m_filePath);
            if(!logFile){
                cerr <<  "Error opening file " << strerror(errno);
            }
            logFile << m_logLevel << message << endl;
            logFile.close();
        } 
        
        void SwitchLogLevel(string logLevel) {
            m_logLevel = logLevel;
        }

        void SwitchTimeFormat(){}

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
        void SetConnection() {}
        void SetLogTable() {}
        void CloseConnection() {}
};

class JsonLogger : public ILogger {
    public: 
        JsonLogger() {}
        void Log(string message) override{}
        void SetFilePath() {}
        void PrettyPrint() {}
};


/*
    In this naive implementation we use a concrete factory class which has a method that
    take in a string type and creates the corresponding object. This can be improved as
    this will eventually become un-maintainable as we add more loggers
*/

enum Type { FILE, CONSOLE, DATABASE, JSON};
class ConcreteLoggerFactory {
    public:
        ILogger* createLogger(Type t){
            if(t == Type::FILE){
                return new FileLogger();

            } else if (t == Type::CONSOLE){
                return new ConsoleLogger();

            } else if (t == Type::DATABASE){
                return new DatabaseLogger();

            } else if (t == Type::JSON){
                return new JsonLogger();  
            }
        }
};


int main(){


}