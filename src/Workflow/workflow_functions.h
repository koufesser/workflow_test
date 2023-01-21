#ifndef UNTITLED_WORKFLOW_FUNCTIONS_H
#define UNTITLED_WORKFLOW_FUNCTIONS_H

#include <vector>

namespace workflow_functions {
    void readfile(std::string &data, const std::string &filename);

    void writefile(std::string &data, const std::string &filename);

    void grep(std::string &data, const std::string &word);

    std::vector<std::string> split(const std::string &s, char delim);

    void sort(std::string &data);

    void replace(std::string &data, const std::string &old_word, const std::string &new_word);

}

#endif //UNTITLED_WORKFLOW_FUNCTIONS_H
