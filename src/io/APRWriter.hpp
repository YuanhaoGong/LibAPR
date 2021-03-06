//
// Created by cheesema on 14.01.18.
//

#ifndef PARTPLAY_APRWRITER_HPP
#define PARTPLAY_APRWRITER_HPP

#include "hdf5functions_blosc.h"
#include "src/data_structures/APR/APR.hpp"
#include <src/data_structures/APR/APRAccess.hpp>
#include <numeric>

template<typename U>
class APR;


class APRWriter {
public:

    template<typename T> hid_t get_type_data_hdf5(T o){ return 0; };


    template<typename ImageType>
    void read_apr(APR<ImageType>& apr,std::string file_name)
    {

        //currently only supporting 16 bit compress
        APRCompress<ImageType> apr_compress;

        //hdf5 inits
        hid_t fid, pr_groupid, obj_id,attr_id;
        H5G_info_t info;

        //need to register the filters so they work properly
        register_bosc();

        fid = H5Fopen(file_name.c_str(),H5F_ACC_RDONLY,H5P_DEFAULT);

        //Get the group you want to open

        pr_groupid = H5Gopen2(fid,"ParticleRepr",H5P_DEFAULT);
        H5Gget_info( pr_groupid, &info );

        //Getting an attribute
        obj_id =  H5Oopen_by_idx( fid, "ParticleRepr", H5_INDEX_NAME, H5_ITER_INC,0,H5P_DEFAULT);

        //Load the attributes


        /////////////////////////////////////////////
        //  Get metadata
        //
        //////////////////////////////////////////////

        hid_t aid, atype;

        H5Screate(H5S_SCALAR);

        apr.name.reserve(100);

        //std::string string_out;

        //std::vector<char> string_out;
        //string_out.resize(80);

        //atype = H5Tcopy (H5T_C_S1);

        char string_out[100];

        for (int j = 0; j < 100; ++j) {
            string_out[j] = 0;
        }

        attr_id = 	H5Aopen(pr_groupid,"name",H5P_DEFAULT);

        atype = H5Aget_type(attr_id);

        hid_t atype_mem = H5Tget_native_type(atype, H5T_DIR_ASCEND);

        H5Aread(attr_id,atype_mem,string_out) ;
        H5Aclose(attr_id);

        apr.name= string_out;
//        apr.pars.name = string_out;


        attr_id = 	H5Aopen(pr_groupid,"total_number_particles",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.total_number_particles) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"total_number_gaps",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.total_number_gaps) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"total_number_non_empty_rows",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.total_number_non_empty_rows) ;
        H5Aclose(attr_id);

        uint64_t type_size;

        attr_id = 	H5Aopen(pr_groupid,"type_vector_size",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&type_size) ;
        H5Aclose(attr_id);



        attr_id = 	H5Aopen(pr_groupid,"y_num",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.org_dims[0]) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"x_num",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.org_dims[1]) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"z_num",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.org_dims[2]) ;
        H5Aclose(attr_id);


        attr_id = 	H5Aopen(pr_groupid,"level_max",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.level_max) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"level_min",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&apr.apr_access.level_min) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"lambda",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.lambda ) ;
        H5Aclose(attr_id);

        int compress_type;
        attr_id = 	H5Aopen(pr_groupid,"compress_type",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_INT,&compress_type ) ;
        H5Aclose(attr_id);

        float quantization_factor;
        attr_id = 	H5Aopen(pr_groupid,"quantization_factor",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&quantization_factor ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"sigma_th",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.sigma_th ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"sigma_th_max",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.sigma_th_max ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"I_th",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.Ip_th ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"dx",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.dx ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"dy",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.dy ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"dz",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.dz ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"psfx",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.psfx ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"psfy",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.psfy ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"psfz",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.psfz ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"rel_error",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.rel_error ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"background_intensity_estimate",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.background_intensity_estimate ) ;
        H5Aclose(attr_id);

        attr_id = 	H5Aopen(pr_groupid,"noise_sd_estimate",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_FLOAT,&apr.parameters.noise_sd_estimate ) ;
        H5Aclose(attr_id);

        //std::cout << "Number particles: " << num_parts << " Number Cells: " << num_cells << std::endl;

        apr.apr_access.x_num.resize(apr.apr_access.level_max+1);
        apr.apr_access.y_num.resize(apr.apr_access.level_max+1);
        apr.apr_access.z_num.resize(apr.apr_access.level_max+1);

        for(int i = apr.apr_access.level_min;i < apr.apr_access.level_max; i++){

            //get the info

            int x_num;
            std::string name = "x_num_"+std::to_string(i);

            attr_id = 	H5Aopen(pr_groupid,name.c_str(),H5P_DEFAULT);
            H5Aread(attr_id,H5T_NATIVE_INT,&x_num) ;
            H5Aclose(attr_id);

            int y_num;
            name = "y_num_"+std::to_string(i);

            attr_id = 	H5Aopen(pr_groupid,name.c_str(),H5P_DEFAULT);
            H5Aread(attr_id,H5T_NATIVE_INT,&y_num) ;
            H5Aclose(attr_id);

            int z_num;
            name = "z_num_"+std::to_string(i);

            attr_id = 	H5Aopen(pr_groupid,name.c_str(),H5P_DEFAULT);
            H5Aread(attr_id,H5T_NATIVE_INT,&z_num) ;
            H5Aclose(attr_id);


            apr.apr_access.x_num[i] = x_num;
            apr.apr_access.y_num[i] = y_num;
            apr.apr_access.z_num[i] = z_num;

        }


        aid = H5Screate(H5S_SCALAR);

        int data_type;

        attr_id = 	H5Aopen(pr_groupid,"data_type",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_INT,&data_type ) ;
        H5Aclose(attr_id);

        hid_t hdf5_data_type = 0;

        apr.particles_intensities.data.resize(apr.apr_access.total_number_particles);

        if(apr.particles_intensities.data.size()>0){
            std::string name = "particle_intensities";
            hdf5_load_data_blosc(obj_id,hdf5_data_type,apr.particles_intensities.data.data(),name.c_str());
        }


        apr.apr_access.y_num[apr.apr_access.level_max] = apr.apr_access.org_dims[0];
        apr.apr_access.x_num[apr.apr_access.level_max] = apr.apr_access.org_dims[1];
        apr.apr_access.z_num[apr.apr_access.level_max] = apr.apr_access.org_dims[2];

        MapStorageData* map_data = new MapStorageData();
        //all the access map data

        map_data->global_index.resize(apr.apr_access.total_number_gaps);

        std::vector<int16_t> index_delta;
        index_delta.resize(apr.apr_access.total_number_gaps);

        std::string dataset_name = "map_global_index";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_INT16,index_delta.data(),dataset_name.c_str());

        std::vector<uint64_t> index_delta_big;
        index_delta_big.resize(apr.apr_access.total_number_gaps);
        std::copy(index_delta.begin(),index_delta.end(),index_delta_big.begin());
        std::partial_sum(index_delta_big.begin(),index_delta_big.end(),map_data->global_index.begin());

        map_data->y_end.resize(apr.apr_access.total_number_gaps);
        dataset_name = "map_y_end";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT16,map_data->y_end.data(),dataset_name.c_str());


        map_data->y_begin.resize(apr.apr_access.total_number_gaps);
        dataset_name = "map_y_begin";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT16,map_data->y_begin.data(),dataset_name.c_str());

        map_data->number_gaps.resize(apr.apr_access.total_number_non_empty_rows);
        dataset_name = "map_number_gaps";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT16,map_data->number_gaps.data(),dataset_name.c_str());

        map_data->level.resize(apr.apr_access.total_number_non_empty_rows);
        dataset_name = "map_level";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT8,map_data->level.data(),dataset_name.c_str());

        map_data->x.resize(apr.apr_access.total_number_non_empty_rows);
        dataset_name = "map_x";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT16,map_data->x.data(),dataset_name.c_str());

        map_data->z.resize(apr.apr_access.total_number_non_empty_rows);
        dataset_name = "map_z";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT16,map_data->z.data(),dataset_name.c_str());

        apr.apr_access.particle_cell_type.data.resize(type_size);
        dataset_name = "particle_cell_type";
        hdf5_load_data_blosc(obj_id,H5T_NATIVE_UINT8,apr.apr_access.particle_cell_type.data.data(),dataset_name.c_str());


        apr.apr_access.rebuild_map(apr, *map_data);


        //close shiz
        H5Gclose(obj_id);
        H5Gclose(pr_groupid);
        H5Fclose(fid);

        //
        //
        //  Decompress if needed
        //
        //

        if(compress_type > 0){
            apr_compress.set_compression_type(compress_type);
            apr_compress.set_quantization_factor(quantization_factor);

            apr_compress.decompress(apr,apr.particles_intensities);

        }

    }

    template<typename ImageType>
    void write_apr(APR<ImageType>& apr,std::string save_loc,std::string file_name){
        //compress
        APRCompress<ImageType> apr_compressor;
        apr_compressor.set_compression_type(0);

        write_apr(apr,save_loc,file_name,apr_compressor);

    }

    template<typename ImageType>
    float write_apr(APR<ImageType>& apr,std::string save_loc,std::string file_name,APRCompress<ImageType>& apr_compressor,unsigned int blosc_comp_type = BLOSC_ZSTD,unsigned int blosc_comp_level = 2,unsigned int blosc_shuffle=1){
        //
        //
        //  Bevan Cheeseman 2018
        //
        //  Writes the APR to the particle cell structure sparse format, using the p_map for reconstruction
        //
        //

        int compress_type_num = apr_compressor.get_compression_type();
        float quantization_factor = apr_compressor.get_quantization_factor();

        APRTimer write_timer;

        write_timer.verbose_flag = false;

        //Neighbour Routine Checking
        register_bosc();

        std::string hdf5_file_name = save_loc + file_name + "_apr.h5";

        file_name = file_name + "_apr";

        hdf5_create_file_blosc(hdf5_file_name);

        //hdf5 inits
        hid_t fid, pr_groupid, obj_id;
        H5G_info_t info;

        hsize_t     dims_out[2];

        hsize_t rank = 1;

        hsize_t dims;
        hsize_t dim_a=1;

        fid = H5Fopen(hdf5_file_name.c_str(),H5F_ACC_RDWR,H5P_DEFAULT);

        //Get the group you want to open

        //////////////////////////////////////////////////////////////////
        //
        //  Write meta-data to the file
        //
        //
        //
        ///////////////////////////////////////////////////////////////////////
        dims = 1;

        pr_groupid = H5Gcreate2(fid,"ParticleRepr",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
        H5Gget_info( pr_groupid, &info );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"x_num",1,&dims, &apr.apr_access.org_dims[1] );
        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"y_num",1,&dims, &apr.apr_access.org_dims[0] );
        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"z_num",1,&dims, &apr.apr_access.org_dims[2] );


        obj_id = H5Gcreate2(fid,"ParticleRepr/t",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);

        dims_out[0] = 1;
        dims_out[1] = 1;

        //just an identifier in here for the reading of the parts

        uint64_t total_number_parts = apr.apr_access.total_number_particles;
        uint64_t total_number_gaps = apr.apr_access.total_number_gaps;
        uint64_t total_number_non_empty_rows = apr.apr_access.total_number_non_empty_rows;
        uint64_t type_vector_size = apr.apr_access.particle_cell_type.data.size();

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"total_number_particles",1,dims_out, &total_number_parts );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"total_number_gaps",1,dims_out, &total_number_gaps );
        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"total_number_non_empty_rows",1,dims_out, &total_number_non_empty_rows );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"type_vector_size",1,dims_out, &type_vector_size );

        // New parameter and background data

        if(apr.name.size() == 0){
            apr.name = "no_name";
        }

        hdf5_write_string_blosc(pr_groupid,"name",apr.name);

        std::string git_hash = exec_blosc("git rev-parse HEAD");

        hdf5_write_string_blosc(pr_groupid,"githash",git_hash);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,"compress_type",1,dims_out, &compress_type_num);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"quantization_factor",1,dims_out, &quantization_factor);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"lambda",1,dims_out, &apr.parameters.lambda );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"sigma_th",1,dims_out, &apr.parameters.sigma_th );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"sigma_th_max",1,dims_out, &apr.parameters.sigma_th_max );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"I_th",1,dims_out, &apr.parameters.Ip_th );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"dx",1,dims_out, &apr.parameters.dx );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"dy",1,dims_out, &apr.parameters.dy );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"dz",1,dims_out, &apr.parameters.dz );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"psfx",1,dims_out, &apr.parameters.psfx );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"psfy",1,dims_out, &apr.parameters.psfy );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"psfz",1,dims_out, &apr.parameters.psfz );

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"rel_error",1,dims_out, &apr.parameters.rel_error);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"noise_sd_estimate",1,dims_out, &apr.parameters.noise_sd_estimate);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_FLOAT,"background_intensity_estimate",1,dims_out, &apr.parameters.background_intensity_estimate);

        //////////////////////////////////////////////////////////////////
        //
        //  Write data to the file
        //
        //
        //
        ///////////////////////////////////////////////////////////////////////

        write_timer.start_timer("intensities");

        if(compress_type_num > 0){
            apr_compressor.compress(apr,apr.particles_intensities);
        }

        dims = apr.particles_intensities.data.size();

        //just an identifier in here for the reading of the parts
        ImageType val = 0;
        hid_t type = get_type_data_hdf5(val);
        int type_id = sizeof(val);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT,"data_type",1,dims_out, &type_id);

        if(dims > 0){
            //write the parts

            std::string dataset_name = "particle_intensities";
            hdf5_write_data_blosc(obj_id, type, dataset_name.c_str(), rank, &dims, apr.particles_intensities.data.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        }

        write_timer.stop_timer();

        write_timer.start_timer("access_data");

        MapStorageData map_data;
        apr.apr_access.flatten_structure(apr,map_data);

        //number of gaps
        blosc_comp_level=3;
        blosc_shuffle = 1;
        blosc_comp_type = BLOSC_ZSTD;

        std::vector<uint16_t> index_delta;
        index_delta.resize(map_data.global_index.size());

        std::adjacent_difference(map_data.global_index.begin(),map_data.global_index.end(),index_delta.begin());

        dims = map_data.global_index.size();
        std::string dataset_name = "map_global_index";
        //hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT64, dataset_name.c_str(), rank, &dims, index_delta.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, dataset_name.c_str(), rank, &dims, index_delta.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);



        dims = map_data.y_end.size();
        dataset_name = "map_y_end";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, dataset_name.c_str(), rank, &dims,  map_data.y_end.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);


        dims = map_data.y_begin.size();
        dataset_name = "map_y_begin";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, dataset_name.c_str(), rank, &dims,  map_data.y_begin.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        //number of non-zero rows
        dims = map_data.number_gaps.size();
        dataset_name = "map_number_gaps";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, dataset_name.c_str(), rank, &dims,  map_data.number_gaps.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        dims = map_data.level.size();
        dataset_name = "map_level";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT8, dataset_name.c_str(), rank, &dims,  map_data.level.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        dims = map_data.x.size();
        dataset_name = "map_x";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, dataset_name.c_str(), rank, &dims,  map_data.x.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        dims = map_data.z.size();
        dataset_name = "map_z";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, dataset_name.c_str(), rank, &dims,  map_data.z.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        dims =apr.apr_access.particle_cell_type.data.size();
        dataset_name = "particle_cell_type";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT8, dataset_name.c_str(), rank, &dims,  apr.apr_access.particle_cell_type.data.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        write_timer.stop_timer();

        for (int i = apr.level_min(); i <apr.level_max() ; ++i) {
            std::string name = "x_num_"+std::to_string(i);
            hsize_t attr = apr.apr_access.x_num[i];
            hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,name.c_str(),1,&dim_a, &attr);

            attr = apr.apr_access.y_num[i];
            name = "y_num_"+std::to_string(i);
            hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,name.c_str(),1,&dim_a, &attr);

            attr =apr.apr_access.z_num[i];
            name = "z_num_"+std::to_string(i);
            hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,name.c_str(),1,&dim_a, &attr);
        }

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"level_max",1,&dim_a, &apr.apr_access.level_max );
        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"level_min",1,&dim_a, &apr.apr_access.level_min );

        // output the file size
        hsize_t file_size;
        H5Fget_filesize(fid, &file_size);

        std::cout << "HDF5 Filesize: " << file_size*1.0/1000000.0 << " MB" << std::endl;

        //close shiz
        H5Gclose(obj_id);
        H5Gclose(pr_groupid);
        H5Fclose(fid);

        std::cout << "Writing Complete" << std::endl;

        return file_size*1.0/1000000.0; //filesize in MB

    }

    template<typename ImageType,typename T>
    void write_apr_paraview(APR<ImageType>& apr,std::string save_loc,std::string file_name,ExtraParticleData<T>& parts){
        //
        //
        //  Bevan Cheeseman 2018
        //
        //  Writes the APR and Extra PartCell Data to
        //
        //

        unsigned int blosc_comp_type = BLOSC_ZSTD;
        unsigned int blosc_comp_level = 1;
        unsigned int blosc_shuffle = 2;

        APRTimer write_timer;

        write_timer.verbose_flag = false;

        //Neighbour Routine Checking
        register_bosc();

        std::string hdf5_file_name = save_loc + file_name + "_paraview.h5";

        file_name = file_name + "_paraview";

        hdf5_create_file_blosc(hdf5_file_name);

        //hdf5 inits
        hid_t fid, pr_groupid, obj_id;
        H5G_info_t info;

        hsize_t     dims_out[2];

        hsize_t rank = 1;

        hsize_t dims;
        hsize_t dim_a=1;

        fid = H5Fopen(hdf5_file_name.c_str(),H5F_ACC_RDWR,H5P_DEFAULT);

        //Get the group you want to open

        //////////////////////////////////////////////////////////////////
        //
        //  Write meta-data to the file
        //
        //
        //
        ///////////////////////////////////////////////////////////////////////
        dims = 1;

        pr_groupid = H5Gcreate2(fid,"ParticleRepr",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
        H5Gget_info( pr_groupid, &info );

        obj_id = H5Gcreate2(fid,"ParticleRepr/t",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);

        dims_out[0] = 1;
        dims_out[1] = 1;

        //just an identifier in here for the reading of the parts


        int num_parts = apr.apr_access.total_number_particles;

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"total_number_particles",1,dims_out, &num_parts );

        // New parameter and background data

        if(apr.name.size() == 0){
            apr.name = "no_name";
        }

        hdf5_write_string_blosc(pr_groupid,"name",apr.name);

        std::string git_hash = exec_blosc("git rev-parse HEAD");

        hdf5_write_string_blosc(pr_groupid,"githash",git_hash);

        //////////////////////////////////////////////////////////////////
        //
        //  Write data to the file
        //
        //
        //
        ///////////////////////////////////////////////////////////////////////

        //write the parts
        std::string name = "particle property";

        T type_example = 0;
        hid_t data_type =  get_type_data_hdf5(type_example);

        APRIterator<ImageType> apr_iterator(apr);

        dims = apr_iterator.total_number_particles();
        hdf5_write_data_blosc(obj_id, data_type, name.c_str(), rank, &dims, parts.data.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        std::vector<uint16_t> xv;
        xv.resize(apr_iterator.total_number_particles());

        std::vector<uint16_t> yv;
        yv.resize(apr_iterator.total_number_particles());

        std::vector<uint16_t> zv;
        zv.resize(apr_iterator.total_number_particles());

        std::vector<uint8_t> levelv;
        levelv.resize(apr_iterator.total_number_particles());

        std::vector<uint8_t> typev;
        typev.resize(apr_iterator.total_number_particles());

        uint64_t particle_number = 0;
#ifdef HAVE_OPENMP
	#pragma omp parallel for schedule(static) private(particle_number) firstprivate(apr_iterator)
#endif
        for (particle_number= 0; particle_number < apr_iterator.total_number_particles(); ++particle_number) {
            apr_iterator.set_iterator_to_particle_by_number(particle_number);

            xv[particle_number] = apr_iterator.x_global();
            yv[particle_number] = apr_iterator.y_global();
            zv[particle_number] = apr_iterator.z_global();
            levelv[particle_number] = apr_iterator.level();
            typev[particle_number] = apr_iterator.type();

        }



        name = "x";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, name.c_str(), rank, &dims, xv.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        name = "y";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, name.c_str(), rank, &dims, yv.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        name = "z";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT16, name.c_str(), rank, &dims, zv.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        name = "level";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT8, name.c_str(), rank, &dims, levelv.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        name = "type";
        hdf5_write_data_blosc(obj_id, H5T_NATIVE_UINT8, name.c_str(), rank, &dims, typev.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,"level_max",1,&dim_a, &apr.apr_access.level_max );
        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,"level_min",1,&dim_a, &apr.apr_access.level_min );

        // output the file size
        hsize_t file_size;
        H5Fget_filesize(fid, &file_size);

        std::cout << "HDF5 Filesize: " << file_size*1.0/1000000.0 << " MB" << std::endl;

        // #TODO This needs to be able extended to handle more general type, currently it is assuming uint16
        write_main_paraview_xdmf_xml(save_loc,file_name,apr_iterator.total_number_particles());

        //close shiz
        H5Gclose(obj_id);
        H5Gclose(pr_groupid);
        H5Fclose(fid);

        std::cout << "Writing Complete" << std::endl;

    }

    template<typename S>
    float write_particles_only(std::string save_loc,std::string file_name,ExtraParticleData<S>& parts_extra){
        //
        //
        //  Bevan Cheeseman 2018
        //
        //  Writes only the particle data, requires the same APR to be read in correctly.
        //
        //
        //
        //

        //Neighbour Routine Checking

        register_bosc();

        std::string hdf5_file_name = save_loc + file_name + "_apr_extra_parts.h5";

        file_name = file_name + "_apr_extra_parts";

        hdf5_create_file_blosc(hdf5_file_name);

        //hdf5 inits
        hid_t fid, pr_groupid, obj_id;
        H5G_info_t info;

        hsize_t     dims_out[2];

        hsize_t rank = 1;

        hsize_t dims;

        fid = H5Fopen(hdf5_file_name.c_str(),H5F_ACC_RDWR,H5P_DEFAULT);

        //Get the group you want to open

        //////////////////////////////////////////////////////////////////
        //
        //  Write meta-data to the file
        //
        //
        //
        ///////////////////////////////////////////////////////////////////////
        dims = 1;

        pr_groupid = H5Gcreate2(fid,"ParticleRepr",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
        H5Gget_info( pr_groupid, &info );


        obj_id = H5Gcreate2(fid,"ParticleRepr/t",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);

        dims_out[0] = 1;
        dims_out[1] = 1;

        //just an identifier in here for the reading of the parts
        S val = 0;
        hid_t type_id = get_type_blosc(val);
        hid_t type = get_type_data_hdf5(val);

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_INT,"data_type",1,dims_out, &type_id);

        uint64_t total_number_parts = parts_extra.data.size();

        hdf5_write_attribute_blosc(pr_groupid,H5T_NATIVE_UINT64,"total_number_particles",1,dims_out, &total_number_parts );

        //////////////////////////////////////////////////////////////////
        //
        //  Write data to the file
        //
        //
        //
        ///////////////////////////////////////////////////////////////////////

        unsigned int blosc_comp_type = BLOSC_ZSTD;
        unsigned int blosc_comp_level = 3;
        unsigned int blosc_shuffle = 2;

        dims = total_number_parts;
        std::string name = "extra_particle_data";
        hdf5_write_data_blosc(obj_id, type, name.c_str(), rank, &dims, parts_extra.data.data(),blosc_comp_type,blosc_comp_level,blosc_shuffle);


        // New parameter and background data

        std::string git_hash = exec_blosc("git rev-parse HEAD");

        hdf5_write_string_blosc(pr_groupid,"githash",git_hash);

        // output the file size
        hsize_t file_size;
        H5Fget_filesize(fid, &file_size);

        std::cout << "HDF5 Filesize: " << file_size*1.0/1000000.0 << " MB" << std::endl;

        //close shiz
        H5Gclose(obj_id);
        H5Gclose(pr_groupid);
        H5Fclose(fid);

        std::cout << "Writing ExtraPartCellData Complete" << std::endl;

        return file_size*1.0/1000000.0; //returns file size in MB

    }

    template<typename T>
    void read_parts_only(std::string file_name,ExtraParticleData<T>& extra_parts)
    {

        //hdf5 inits
        hid_t fid, pr_groupid, obj_id,attr_id;
        H5G_info_t info;

        //need to register the filters so they work properly
        register_bosc();

        fid = H5Fopen(file_name.c_str(),H5F_ACC_RDONLY,H5P_DEFAULT);

        //Get the group you want to open

        pr_groupid = H5Gopen2(fid,"ParticleRepr",H5P_DEFAULT);
        H5Gget_info( pr_groupid, &info );

        //Getting an attribute
        obj_id =  H5Oopen_by_idx( fid, "ParticleRepr", H5_INDEX_NAME, H5_ITER_INC,0,H5P_DEFAULT);

        //Load the attributes
        std::string name;

        /////////////////////////////////////////////
        //  Get metadata
        //
        //////////////////////////////////////////////
        uint64_t total_number_parts;
        attr_id = 	H5Aopen(pr_groupid,"total_number_particles",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_UINT64,&total_number_parts) ;
        H5Aclose(attr_id);

        hid_t       aid;

        aid = H5Screate(H5S_SCALAR);

        int data_type;

        attr_id = 	H5Aopen(pr_groupid,"data_type",H5P_DEFAULT);
        H5Aread(attr_id,H5T_NATIVE_INT,&data_type ) ;
        H5Aclose(attr_id);

        extra_parts.data.resize(total_number_parts);
        std::string dataset_name = "extra_particle_data";
        hdf5_load_data_blosc(obj_id,data_type,extra_parts.data.data(),dataset_name.c_str());

        //close shiz
        H5Gclose(obj_id);
        H5Gclose(pr_groupid);
        H5Fclose(fid);

    };
};

