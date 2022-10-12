#include <iostream>
#include <fstream>
#include <string.h>

int main(int ac, char **av)
{
    std::string occurence, replace, filename1, filename2, line;
    size_t i;
    if (ac == 4)
    {
        occurence = av[2];
        replace = av[3];
        if (occurence.empty() || replace.empty())
            std::cout << "Syntax Error\n";
        filename1 = av[1];
        filename2 = filename1 + ".replace";
        std::ifstream ifs(filename1);
        if (!ifs)
            std::cout << "File not found";
        else
        {
            std::ofstream ofs(filename2);
            while (std::getline(ifs, line))
            {
                i = 0;
                while ((i = line.find(occurence, i)) != std::string::npos)
                {
                    line.erase(i, occurence.size());
                    line = line.substr(0, i) + replace + line.substr(i, line.size());
                    i += replace.size();
                }
                ofs << line << "\n";
            }
            ofs.close();
        }
        ifs.close();
    }
    else
        std::cout << "Warning: the program need 4 arguments." <<std::endl;
}