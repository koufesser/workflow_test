#include "Workflow/Workflow.h"
#include "../tests/workflow_functions_test.cpp.h"

void test() {
    test_sort();
    test_grep();
    test_replace();
}

int main() {
    Workflow w;
    w.initialize();
    w.run();
    return 0;
}
