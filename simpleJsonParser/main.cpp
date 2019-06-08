#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#define SAMPLE_JSON1 "/home/nathaniel/VsCodeProjects/BoostTests/simpleJsonParser/testJson/sample1.json"
#define SAMPLE_JSON2 "/home/nathaniel/VsCodeProjects/BoostTests/simpleJsonParser/testJson/sample2.json"
#define SAMPLE_JSON3 "/home/nathaniel/VsCodeProjects/BoostTests/simpleJsonParser/testJson/sample3.json"

std::map<std::string, std::string> getParsedMap(std::string str);
void printParsedMap(std::map<std::string, std::string> ssMap);
std::string readFile(std::string path);

int main() {
    std::string data;

    printParsedMap(getParsedMap(readFile(SAMPLE_JSON1)));
    std::cout << std::endl << std::endl;
    printParsedMap(getParsedMap(readFile(SAMPLE_JSON2)));
    std::cout << std::endl << std::endl;
    printParsedMap(getParsedMap(readFile(SAMPLE_JSON3)));

    return 0;
}


std::map<std::string, std::string> getParsedMap(std::string str)
{
    std::vector<std::string> keyValues;
    std::vector<std::string> keyAndValues;
    std::map<std::string, std::string> ssMap;

    boost::replace_all(str, "{", "");
    boost::replace_all(str, "}", "");
    boost::split(keyValues, str, boost::is_any_of(",:"));

    int i = 0;
    std::string lastKey;

    for(auto tok : keyValues)
    {
        if(i++%2)
        {
            boost::trim(tok);
            ssMap[lastKey] = tok;
        }
        else 
        {
            boost::trim(tok);
            lastKey = tok;
        }
    }

    return ssMap;
}

void printParsedMap(std::map<std::string, std::string> ssMap)
{
    for(auto kv: ssMap)
    {
        std::cout << kv.first << ": " << kv.second << std::endl;
    }
}

std::string readFile(std::string path)
{
    std::ifstream infile;
    std::string data;

    infile.open(path); 
    data = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    return data;
}
