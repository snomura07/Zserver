#include<iostream>
#include<vector>
#include "../module/Zserver.h"

int main(int argc, char *argv[])
{
    if (argc < 1) {
        std::cerr << "Usage: " << argv[0] << " <path> [params...]" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::vector<int> params;

    if (argc > 1) {
        for (int i = 2; i < argc; ++i) {
            try {
                params.push_back(std::stoi(argv[i]));
            } catch (const std::exception& e) {
                std::cerr << "Invalid parameter: " << argv[i] << std::endl;
                return 1;
            }
        }
    }

    Zclient zclient(5557);
    zclient.run(path, params);
}
