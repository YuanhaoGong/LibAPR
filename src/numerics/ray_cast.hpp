#ifndef _ray_cast_num_h
#define _ray_cast_num_h
//////////////////////////////////////////////////
//
//
//  Bevan Cheeseman 2016
//
//  Ray casting numerics
//
//
//////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

#include "../data_structures/Tree/PartCellStructure.hpp"
#include "../data_structures/Tree/ExtraPartCellData.hpp"
#include "../data_structures/Tree/PartCellParent.hpp"

#include "filter_help/CurrLevel.hpp"
#include "filter_help/NeighOffset.hpp"

#include "../../test/utils.h"

template<typename S>
void single_ray_parrallel(PartCellStructure<S,uint64_t>& pc_struct){
    //
    //  Bevan Cheeseman 2017
    //
    //  Simple ray case example, signle ray, accumulating, parralell projection
    //
    //
    
    
    //////////////////////////////
    //
    //  This creates data sets where each particle is a cell.
    //
    //  This same code can be used where there are multiple particles per cell as in original pc_struct, however, the particles have to be accessed in a different way.
    //
    //////////////////////////////
    
    
    ParticleDataNew<float, uint64_t> part_new;
    //flattens format to particle = cell, this is in the classic access/part paradigm
    part_new.initialize_from_structure(pc_struct);
    
    //generates the nieghbour structure
    PartCellData<uint64_t> pc_data;
    part_new.create_pc_data_new(pc_data);
    
    //Genearate particle at cell locations, easier access
    ExtraPartCellData<float> particles_int;
    part_new.create_particles_at_cell_structure(particles_int);
    
    PartCellParent<uint64_t> parent_cells(pc_data);
    
    CurrentLevel<float,uint64_t> curr_level;
    
    //random seed
    srand ((unsigned int)time(NULL));
    
    //chose a point within the domain
    uint64_t x = rand()%(pc_struct.org_dims[1]*2), y = rand()%(pc_struct.org_dims[0]*2), z = rand()%(pc_struct.org_dims[2]*2);
    
    uint64_t init_key = parent_cells.find_partcell(x, y, z, pc_data);
    
    if(init_key > 0){
        //above zero means the location is inside the domain
        
        curr_level.init(init_key,pc_data);
        
        bool end_domain = false;
        
        unsigned int direction = rand()%6;
        unsigned int index = rand()%4;
        
        int counter =0;
        float accum_int = 0;
        
        while(!end_domain){
            //iterate through domain until you hit the edge
            end_domain = curr_level.move_cell(direction,index,part_new,pc_data);
            //get the intensity of the particle
            accum_int += curr_level.get_val(particles_int);
            counter++;
        }
        
        std::cout << "moved " << counter << " times through the domain" << std::endl;
        std::cout << "accumulated " << accum_int << " intensity" << std::endl;
        
    } else {
        std::cout << "outside domain" << std::endl;
    }

    
}

























#endif