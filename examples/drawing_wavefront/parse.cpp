#include "parse.h"
#include <fstream>
#include <sstream>


Wavefront parse(const std::string& path)
{
    std::ifstream fin(path);
    
    if (!fin)
        return {};

    std::string line, tmp;
    Wavefront wavefront;

    while (fin.peek() != EOF)
    {
        std::getline(fin, line, '\n');
        std::stringstream curr_line(line);

        std::getline(curr_line, tmp, ' ');

        if (tmp == std::string("v"))
        {
            std::getline(curr_line, tmp, '\n');
            std::stringstream ss(tmp);
            wavefront.vertices.push_back({});
            ss >> wavefront.vertices.back().x >> wavefront.vertices.back().y;
        }

        if (tmp == std::string("f"))
        {
            wavefront.faces.push_back({});

            std::getline(curr_line, tmp, ' ');
            std::stringstream(tmp) >> wavefront.faces.back().v1;

            std::getline(curr_line, tmp, ' ');
            std::stringstream(tmp) >> wavefront.faces.back().v2;

            std::getline(curr_line, tmp, '\n');
            std::stringstream(tmp) >> wavefront.faces.back().v3;
        }
    }

    return wavefront;
}