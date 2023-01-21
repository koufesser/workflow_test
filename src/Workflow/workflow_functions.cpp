#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "workflow_functions.h"

namespace workflow_functions {
    void readfile(std::string &data, const std::string &filename) {
        std::ifstream in(filename);
        std::stringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();
        in.close();
    }

    void writefile(std::string &data, const std::string &filename) {
        std::ofstream out(filename);
        out << data;
        out.close();
    }

    void grep(std::string &data, const std::string &word) {
        auto old_lines = split(data, '\n');
        data = "";
        for (const auto &line: old_lines) {
            if (line.find(word) != std::string::npos)
                data += line + '\n';
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }

        return result;
    }

    void sort(std::string &data) {
        auto old_lines = split(data, '\n');
        data = "";
        std::sort(old_lines.begin(), old_lines.end());
        for (const auto &line: old_lines)
            data += line + '\n';
    }


    void replace(std::string &data, const std::string &old_word, const std::string &new_word) {
        while (data.find(old_word) != std::string::npos)
            data.replace(data.find(old_word), old_word.size(), new_word);
    }
}