template<>
hid_t APRWriter::get_type_data_hdf5<uint8_t>(uint8_t o){
    return H5T_NATIVE_UINT8;
};

template<>
hid_t APRWriter::get_type_data_hdf5<uint16_t>(uint16_t o){
    return H5T_NATIVE_UINT16;
};

template<>
hid_t APRWriter::get_type_data_hdf5<int16_t>(int16_t o){
    return H5T_NATIVE_INT16;
};

template<>
hid_t APRWriter::get_type_data_hdf5<float>(float o){
    return H5T_NATIVE_FLOAT;
};

template<>
hid_t APRWriter::get_type_data_hdf5<int>(int o){
    return H5T_NATIVE_INT;
};

template<>
hid_t APRWriter::get_type_data_hdf5<unsigned int>(unsigned int o){
    return H5T_NATIVE_UINT;
};

template<>
hid_t APRWriter::get_type_data_hdf5<double>(double o){
    return H5T_NATIVE_DOUBLE;
};

template<>
hid_t APRWriter::get_type_data_hdf5<int8_t>(int8_t o){
    return H5T_NATIVE_INT8;
};

template<>
hid_t APRWriter::get_type_data_hdf5<uint64_t>(uint64_t o){
    return H5T_NATIVE_UINT64;
};


#endif //PARTPLAY_APRWRITER_HPP
