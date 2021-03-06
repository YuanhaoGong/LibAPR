//
// Created by cheesema on 21.01.18.
//

#ifndef PARTPLAY_EXAMPLE_COMPUTE_GRADIENT_HPP
#define PARTPLAY_EXAMPLE_COMPUTE_GRADIENT_HPP

#include <functional>
#include <string>

#include "src/data_structures/APR/APR.hpp"
#include "src/numerics/APRNumerics.hpp"
#include "src/numerics/MeshNumerics.hpp"

struct cmdLineOptions{
    std::string output = "output";
    std::string stats = "";
    std::string directory = "";
    std::string input = "";
    bool stats_file = false;
    std::string original_image = "";
    unsigned int smooth_number = 0;
    float anisotropy_z = 1.0f;
};

cmdLineOptions read_command_line_options(int argc, char **argv);

bool command_option_exists(char **begin, char **end, const std::string &option);

char* get_command_option(char **begin, char **end, const std::string &option);


#endif //PARTPLAY_EXAMPLE_COMPUTE_GRADIENT_HPP
