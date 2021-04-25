#include <utility>
#include "ctime"
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>

#include "Parser.h"
#include "FibbTree.hpp"

using namespace std;

vector<int> split(const std::string &s, char delimiter) {
    vector<int> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(stoi(token));
    }
    return tokens;
}

string pathToInputFile = R"(D:\AaDS\onthewaytoproject-master\input.txt)";

std::string Parser::process_data() {
    ifstream file(pathToInputFile);
    string result;
    string line;

    while (getline(file, line)) {

        fibbHeap *testHeap = new fibbHeap;
        vector<int> intValues = split(line, ' ');
        result = to_string(intValues.size()) + " elements";

//insert
        double startTime = clock();
        for (int value : intValues)
            testHeap->insert(value);

        double endTime = clock();
        cout << "insert :" << to_string(endTime - startTime) + " ms\n";

//find min
        startTime = clock();
        testHeap->findMin();
        endTime = clock();
        cout << "find min :" << to_string(endTime - startTime) + " ms\n";

//extract min
        startTime = clock();
        testHeap->extractMin();
        endTime = clock();
        cout << "extract min :" << to_string(endTime - startTime) + " ms\n";
    }

    file.close();
    return result;
}