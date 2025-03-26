
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
        FileLogger()
            : m_filePath("./log_file.log"), m_logLevel("INFO") {}

        void Log(string message) override {

            ofstream logFile(m_filePath);
            if(!logFile){
                cerr <<  "Error opening file " << strerror(errno);
            }
            logFile << m_logLevel << message << endl;
            logFile.close();
        }

        void SetLogPath(string filePath){
            m_filePath = filePath;
        }
        
        void SetLogLevel(string logLevel) {
            m_logLevel = logLevel;
        }

        void SetTimeFormat(){}

};

class ConsoleLogger : public ILogger {
    private:
        string m_logLocation;
    public:
        ConsoleLogger() 
            : m_logLocation("OUT") {}

        void Log(string message) override {
            if(m_logLocation == "OUT"){
                cout << message << endl;
            } else {
                cerr << message << endl;
            }
        }

        string GetLogOuput() {
            return m_logLocation;
        }

        void SetLogOutput(string newOutput) {
            if(newOutput != "OUT" || newOutput != "ERR"){
                cerr << "Invalid Log Output for ConsoleLogger. Use 'OUT' or 'ERR'" << endl;
            }
            m_logLocation = newOutput;
        }
};

class DatabaseLogger : public ILogger {
    public:
        DatabaseLogger() {}
        void Log(string message) override{}
        void SetLogTable() {}
        ~DatabaseLogger() {}
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

enum LoggerType { FILE, CONSOLE, DATABASE, JSON};
class ConcreteLoggerFactory {
    public:
        ILogger* createLogger(LoggerType t){
            if(t == LoggerType::FILE){
                return new FileLogger();

            } else if (t == LoggerType::CONSOLE){
                return new ConsoleLogger();

            } else if (t == LoggerType::DATABASE){
                return new DatabaseLogger();

            } else if (t == LoggerType::JSON){
                return new JsonLogger();  
            }
        }
};


int main(){

    LoggerType fileLoggerType = LoggerType::FILE;
    ConcreteLoggerFactory concreteLoggerFactory;

    ILogger* fileLogger = concreteLoggerFactory.createLogger(fileLoggerType);

}