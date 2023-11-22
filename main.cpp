#include "LexAnalyse.cpp"
#include "SynAnalyse.cpp"
#include <cstring>

int main()
{
    // lexical analysis part
    initKeyMap();
    initOperMap();
    initLimitMap();
    initNode();

    cout << "The lexical analysis results are as follows: " << endl;
    scanner();

    printNodeLink();
    outputNodeLink();
    printErrorLink();

    // Word link points to the first word
    NormalNode *p = normalHead->next;
    // Refresh intermediate variable occupancy
    memset(T, 0, sizeof(T));
    // Define the special case of the intermediate point
    error.isT = -1;
    null.isT = 2;

    // Grammar analysis part
    cout << "The grammar (guided translation) analysis results are as follows: " << endl;
    program(p);

    // Output and export the identifier table
    printIdentLink();
    outputIdenLink();

    // Output and export the updated word analysis table
    printNodeLink();
    outputNodeLink();

    // Output and export quaternion code
    printCode();
    outputCode();

    clear();
    return 0;
}