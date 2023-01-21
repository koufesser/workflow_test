#include <string>
#include <cassert>
#include "../src/Workflow/workflow_functions.h"


void restart(std::string &data) {
    std::string filename = R"(C:\Users\Work\CLionProjects\untitled\example1.in)";
    workflow_functions::readfile(data, filename);
}

void test_grep() {
    std::string data;
    restart(data);
    workflow_functions::grep(data, "wizard");
    assert(data == "wizardfantasy\n"
                   "fantasywizard\n"
                   "sfaflksfjwizardaflkajfklfantazy\n"
    );
}


void test_sort() {
    std::string data;
    restart(data);
    workflow_functions::sort(data);
    assert(data == "aaaaaddddfantasy\n"
                   "adkfjalafantasy\n"
                   "fantasywizard\n"
                   "sfaflksfjwizardaflkajfklfantazy\n"
                   "sfds\n"
                   "sfsafjkfjafkl\n"
                   "wizardfantasy\n"
    );
}


void test_replace() {
    std::string data;
    restart(data);
    workflow_functions::replace(data, "wizard", "bad");
    assert(data == "adkfjalafantasy\n"
                   "sfds\n"
                   "sfsafjkfjafkl\n"
                   "aaaaaddddfantasy\n"
                   "badfantasy\n"
                   "fantasybad\n"
                   "sfaflksfjbadaflkajfklfantazy\n"
    );
}

