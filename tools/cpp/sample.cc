#include "console.h"
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <sstream>

using namespace clidevt;

class IunitCommand : public Command {
    class OptionCheckFunctor {
        std::string optionName;
    public:
        OptionCheckFunctor(const std::string optionName) : optionName(optionName) {
        }

        bool operator()(const std::string str) {
            if(str.find(optionName) != std::string::npos) {
                return true;
            } else {
                return false;
            }
        };
    };
    class ExcludeCandidatesCleaner {
    public:
        void operator()(std::string& candidate) {
            if(candidate == "--exclude=" || candidate == "--include=" || candidate == "--repeat=") {
                return;
            }
            size_t pos = candidate.rfind(",");
            if(pos != std::string::npos) {
                candidate = candidate.substr(pos+1);
            } else {
                candidate = candidate.substr(candidate.find("=")+1);
            }
        }
    };

    std::string _cmd;
public:
    IunitCommand() {
        _cmd = "../../bin/cpp/iunitdemo_cpp ";
    }
    virtual ~IunitCommand() {}

    virtual std::string getKey() const { return "run"; }
    virtual void printHelp() const { std::cout << "Execute bin/cpp/iunitdemo_cpp." << std::endl; }
    virtual void execute(std::string parameter) {
        std::string cmd = _cmd;
        cmd += parameter;
        system(cmd.c_str());
    }
    virtual void getParamCandidates(std::vector<std::string>& inputtedList, std::string inputting, std::vector<std::string>& candidates) const {
        if(inputting.find("--exclude=") != std::string::npos) {
            getExcludeList(inputting, candidates);
        } else if(inputting.find("--include=") != std::string::npos) {
            getExcludeList(inputting, candidates);
        } else {
            OptionCheckFunctor shuffle("--shuffle");
            if(std::find_if(inputtedList.begin(), inputtedList.end(), shuffle) == inputtedList.end()) {
                candidates.push_back("--shuffle");
            }
            OptionCheckFunctor repeat("--repeat");
            if(std::find_if(inputtedList.begin(), inputtedList.end(), repeat) == inputtedList.end()) {
                candidates.push_back("--repeat=");
            }
            OptionCheckFunctor exclude("--exclude");
            if(std::find_if(inputtedList.begin(), inputtedList.end(), exclude) == inputtedList.end()) {
                candidates.push_back("--exclude=");
            }
            OptionCheckFunctor include("--include");
            if(std::find_if(inputtedList.begin(), inputtedList.end(), include) == inputtedList.end()) {
                candidates.push_back("--include=");
            }
            OptionCheckFunctor printPath("--print-path");
            if(std::find_if(inputtedList.begin(), inputtedList.end(), printPath) == inputtedList.end()) {
                candidates.push_back("--print-path");
            }
            OptionCheckFunctor help("--help");
            if(std::find_if(inputtedList.begin(), inputtedList.end(), help) == inputtedList.end()) {
                candidates.push_back("--help");
            }
        }
    }

    void getExcludeList(std::string& inputting, std::vector<std::string>& candidates) const {
        std::string prefix;
        std::string suffix;
        size_t pos = inputting.rfind(",");
        std::vector<std::string> inputtedPath;
        if(pos != std::string::npos) {
            prefix = inputting.substr(0, pos+1);
            suffix = inputting.substr(pos+1);
            pos = inputting.find("=")+1;
            size_t next = inputting.find(",", pos);
            while(next != std::string::npos) {
                std::string path = inputting.substr(pos, (next-pos));
                if(!path.empty()) {
                    inputtedPath.push_back(prefix+path);
                }
                pos = next+1;
                next = inputting.find(",", next+1);
            }
        } else {
            prefix = inputting.substr(0, inputting.find("=")+1);
            suffix = inputting.substr(inputting.find("=")+1);
        }

        // テストパス情報の取得
        FILE* in_pipe = NULL;
        std::string cmd = _cmd + "--print-path";
        in_pipe = popen(cmd.c_str(), "r");
        std::stringstream paramList("");
        char buffer[512+1] = {0};
        if(in_pipe != NULL) {
            size_t readed_num = fread(buffer, sizeof(char), 512, in_pipe);
            while(readed_num > 0) {
                paramList.write(buffer, readed_num);
                readed_num = fread(buffer, sizeof(char), 512, in_pipe);
            }
        }
        pclose(in_pipe);

        // テストパスを ディレクトリ移動と同じスタイルで補完できるように処理
        // また、一度指定したパスは補完対象から除く
        while(!paramList.eof()) {
            std::string str;
            paramList >> std::skipws >> str;
            if(str.empty()) {
                continue;
            }
            pos = str.find("/", suffix.length());
            std::string name;
            if(pos != std::string::npos) {
                std::string path = str.substr(0, str.find("/", suffix.length())+1);
                name = prefix+path;
            } else {
                name = prefix+str;
            }
            if(std::find(inputtedPath.begin(), inputtedPath.end(), name) == inputtedPath.end()) {
                candidates.push_back(name);
            }
        }

        std::sort(candidates.begin(), candidates.end());
        candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
        
    }

