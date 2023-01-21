#ifndef UNTITLED_WORKFLOW_H
#define UNTITLED_WORKFLOW_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cassert>
#include <sstream>
#include <functional>
#include <unordered_set>
#include <mutex>
#include <unistd.h>
#include <thread>
#include <utility>
#include "workflow_functions.h"

struct Workflow {

    explicit Workflow(std::string task_file_) : task_file(std::move(task_file_)) {}

    enum Task {
        readfile, writefile, grep, sort, replace, synch
    };

    std::unordered_map<std::string, Task> const table = {
            {"readfile",  Task::readfile},
            {"writefile", Task::writefile},
            {"grep",      Task::grep},
            {"sort",      Task::sort},
            {"replace",   Task::replace},
            {"synch",     Task::synch}
    };
    std::string task_file;
    std::vector<std::string> command_chains;
    std::unordered_map<int, std::function<void(std::string &)>> text_commands;
    std::unordered_set<int> sync_commands;

    void initialize();

    void run();
};


#endif //UNTITLED_WORKFLOW_H
