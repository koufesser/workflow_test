#include "Workflow.h"

void Workflow::initialize() {
    std::string fword, equals_symbol, command;
    std::ifstream infile(task_file);
    while ((infile >> fword) && fword != "end") {
        int id = std::stoi(fword);
        infile >> equals_symbol >> command;
        assert(equals_symbol == "=");
        std::string arg1, arg2;
        switch (table.at(command)) {
            case readfile:
                infile >> arg1;
                text_commands[id] = [arg1](std::string &data) {
                    workflow_functions::readfile(data, arg1);
                };
                break;
            case writefile:
                infile >> arg1;
                text_commands[id] = [arg1](std::string &data) {
                    workflow_functions::writefile(data, arg1);
                };
                break;
            case grep:
                infile >> arg1;
                text_commands[id] = [arg1](std::string &data) {
                    workflow_functions::grep(data, arg1);
                };
                break;

            case sort:
                text_commands[id] = [arg1](std::string &data) {
                    workflow_functions::sort(data);
                };
                break;

            case replace:
                infile >> arg1 >> arg2;
                text_commands[id] = [arg1, arg2](std::string &data) {
                    workflow_functions::replace(data, arg1, arg2);
                };
                break;
            case synch:
                sync_commands.insert(id);
                break;
        }
    }
    std::string chain;
    while ((infile >> chain) and !infile.eof())
        command_chains.push_back(chain);
}

void Workflow::run() {

    std::vector<long long> locker_array(command_chains.size());
    std::mutex mtx;

    auto worker = [&](const std::string &chain, int thread_id) {
        std::stringstream ss;
        ss << chain;

        std::string data;
        int command_id;

        while (!ss.eof()) {
            ss >> command_id;
            if (sync_commands.find(command_id) != sync_commands.end()) {
                long long locker;
                mtx.lock();
                locker = ++locker_array[thread_id];
                mtx.unlock();
                bool synced = false;
                while (!synced) {
                    mtx.lock();
                    synced = std::all_of(locker_array.begin(), locker_array.end(),
                                         [locker](int i) { return i >= locker; });
                    mtx.unlock();
                }
            } else {
                text_commands[command_id](data);
            }
            char t;
            ss >> t >> t;
        }
        locker_array[thread_id] = INT32_MAX;
    };

    std::vector<std::thread> threadVector;
    for (int i = 0; i < command_chains.size(); i++)
        threadVector.emplace_back(worker, command_chains[i], i);

    for (auto &thread: threadVector)
        thread.join();

}
