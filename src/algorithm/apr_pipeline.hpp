//
// Created by cheesema on 23/01/17.
//

#ifndef PARTPLAY_APR_PIPELINE_HPP
#define PARTPLAY_APR_PIPELINE_HPP

#include "../../src/data_structures/structure_parts.h"

#include "../../src/data_structures/meshclass.h"
#include "../../src/io/readimage.h"

#include "../../src/algorithm/gradient.hpp"
#include "../../src/data_structures/particle_map.hpp"
#include "../../src/data_structures/Tree/PartCellBase.hpp"
#include "../../src/data_structures/Tree/PartCellStructure.hpp"
#include "../../src/algorithm/level.hpp"
#include "../../src/io/writeimage.h"
#include "../../src/io/write_parts.h"
#include "../../src/io/partcell_io.h"
#include "../../src/data_structures/Tree/PartCellParent.hpp"

struct cmdLineOptions{
    std::string output_dir = "";
    std::string output = "output";
    std::string stats = "";
    std::string directory = "";
    std::string input = "";
    bool stats_file = false;
};

bool command_option_exists(char **begin, char **end, const std::string &option)
{
    return std::find(begin, end, option) != end;
}

char* get_command_option(char **begin, char **end, const std::string &option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

cmdLineOptions read_command_line_options(int argc, char **argv, Part_rep& part_rep){

    cmdLineOptions result;

    if(argc == 1) {
        std::cerr << "Usage: \"pipeline -i inputfile [-t] [-s statsfile -d directory] [-o outputfile]\"" << std::endl;
        exit(1);
    }

    if(command_option_exists(argv, argv + argc, "-i"))
    {
        result.input = std::string(get_command_option(argv, argv + argc, "-i"));
    } else {
        std::cout << "Input file required" << std::endl;
        exit(2);
    }

    if(command_option_exists(argv, argv + argc, "-o"))
    {
        result.output = std::string(get_command_option(argv, argv + argc, "-o"));
    }



    if(command_option_exists(argv, argv + argc, "-d"))
    {
        result.directory = std::string(get_command_option(argv, argv + argc, "-d"));
    }
    if(command_option_exists(argv, argv + argc, "-s"))
    {
        result.stats = std::string(get_command_option(argv, argv + argc, "-s"));
        get_image_stats(part_rep.pars, result.directory, result.stats);
        result.stats_file = true;
    }
    if(command_option_exists(argv, argv + argc, "-t"))
    {
        part_rep.timer.verbose_flag = true;
    }

    if(command_option_exists(argv, argv + argc, "-od"))
    {
        result.output_dir = std::string(get_command_option(argv, argv + argc, "-od"));
    } else {
        result.output_dir = result.directory;
    }

    return result;

}

template<typename U>
U median_3(U& a,U& b,U& c) {
    // 3 value median
    return std::max(std::min(a, b), std::min(std::max(a, b), c));
}

template<typename U>
void calc_median_filter(Mesh_data<U>& input_img){


    uint64_t offset_min;
    uint64_t offset_max;

    const int x_num_m = input_img.x_num;
    const int y_num_m = input_img.y_num;
    const int z_num_m = input_img.z_num;

    Part_timer timer;

    timer.start_timer("compute gradient y");

    std::vector<U> temp_vec;
    temp_vec.resize(y_num_m);


    uint64_t x_,z_;

#pragma omp parallel for default(shared) private(z_,x_,offset_min,offset_max) firstprivate(temp_vec)
    for(z_ = 0;z_ < z_num_m;z_++){
        //both z and x are explicitly accessed in the structure

        for(x_ = 0;x_ < x_num_m;x_++){

            for (int k = 0; k < y_num_m; ++k) {
                temp_vec[k] = input_img.mesh[z_*x_num_m*y_num_m + x_*y_num_m + k];
            }

            for (int k = 0; k < y_num_m; ++k) {
                offset_max = std::min((int)(k + 1),(int)(y_num_m-1));
                offset_min = std::max((int)(k - 1),(int)0);

                input_img.mesh[z_*x_num_m*y_num_m + x_*y_num_m + k] = median_3(temp_vec[offset_min],temp_vec[k],temp_vec[offset_max]);
            }


        }
    }

    timer.stop_timer();

    float time = (timer.t2 - timer.t1);

    std::cout << " Median Filter y took: " << time << std::endl;

    std::vector<U> temp_vecp;
    temp_vecp.resize(y_num_m);

    std::vector<U> temp_vecm;
    temp_vecm.resize(y_num_m);


#pragma omp parallel for default(shared) private(z_,x_,offset_min,offset_max) firstprivate(temp_vec,temp_vecm,temp_vecp)
    for(z_ = 0;z_ < z_num_m;z_++){
        //both z and x are explicitly accessed in the structure

        for (int k = 0; k < y_num_m; ++k) {
            temp_vecp[k] = input_img.mesh[z_*x_num_m*y_num_m + k];
            temp_vec[k] = input_img.mesh[z_*x_num_m*y_num_m + k];
        }

        for(x_ = 0;x_ < x_num_m;x_++){

            std::swap(temp_vec,temp_vecm);
            std::swap(temp_vecp,temp_vec);

            offset_max = std::min((int)(x_ + 1),(int)(x_num_m-1));
            //offset_min = std::max((int)(x_ - 1),(int)0);

            //get plus value
            for (int k = 0; k < y_num_m; ++k) {
                temp_vecp[k] = input_img.mesh[z_*x_num_m*y_num_m + offset_max*y_num_m + k];
            }


            for (int k = 0; k < y_num_m; ++k) {

                input_img.mesh[z_*x_num_m*y_num_m + x_*y_num_m + k] = median_3(temp_vec[k],temp_vecp[k],temp_vecm[k]);
            }


        }
    }

    timer.stop_timer();

    time = (timer.t2 - timer.t1);

    std::cout << " Median Filter x took: " << time << std::endl;


#pragma omp parallel for default(shared) private(z_,x_,offset_min,offset_max) firstprivate(temp_vec,temp_vecm,temp_vecp)
    for(x_ = 0;x_ < x_num_m;x_++){
        //both z and x are explicitly accessed in the structure

        for (int k = 0; k < y_num_m; ++k) {
            temp_vecp[k] = input_img.mesh[ x_*y_num_m + k];
            temp_vec[k] = input_img.mesh[ x_*y_num_m + k];
        }

        for(z_ = 0;z_ < z_num_m;z_++){

            std::swap(temp_vec,temp_vecm);
            std::swap(temp_vecp,temp_vec);

            offset_max = std::min((int)(z_ + 1),(int)(z_num_m-1));
            //offset_min = std::max((int)(z_ - 1),(int)0);

            //get plus value
            for (int k = 0; k < y_num_m; ++k) {
                temp_vecp[k] = input_img.mesh[offset_max*x_num_m*y_num_m + x_*y_num_m + k];
            }


            for (int k = 0; k < y_num_m; ++k) {

                input_img.mesh[z_*x_num_m*y_num_m + x_*y_num_m + k] = median_3(temp_vec[k],temp_vecp[k],temp_vecm[k]);
            }


        }
    }

    timer.stop_timer();

    time = (timer.t2 - timer.t1);

    std::cout << " Median Filter z took: " << time << std::endl;


}



void get_variance(Mesh_data<float>& variance_u,cmdLineOptions& options){

    Part_rep part_rep;
    
    get_image_stats(part_rep.pars, options.directory, options.stats);
    
    Mesh_data<float> input_image_float;
    Mesh_data<float> gradient,variance;
    Mesh_data<float> interp_img;
    {
        Mesh_data<uint16_t> input_image;

        load_image_tiff(input_image, options.directory + options.input);

        gradient.initialize(input_image.y_num, input_image.x_num, input_image.z_num, 0);
        part_rep.initialize(input_image.y_num, input_image.x_num, input_image.z_num);

        input_image_float = input_image.to_type<float>();
        interp_img = input_image.to_type<float>();
        // After this block, input_image will be freed.
    }

    if(!options.stats_file) {
        // defaults

        part_rep.pars.dy = part_rep.pars.dx = part_rep.pars.dz = 1;
        part_rep.pars.psfx = part_rep.pars.psfy = part_rep.pars.psfz = 1;
        part_rep.pars.rel_error = 0.1;
        part_rep.pars.var_th = 0;
        part_rep.pars.var_th_max = 0;

        std::cout << "Need status file" << std::endl;

        return;
    }

    Part_timer t;
    t.verbose_flag = true;

    // preallocate_memory
    Particle_map<float> part_map(part_rep);
    preallocate(part_map.layers, gradient.y_num, gradient.x_num, gradient.z_num, part_rep);
    variance.preallocate(gradient.y_num, gradient.x_num, gradient.z_num, 0);
    std::vector<Mesh_data<float>> down_sampled_images;

    Mesh_data<float> temp;
    temp.preallocate(gradient.y_num, gradient.x_num, gradient.z_num, 0);

    t.start_timer("whole");

    part_rep.timer.start_timer("get_gradient_3D");
    get_gradient_3D(part_rep, input_image_float, gradient);
    part_rep.timer.stop_timer();

    part_rep.timer.start_timer("get_variance_3D");
    get_variance_3D(part_rep, input_image_float, variance);
    part_rep.timer.stop_timer();


    int x_dim = ceil(gradient.x_num/2.0)*2;
    int z_dim = ceil(gradient.z_num/2.0)*2;
    int y_dim = ceil(gradient.y_num/2.0)*2;

    variance_u.mesh.resize(x_dim*z_dim*y_dim,0);

    std::vector<unsigned int> dims = {(unsigned int)gradient.y_num,(unsigned int)gradient.x_num,(unsigned int)gradient.z_num};

    const_upsample_img(variance_u,variance,dims);

}

void get_apr(int argc, char **argv,PartCellStructure<float,uint64_t>& pc_struct,cmdLineOptions& options) {

    Part_rep part_rep;

    // INPUT PARSING

    options = read_command_line_options(argc, argv, part_rep);

    int interp_type = 0;

    // COMPUTATIONS

    Mesh_data<float> input_image_float;
    Mesh_data<float> gradient, variance;
    Mesh_data<float> interp_img;
    {
        Mesh_data<uint16_t> input_image;

        load_image_tiff(input_image, options.directory + options.input);

        gradient.initialize(input_image.y_num, input_image.x_num, input_image.z_num, 0);
        part_rep.initialize(input_image.y_num, input_image.x_num, input_image.z_num);

        input_image_float = input_image.to_type<float>();
        interp_img = input_image.to_type<float>();
        // After this block, input_image will be freed.
    }

    if (!options.stats_file) {
        // defaults

        part_rep.pars.dy = part_rep.pars.dx = part_rep.pars.dz = 1;
        part_rep.pars.psfx = part_rep.pars.psfy = part_rep.pars.psfz = 1;
        part_rep.pars.rel_error = 0.1;
        part_rep.pars.var_th = 0;
        part_rep.pars.var_th_max = 0;

        std::cout << "Need status file" << std::endl;

        return;
    }

    Part_timer t;
    t.verbose_flag = true;

    // preallocate_memory
    Particle_map<float> part_map(part_rep);
    preallocate(part_map.layers, gradient.y_num, gradient.x_num, gradient.z_num, part_rep);
    variance.preallocate(gradient.y_num, gradient.x_num, gradient.z_num, 0);
    std::vector<Mesh_data<float>> down_sampled_images;

    Mesh_data<float> temp;
    temp.preallocate(gradient.y_num, gradient.x_num, gradient.z_num, 0);

    t.start_timer("whole");

    if (interp_type == 0) {
        part_map.downsample(interp_img);
        calc_median_filter(part_map.downsampled[part_map.k_max+1]);
    }

    //    std::swap(part_map.downsampled[part_map.k_max+1],input_image_float);

    part_rep.timer.start_timer("get_gradient_3D");
    get_gradient_3D(part_rep, input_image_float, gradient);
    part_rep.timer.stop_timer();

    part_rep.timer.start_timer("get_variance_3D");
    get_variance_3D(part_rep, input_image_float, variance);
    part_rep.timer.stop_timer();

    part_rep.timer.start_timer("get_level_3D");
    get_level_3D(variance, gradient, part_rep, part_map, temp);
    part_rep.timer.stop_timer();

    // free memory (not used anymore)
    std::vector<float>().swap(gradient.mesh);
    std::vector<float>().swap(variance.mesh);

    part_rep.timer.start_timer("pushing_scheme");
    part_map.pushing_scheme(part_rep);
    part_rep.timer.stop_timer();

    if (interp_type == 1) {
        part_map.downsample(input_image_float);
    }
    part_rep.timer.start_timer("Construct Part Structure");

    pc_struct.initialize_structure(part_map);

    part_rep.timer.stop_timer();

    t.stop_timer();

}






#endif //PARTPLAY_APR_PIPELINE_HPP