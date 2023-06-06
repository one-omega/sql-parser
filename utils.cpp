#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

struct FieldInfo {
    std::string type;
    int length;
};
std::map<std::string, std::map<std::string, FieldInfo>> table_map;

void delete_row(DeleteRecord* delete_record_ctx) {
    std::cout << "hello" << std::endl;
}

void build_table_data() {
    std::ifstream file("./data/{db}/sys.dat");
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string tableName, index, fieldName, type, lengthStr;
        ss >> tableName >> index >> fieldName >> type >> lengthStr;
        
        FieldInfo fieldInfo;
        fieldInfo.type = type;
        
        // Parse length if it exists
        if (type != "int") {
            std::istringstream(lengthStr) >> fieldInfo.length;
        }
        
        table_map[tableName][fieldName] = fieldInfo;
    }
    
    file.close();
}
