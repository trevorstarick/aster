//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_IOMANAGER_H
#define ASTER_IOMANAGER_H

#include <vector>
#include <string>

class IOManager {
public:
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
private:
};


#endif //ASTER_IOMANAGER_H
