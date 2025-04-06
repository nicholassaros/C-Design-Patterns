
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ILogger {
    protected:
        string m_logLevel = "INFO";
    public:
        virtual void Log(string message) = 0;
        virtual void SetLogLevel(string level) = 0;
        virtual string GetLogLevel() = 0;
        virtual ~ILogger() {}
};

class FileLogger : public ILogger {
    private:
        string m_filePath;
    public:
        FileLogger()
            : m_filePath("./log_file.log") {}

        void Log(string message) override {

            ofstream logFile(m_filePath, ios::app);
            if(!logFile){
                cerr <<  "Error opening file " << strerror(errno);
            }
            string formatted_log_level = "[" + m_logLevel + "] ";

            logFile << formatted_log_level << message << endl;            
            logFile.close();
        }
        
        void SetLogLevel(string logLevel) {
            if (logLevel != "INFO" &&
                logLevel != "ERROR" &&
                logLevel != "DEBUG"){
                
                // invalid log level
                cout << "Invalid Log Level" << endl;
                exit(1);
            }
            m_logLevel = logLevel;
        }

        string GetLogLevel() {
            return m_logLevel;
        }

};

class ConsoleLogger : public ILogger {
    public:
        ConsoleLogger() {}
        void Log(string message) override {
            string formatted_log_level = "[" + m_logLevel + "] ";

            if(m_logLevel == "ERROR"){
                cerr << formatted_log_level << message << endl;
            } else {
                cout << formatted_log_level << message << endl;
            }
        }

        void SetLogLevel(string logLevel) {
            if (logLevel != "INFO" &&
                logLevel != "ERROR" &&
                logLevel != "DEBUG"){
                
                // invalid log level
                cout << "Invalid Log Level" << endl;
                exit(1);
            }
            m_logLevel = logLevel;
        }

        string GetLogLevel() {
            return m_logLevel;
        }
};



/*
    In this naive implementation we use a concrete factory class which has a method that
    take in a string type and creates the corresponding object. This can be improved as
    this will eventually become un-maintainable as we add more loggers
*/
namespace Logger {
    enum LoggerType { FILE, CONSOLE };
}
class ConcreteLoggerFactory {
    public:
        ILogger* createLogger(Logger::LoggerType t){
            if(t == Logger::LoggerType::FILE){
                return new FileLogger();

            } else {
                return new ConsoleLogger();

            }
        }
};

void testFileLogger(ILogger* fileLogger){
    fileLogger->Log("My First FileLogger Message");

    fileLogger->Log("My FileLogger level: " +fileLogger->GetLogLevel());

    string level = "ERROR";
    fileLogger->SetLogLevel(level);

    fileLogger->Log("Changed FileLogger level: " +fileLogger->GetLogLevel()); 

}

void testConsoleLogger(ILogger* consoleLogger){
    consoleLogger->Log("My First ConsoleLogger Message");

    consoleLogger->Log("My ConsoleLogger level: " +consoleLogger->GetLogLevel());

    string level = "ERROR";
    consoleLogger->SetLogLevel(level);

    consoleLogger->Log("Changed ConsoleLogger level: " +consoleLogger->GetLogLevel()); 
}



int main(){

    ConcreteLoggerFactory concreteLoggerFactory;
    int logger;
    string msg;

    cout << R"(
         _                                  _____          _                   
        | |    ___   __ _  __ _  ___ _ __  |  ___|_ _  ___| |_ ___  _ __ _   _ 
        | |   / _ \ / _` |/ _` |/ _ \ '__| | |_ / _` |/ __| __/ _ \| '__| | | |
        | |__| (_) | (_| | (_| |  __/ |    |  _| (_| | (__| || (_) | |  | |_| |
        |_____\___/ \__, |\__, |\___|_|    |_|  \__,_|\___|\__\___/|_|   \__, |
                    |___/ |___/                                          |___/ 
    )";
    cout << '\n';
    cout << '\n';
    cout << '\n';

 
    cout << "Enter '1' for File Logger" << '\n';
    cout << "Enter '2' for Console Logger" << '\n';

    cout << "Logger Selection: " << '\n';
    cin >> logger;

    if (logger == 1) {
        // Create fileLogger
        Logger::LoggerType fileLoggerType = Logger::LoggerType::FILE;
        ILogger* fileLogger = concreteLoggerFactory.createLogger(fileLoggerType);
        cout << "Selected FileLogger " << '\n';

        while(true){ 
            getline(cin, msg);
            fileLogger->Log(msg);
            cout << '\n';
        }

    } else if (logger == 2) {
        // Create consoleLogger
        Logger::LoggerType consoleLoggerType = Logger::LoggerType::CONSOLE;
        ILogger* consoleLogger = concreteLoggerFactory.createLogger(consoleLoggerType);
        cout << "Selected ConsoleLogger " << '\n';

        while(true){
            getline(cin, msg);
            consoleLogger->Log(msg);
            cout << '\n';
        }

    } else {
        cout << "INVALID SELECTION!";
    }



    cout << "Application Terminated";
}