    virtual void afterCompletionHook(std::vector<std::string>& candidates) const {
        ExcludeCandidatesCleaner func;
        std::for_each(candidates.begin(), candidates.end(), func);
    }
    
private:
};

class ExitCommand : public Command {
public:
    ExitCommand() {}
    virtual ~ExitCommand() {}

    virtual std::string getKey() const { return "exit"; }
    virtual void printHelp() const { std::cout << "console exit." << std::endl; }
    virtual void execute(std::string parameter) { _console->actionTerminate(); }
    virtual void getParamCandidates(std::vector<std::string>& inputtedList, std::string inputting, std::vector<std::string>& matchList) const {
    }

private:
};

int main(int argc, char const* argv[])
{
    int historySize = 100;
    std::string historyFileName = ".cli_history";

    // Console console;             // use default : historySize = 20, ctrl_c = true, historyFileName = ".cli_history"
    // Console console(history); 
    // Console console(history, ctrl_c);
    Console console(historySize, historyFileName.c_str());

    if(console.installCommand(new ExitCommand()) == false) {
        std::cout << "install false" << std::endl;
        return -1;
    }
    if(console.installCommand(new IunitCommand()) == false) {
        std::cout << "install false" << std::endl;
        return -1;
    }

    console.run();

    return 0;
}

std::string Console::printPromptImpl() const {
    std::string dir = getCurrentDirectory();
    std::string prompt = "$ ";
    return prompt;
}
void Console::printTitle() {
    std::cout << "+------------------------------------+\n";
    std::cout << "|           iunit console            |\n";
    std::cout << "+------------------------------------+\n";
}

// キー入力発生時に実行する関数を登録
void Console::keyBindInitialize() {

    // Delete Character
    registerKeyBinding(KeyCode::KEY_BS, &Console::actionDeleteBackwardCharacter);
    registerKeyBinding(KeyCode::KEY_DEL, &Console::actionDeleteForwardCharacter);
    registerKeyBinding(KeyCode::KEY_CTRL_K, &Console::actionDeleteFromCursorToEnd);
    registerKeyBinding(KeyCode::KEY_CTRL_U, &Console::actionDeleteFromHeadToCursor);
    registerKeyBinding(KeyCode::KEY_CTRL_L, &Console::actionClearScreen);
    registerKeyBinding(KeyCode::KEY_CTRL_S, &Console::actionClearLine);
    registerKeyBinding(KeyCode::KEY_CTRL_G, &Console::actionDeleteParam);

    // Comerplete
    registerKeyBinding(KeyCode::KEY_TAB, &Console::actionComplete);
    registerKeyBinding(KeyCode::KEY_CTRL_SPACE, &Console::actionComplete);

    // Hisertory select
    registerKeyBinding(KeyCode::KEY_UP_ARROW, &Console::actionBackwardHistory);
    registerKeyBinding(KeyCode::KEY_ALT_K, &Console::actionBackwardHistory);
    registerKeyBinding(KeyCode::KEY_DOWN_ARROW, &Console::actionForwardHistory);
    registerKeyBinding(KeyCode::KEY_ALT_J, &Console::actionForwardHistory);

    // curersor move
    registerKeyBinding(KeyCode::KEY_RIGHT_ARROW, &Console::actionMoveCursorRight);
    registerKeyBinding(KeyCode::KEY_CTRL_F, &Console::actionMoveCursorRight);
    registerKeyBinding(KeyCode::KEY_LEFT_ARROW, &Console::actionMoveCursorLeft);
    registerKeyBinding(KeyCode::KEY_CTRL_B, &Console::actionMoveCursorLeft);
    registerKeyBinding(KeyCode::KEY_CTRL_A, &Console::actionMoveCursorTop);
    registerKeyBinding(KeyCode::KEY_CTRL_E, &Console::actionMoveCursorBottom);


    // comermand execute
    registerKeyBinding(KeyCode::KEY_CR, &Console::actionEnter);
    registerKeyBinding(KeyCode::KEY_CTRL_N, &Console::actionMoveCursorForwardParam);
    registerKeyBinding(KeyCode::KEY_CTRL_P, &Console::actionMoveCursorBackwardParam);

    // CTRerL-C
    registerKeyBinding(KeyCode::KEY_CTRL_C, &Console::actionTerminate);
}

