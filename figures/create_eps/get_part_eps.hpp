//
// Created by cheesema on 21/02/17.
//

#ifndef PARTPLAY_GET_PART_EPS_HPP
#define PARTPLAY_GET_PART_EPS_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#include "../../src/data_structures/Tree/PartCellStructure.hpp"
#include "../../src/data_structures/Tree/ExtraPartCellData.hpp"
#include "../../src/data_structures/Tree/PartCellParent.hpp"

using namespace LibBoard;
using namespace std;

void GroundColorMix(double* color, double x, double min, double max)
{
    /*
     * Red = 0
     * Green = 1
     * Blue = 2
     */
    double posSlope = (max-min)/60;
    double negSlope = (min-max)/60;

    if( x < 60 )
    {
        color[0] = max;
        color[1] = posSlope*x+min;
        color[2] = min;
        return;
    }
    else if ( x < 120 )
    {
        color[0] = negSlope*x+2*max+min;
        color[1] = max;
        color[2] = min;
        return;
    }
    else if ( x < 180  )
    {
        color[0] = min;
        color[1] = max;
        color[2] = posSlope*x-2*max+min;
        return;
    }
    else if ( x < 240  )
    {
        color[0] = min;
        color[1] = negSlope*x+4*max+min;
        color[2] = max;
        return;
    }
    else if ( x < 300  )
    {
        color[0] = posSlope*x-4*max+min;
        color[1] = min;
        color[2] = max;
        return;
    }
    else
    {
        color[0] = max;
        color[1] = min;
        color[2] = negSlope*x+6*max;
        return;
    }
}
void BWColorMix(double* color, double x, double min, double max)
{
    /*
     * Red = 0
     * Green = 1
     * Blue = 2
     */
    double posSlope = (max-min)/60;
    double negSlope = (min-max)/60;

    color[0] = posSlope*x+min;
    color[1] = posSlope*x+min;
    color[2] = posSlope*x+min;
    return;


}

void ParulaColorMix(double* color, double x, double min, double max,bool invert = false)
{
    /*
     * Red = 0
     * Green = 1
     * Blue = 2
     */

    std::vector<float> col_1 =
            {0.208100000000000
                    ,0.209100000000000
                    ,0.210100000000000
                    ,0.210900000000000
                    ,0.211600000000000
                    ,0.212100000000000
                    ,0.212400000000000
                    ,0.212500000000000
                    ,0.212300000000000
                    ,0.211800000000000
                    ,0.211100000000000
                    ,0.209900000000000
                    ,0.208400000000000
                    ,0.206300000000000
                    ,0.203800000000000
                    ,0.200600000000000
                    ,0.196800000000000
                    ,0.192100000000000
                    ,0.186700000000000
                    ,0.180200000000000
                    ,0.172800000000000
                    ,0.164100000000000
                    ,0.154100000000000
                    ,0.142700000000000
                    ,0.129500000000000
                    ,0.114700000000000
                    ,0.0986000000000000
                    ,0.0816000000000000
                    ,0.0646000000000000
                    ,0.0482000000000000
                    ,0.0329000000000000
                    ,0.0213000000000000
                    ,0.0136000000000000
                    ,0.00860000000000000
                    ,0.00600000000000000
                    ,0.00510000000000000
                    ,0.00540000000000000
                    ,0.00670000000000000
                    ,0.00890000000000000
                    ,0.0116000000000000
                    ,0.0148000000000000
                    ,0.0184000000000000
                    ,0.0223000000000000
                    ,0.0264000000000000
                    ,0.0306000000000000
                    ,0.0349000000000000
                    ,0.0394000000000000
                    ,0.0437000000000000
                    ,0.0477000000000000
                    ,0.0514000000000000
                    ,0.0549000000000000
                    ,0.0582000000000000
                    ,0.0612000000000000
                    ,0.0640000000000000
                    ,0.0666000000000000
                    ,0.0689000000000000
                    ,0.0710000000000000
                    ,0.0729000000000000
                    ,0.0746000000000000
                    ,0.0761000000000000
                    ,0.0773000000000000
                    ,0.0782000000000000
                    ,0.0789000000000000
                    ,0.0794000000000000
                    ,0.0795000000000000
                    ,0.0793000000000000
                    ,0.0788000000000000
                    ,0.0778000000000000
                    ,0.0764000000000000
                    ,0.0746000000000000
                    ,0.0724000000000000
                    ,0.0698000000000000
                    ,0.0668000000000000
                    ,0.0636000000000000
                    ,0.0600000000000000
                    ,0.0562000000000000
                    ,0.0523000000000000
                    ,0.0484000000000000
                    ,0.0445000000000000
                    ,0.0408000000000000
                    ,0.0372000000000000
                    ,0.0342000000000000
                    ,0.0317000000000000
                    ,0.0296000000000000
                    ,0.0279000000000000
                    ,0.0265000000000000
                    ,0.0255000000000000
                    ,0.0248000000000000
                    ,0.0243000000000000
                    ,0.0239000000000000
                    ,0.0237000000000000
                    ,0.0235000000000000
                    ,0.0233000000000000
                    ,0.0231000000000000
                    ,0.0230000000000000
                    ,0.0229000000000000
                    ,0.0227000000000000
                    ,0.0227000000000000
                    ,0.0232000000000000
                    ,0.0238000000000000
                    ,0.0246000000000000
                    ,0.0263000000000000
                    ,0.0282000000000000
                    ,0.0306000000000000
                    ,0.0338000000000000
                    ,0.0373000000000000
                    ,0.0418000000000000
                    ,0.0467000000000000
                    ,0.0516000000000000
                    ,0.0574000000000000
                    ,0.0629000000000000
                    ,0.0692000000000000
                    ,0.0755000000000000
                    ,0.0820000000000000
                    ,0.0889000000000000
                    ,0.0956000000000000
                    ,0.103100000000000
                    ,0.110400000000000
                    ,0.118000000000000
                    ,0.125800000000000
                    ,0.133500000000000
                    ,0.141800000000000
                    ,0.149900000000000
                    ,0.158500000000000
                    ,0.167100000000000
                    ,0.175800000000000
                    ,0.184900000000000
                    ,0.193800000000000
                    ,0.203300000000000
                    ,0.212800000000000
                    ,0.222400000000000
                    ,0.232400000000000
                    ,0.242300000000000
                    ,0.252700000000000
                    ,0.263100000000000
                    ,0.273500000000000
                    ,0.284500000000000
                    ,0.295300000000000
                    ,0.306400000000000
                    ,0.317700000000000
                    ,0.328900000000000
                    ,0.340500000000000
                    ,0.352000000000000
                    ,0.363500000000000
                    ,0.375300000000000
                    ,0.386900000000000
                    ,0.398600000000000
                    ,0.410300000000000
                    ,0.421800000000000
                    ,0.433400000000000
                    ,0.444700000000000
                    ,0.456100000000000
                    ,0.467200000000000
                    ,0.478300000000000
                    ,0.489200000000000
                    ,0.500000000000000
                    ,0.510600000000000
                    ,0.521200000000000
                    ,0.531500000000000
                    ,0.541800000000000
                    ,0.551900000000000
                    ,0.561900000000000
                    ,0.571800000000000
                    ,0.581600000000000
                    ,0.591300000000000
                    ,0.600900000000000
                    ,0.610300000000000
                    ,0.619700000000000
                    ,0.629000000000000
                    ,0.638200000000000
                    ,0.647300000000000
                    ,0.656400000000000
                    ,0.665300000000000
                    ,0.674200000000000
                    ,0.683000000000000
                    ,0.691800000000000
                    ,0.700400000000000
                    ,0.709100000000000
                    ,0.717600000000000
                    ,0.726100000000000
                    ,0.734600000000000
                    ,0.743000000000000
                    ,0.751300000000000
                    ,0.759600000000000
                    ,0.767900000000000
                    ,0.776100000000000
                    ,0.784300000000000
                    ,0.792400000000000
                    ,0.800500000000000
                    ,0.808500000000000
                    ,0.816600000000000
                    ,0.824600000000000
                    ,0.832500000000000
                    ,0.840500000000000
                    ,0.848400000000000
                    ,0.856300000000000
                    ,0.864200000000000
                    ,0.872000000000000
                    ,0.879800000000000
                    ,0.887700000000000
                    ,0.895400000000000
                    ,0.903200000000000
                    ,0.911000000000000
                    ,0.918700000000000
                    ,0.926400000000000
                    ,0.934100000000000
                    ,0.941700000000000
                    ,0.949300000000000
                    ,0.956700000000000
                    ,0.963900000000000
                    ,0.970800000000000
                    ,0.977300000000000
                    ,0.983100000000000
                    ,0.988200000000000
                    ,0.992200000000000
                    ,0.995200000000000
                    ,0.997300000000000
                    ,0.998600000000000
                    ,0.999100000000000
                    ,0.999000000000000
                    ,0.998500000000000
                    ,0.997600000000000
                    ,0.996400000000000
                    ,0.995000000000000
                    ,0.993300000000000
                    ,0.991400000000000
                    ,0.989400000000000
                    ,0.987300000000000
                    ,0.985100000000000
                    ,0.982800000000000
                    ,0.980500000000000
                    ,0.978200000000000
                    ,0.975900000000000
                    ,0.973600000000000
                    ,0.971300000000000
                    ,0.969200000000000
                    ,0.967200000000000
                    ,0.965400000000000
                    ,0.963800000000000
                    ,0.962300000000000
                    ,0.961100000000000
                    ,0.960000000000000
                    ,0.959300000000000
                    ,0.958800000000000
                    ,0.958600000000000
                    ,0.958700000000000
                    ,0.959100000000000
                    ,0.959900000000000
                    ,0.961000000000000
                    ,0.962400000000000
                    ,0.964100000000000
                    ,0.966200000000000
                    ,0.968500000000000
                    ,0.971000000000000
                    ,0.973600000000000
                    ,0.976300000000000};

    std::vector<float> col_2 =
            {0.166300000000000
                    ,0.172100000000000
                    ,0.177900000000000
                    ,0.183700000000000
                    ,0.189500000000000
                    ,0.195400000000000
                    ,0.201300000000000
                    ,0.207200000000000
                    ,0.213200000000000
                    ,0.219200000000000
                    ,0.225300000000000
                    ,0.231500000000000
                    ,0.237700000000000
                    ,0.244000000000000
                    ,0.250300000000000
                    ,0.256800000000000
                    ,0.263200000000000
                    ,0.269800000000000
                    ,0.276400000000000
                    ,0.283200000000000
                    ,0.290200000000000
                    ,0.297500000000000
                    ,0.305200000000000
                    ,0.313200000000000
                    ,0.321700000000000
                    ,0.330600000000000
                    ,0.339700000000000
                    ,0.348600000000000
                    ,0.357200000000000
                    ,0.365100000000000
                    ,0.372400000000000
                    ,0.379200000000000
                    ,0.385300000000000
                    ,0.391100000000000
                    ,0.396500000000000
                    ,0.401700000000000
                    ,0.406600000000000
                    ,0.411300000000000
                    ,0.415900000000000
                    ,0.420300000000000
                    ,0.424600000000000
                    ,0.428800000000000
                    ,0.432900000000000
                    ,0.437000000000000
                    ,0.441000000000000
                    ,0.444900000000000
                    ,0.448800000000000
                    ,0.452600000000000
                    ,0.456400000000000
                    ,0.460200000000000
                    ,0.464000000000000
                    ,0.467700000000000
                    ,0.471400000000000
                    ,0.475100000000000
                    ,0.478800000000000
                    ,0.482500000000000
                    ,0.486200000000000
                    ,0.489900000000000
                    ,0.493700000000000
                    ,0.497400000000000
                    ,0.501200000000000
                    ,0.505100000000000
                    ,0.508900000000000
                    ,0.512900000000000
                    ,0.516900000000000
                    ,0.521000000000000
                    ,0.525100000000000
                    ,0.529500000000000
                    ,0.533900000000000
                    ,0.538400000000000
                    ,0.543100000000000
                    ,0.547900000000000
                    ,0.552700000000000
                    ,0.557700000000000
                    ,0.562700000000000
                    ,0.567700000000000
                    ,0.572700000000000
                    ,0.577700000000000
                    ,0.582600000000000
                    ,0.587400000000000
                    ,0.592200000000000
                    ,0.596800000000000
                    ,0.601200000000000
                    ,0.605500000000000
                    ,0.609700000000000
                    ,0.613700000000000
                    ,0.617600000000000
                    ,0.621400000000000
                    ,0.625000000000000
                    ,0.628500000000000
                    ,0.631900000000000
                    ,0.635200000000000
                    ,0.638400000000000
                    ,0.641500000000000
                    ,0.644500000000000
                    ,0.647400000000000
                    ,0.650300000000000
                    ,0.653100000000000
                    ,0.655800000000000
                    ,0.658500000000000
                    ,0.661100000000000
                    ,0.663700000000000
                    ,0.666300000000000
                    ,0.668800000000000
                    ,0.671200000000000
                    ,0.673700000000000
                    ,0.676100000000000
                    ,0.678400000000000
                    ,0.680800000000000
                    ,0.683100000000000
                    ,0.685400000000000
                    ,0.687700000000000
                    ,0.689900000000000
                    ,0.692100000000000
                    ,0.694300000000000
                    ,0.696500000000000
                    ,0.698600000000000
                    ,0.700700000000000
                    ,0.702800000000000
                    ,0.704900000000000
                    ,0.706900000000000
                    ,0.708900000000000
                    ,0.710900000000000
                    ,0.712900000000000
                    ,0.714800000000000
                    ,0.716800000000000
                    ,0.718600000000000
                    ,0.720500000000000
                    ,0.722300000000000
                    ,0.724100000000000
                    ,0.725900000000000
                    ,0.727500000000000
                    ,0.729200000000000
                    ,0.730800000000000
                    ,0.732400000000000
                    ,0.733900000000000
                    ,0.735400000000000
                    ,0.736800000000000
                    ,0.738100000000000
                    ,0.739400000000000
                    ,0.740600000000000
                    ,0.741700000000000
                    ,0.742800000000000
                    ,0.743800000000000
                    ,0.744600000000000
                    ,0.745400000000000
                    ,0.746100000000000
                    ,0.746700000000000
                    ,0.747300000000000
                    ,0.747700000000000
                    ,0.748200000000000
                    ,0.748500000000000
                    ,0.748700000000000
                    ,0.748900000000000
                    ,0.749100000000000
                    ,0.749100000000000
                    ,0.749200000000000
                    ,0.749200000000000
                    ,0.749100000000000
                    ,0.749000000000000
                    ,0.748900000000000
                    ,0.748700000000000
                    ,0.748500000000000
                    ,0.748200000000000
                    ,0.747900000000000
                    ,0.747600000000000
                    ,0.747300000000000
                    ,0.746900000000000
                    ,0.746500000000000
                    ,0.746000000000000
                    ,0.745600000000000
                    ,0.745100000000000
                    ,0.744600000000000
                    ,0.744100000000000
                    ,0.743500000000000
                    ,0.743000000000000
                    ,0.742400000000000
                    ,0.741800000000000
                    ,0.741200000000000
                    ,0.740500000000000
                    ,0.739900000000000
                    ,0.739200000000000
                    ,0.738500000000000
                    ,0.737800000000000
                    ,0.737200000000000
                    ,0.736400000000000
                    ,0.735700000000000
                    ,0.735000000000000
                    ,0.734300000000000
                    ,0.733600000000000
                    ,0.732900000000000
                    ,0.732200000000000
                    ,0.731500000000000
                    ,0.730800000000000
                    ,0.730100000000000
                    ,0.729400000000000
                    ,0.728800000000000
                    ,0.728200000000000
                    ,0.727600000000000
                    ,0.727100000000000
                    ,0.726600000000000
                    ,0.726200000000000
                    ,0.725900000000000
                    ,0.725600000000000
                    ,0.725600000000000
                    ,0.725600000000000
                    ,0.725900000000000
                    ,0.726400000000000
                    ,0.727300000000000
                    ,0.728500000000000
                    ,0.730300000000000
                    ,0.732600000000000
                    ,0.735500000000000
                    ,0.739000000000000
                    ,0.743100000000000
                    ,0.747600000000000
                    ,0.752400000000000
                    ,0.757300000000000
                    ,0.762400000000000
                    ,0.767500000000000
                    ,0.772600000000000
                    ,0.777800000000000
                    ,0.782900000000000
                    ,0.788000000000000
                    ,0.793100000000000
                    ,0.798100000000000
                    ,0.803200000000000
                    ,0.808300000000000
                    ,0.813300000000000
                    ,0.818400000000000
                    ,0.823500000000000
                    ,0.828600000000000
                    ,0.833700000000000
                    ,0.838900000000000
                    ,0.844100000000000
                    ,0.849400000000000
                    ,0.854800000000000
                    ,0.860300000000000
                    ,0.865900000000000
                    ,0.871600000000000
                    ,0.877400000000000
                    ,0.883400000000000
                    ,0.889500000000000
                    ,0.895800000000000
                    ,0.902200000000000
                    ,0.908800000000000
                    ,0.915500000000000
                    ,0.922500000000000
                    ,0.929600000000000
                    ,0.936800000000000
                    ,0.944300000000000
                    ,0.951800000000000
                    ,0.959500000000000
                    ,0.967300000000000
                    ,0.975200000000000
                    ,0.983100000000000};

    std::vector<float> col_3 = {0.529200000000000
            ,0.541100000000000
            ,0.553000000000000
            ,0.565000000000000
            ,0.577100000000000
            ,0.589200000000000
            ,0.601300000000000
            ,0.613500000000000
            ,0.625800000000000
            ,0.638100000000000
            ,0.650500000000000
            ,0.662900000000000
            ,0.675300000000000
            ,0.687800000000000
            ,0.700300000000000
            ,0.712900000000000
            ,0.725500000000000
            ,0.738100000000000
            ,0.750700000000000
            ,0.763400000000000
            ,0.776200000000000
            ,0.789000000000000
            ,0.801700000000000
            ,0.814500000000000
            ,0.826900000000000
            ,0.838700000000000
            ,0.849500000000000
            ,0.858800000000000
            ,0.866400000000000
            ,0.872200000000000
            ,0.876500000000000
            ,0.879600000000000
            ,0.881500000000000
            ,0.882700000000000
            ,0.883300000000000
            ,0.883400000000000
            ,0.883100000000000
            ,0.882500000000000
            ,0.881600000000000
            ,0.880500000000000
            ,0.879300000000000
            ,0.877900000000000
            ,0.876300000000000
            ,0.874700000000000
            ,0.872900000000000
            ,0.871100000000000
            ,0.869200000000000
            ,0.867200000000000
            ,0.865200000000000
            ,0.863200000000000
            ,0.861100000000000
            ,0.858900000000000
            ,0.856800000000000
            ,0.854600000000000
            ,0.852500000000000
            ,0.850300000000000
            ,0.848100000000000
            ,0.846000000000000
            ,0.843900000000000
            ,0.841800000000000
            ,0.839800000000000
            ,0.837800000000000
            ,0.835900000000000
            ,0.834100000000000
            ,0.832400000000000
            ,0.830800000000000
            ,0.829300000000000
            ,0.828000000000000
            ,0.827000000000000
            ,0.826100000000000
            ,0.825300000000000
            ,0.824700000000000
            ,0.824300000000000
            ,0.823900000000000
            ,0.823700000000000
            ,0.823400000000000
            ,0.823100000000000
            ,0.822800000000000
            ,0.822300000000000
            ,0.821700000000000
            ,0.820900000000000
            ,0.819800000000000
            ,0.818600000000000
            ,0.817100000000000
            ,0.815400000000000
            ,0.813500000000000
            ,0.811400000000000
            ,0.809100000000000
            ,0.806600000000000
            ,0.803900000000000
            ,0.801000000000000
            ,0.798000000000000
            ,0.794800000000000
            ,0.791600000000000
            ,0.788100000000000
            ,0.784600000000000
            ,0.781000000000000
            ,0.777300000000000
            ,0.773500000000000
            ,0.769600000000000
            ,0.765600000000000
            ,0.761500000000000
            ,0.757400000000000
            ,0.753200000000000
            ,0.749000000000000
            ,0.744600000000000
            ,0.740200000000000
            ,0.735800000000000
            ,0.731300000000000
            ,0.726700000000000
            ,0.722100000000000
            ,0.717300000000000
            ,0.712600000000000
            ,0.707800000000000
            ,0.702900000000000
            ,0.697900000000000
            ,0.692900000000000
            ,0.687800000000000
            ,0.682700000000000
            ,0.677500000000000
            ,0.672300000000000
            ,0.666900000000000
            ,0.661600000000000
            ,0.656100000000000
            ,0.650700000000000
            ,0.645100000000000
            ,0.639500000000000
            ,0.633800000000000
            ,0.628100000000000
            ,0.622300000000000
            ,0.616500000000000
            ,0.610700000000000
            ,0.604800000000000
            ,0.598800000000000
            ,0.592900000000000
            ,0.586900000000000
            ,0.580900000000000
            ,0.574900000000000
            ,0.568900000000000
            ,0.563000000000000
            ,0.557000000000000
            ,0.551200000000000
            ,0.545300000000000
            ,0.539600000000000
            ,0.533900000000000
            ,0.528300000000000
            ,0.522900000000000
            ,0.517500000000000
            ,0.512300000000000
            ,0.507200000000000
            ,0.502100000000000
            ,0.497200000000000
            ,0.492400000000000
            ,0.487700000000000
            ,0.483100000000000
            ,0.478600000000000
            ,0.474100000000000
            ,0.469800000000000
            ,0.465500000000000
            ,0.461300000000000
            ,0.457100000000000
            ,0.453100000000000
            ,0.449000000000000
            ,0.445100000000000
            ,0.441200000000000
            ,0.437400000000000
            ,0.433500000000000
            ,0.429800000000000
            ,0.426100000000000
            ,0.422400000000000
            ,0.418800000000000
            ,0.415200000000000
            ,0.411600000000000
            ,0.408100000000000
            ,0.404600000000000
            ,0.401100000000000
            ,0.397600000000000
            ,0.394200000000000
            ,0.390800000000000
            ,0.387400000000000
            ,0.384000000000000
            ,0.380600000000000
            ,0.377300000000000
            ,0.373900000000000
            ,0.370600000000000
            ,0.367300000000000
            ,0.363900000000000
            ,0.360600000000000
            ,0.357300000000000
            ,0.353900000000000
            ,0.350600000000000
            ,0.347200000000000
            ,0.343800000000000
            ,0.340400000000000
            ,0.337000000000000
            ,0.333600000000000
            ,0.330000000000000
            ,0.326500000000000
            ,0.322900000000000
            ,0.319300000000000
            ,0.315600000000000
            ,0.311700000000000
            ,0.307800000000000
            ,0.303800000000000
            ,0.299600000000000
            ,0.295300000000000
            ,0.290700000000000
            ,0.285900000000000
            ,0.280800000000000
            ,0.275400000000000
            ,0.269600000000000
            ,0.263400000000000
            ,0.257000000000000
            ,0.250400000000000
            ,0.243700000000000
            ,0.237300000000000
            ,0.231000000000000
            ,0.225100000000000
            ,0.219500000000000
            ,0.214100000000000
            ,0.209000000000000
            ,0.204200000000000
            ,0.199500000000000
            ,0.194900000000000
            ,0.190500000000000
            ,0.186300000000000
            ,0.182100000000000
            ,0.178000000000000
            ,0.174000000000000
            ,0.170000000000000
            ,0.166100000000000
            ,0.162200000000000
            ,0.158300000000000
            ,0.154400000000000
            ,0.150500000000000
            ,0.146500000000000
            ,0.142500000000000
            ,0.138500000000000
            ,0.134300000000000
            ,0.130100000000000
            ,0.125800000000000
            ,0.121500000000000
            ,0.117100000000000
            ,0.112600000000000
            ,0.108200000000000
            ,0.103600000000000
            ,0.0990000000000000
            ,0.0944000000000000
            ,0.0897000000000000
            ,0.0850000000000000
            ,0.0802000000000000
            ,0.0753000000000000
            ,0.0703000000000000
            ,0.0651000000000000
            ,0.0597000000000000
            ,0.0538000000000000};


   float index = std::min((float)x,(float)max);
    index = std::max((float) index,(float)min);
    index = floor(255*(index - min)/max);

    if(invert){
        color[0] = 256 * (col_1[255-index]);
        color[1] = 256 * (col_2[255-index]);
        color[2] = 256 * (col_3[255-index]);
    } else {

        color[0] = 256 * col_1[index];
        color[1] = 256 * col_2[index];
        color[2] = 256 * col_3[index];
    }
    return;


}
struct ParticlesFull{

    std::vector<uint8_t> k_vec;

    std::vector<uint8_t> type_vec;

    std::vector<uint16_t> x_c;
    std::vector<uint16_t> y_c;
    std::vector<uint16_t> z_c;

    std::vector<uint16_t> Ip;

    unsigned int depth_max;
    unsigned int depth_min;

};

ParticlesFull get_full_parts_slice(PartCellStructure<float,uint64_t>& pc_struct,unsigned int z_slice){


    //containers for all the variables

    ParticlesFull parts;

    parts.depth_max = pc_struct.depth_max;
    parts.depth_min = pc_struct.depth_min;

    int num_cells = pc_struct.get_number_cells();
    int num_parts = pc_struct.get_number_parts();

    uint8_t k,type;
    uint16_t x_c;
    uint16_t y_c;
    uint16_t z_c;
    uint16_t Ip;


    //initialize
    uint64_t node_val_part;
    uint64_t y_coord;
    int x_;
    int z_;

    uint64_t j_;
    uint64_t status;
    uint64_t curr_key=0;
    uint64_t part_offset=0;

    uint64_t p;

    uint64_t counter = 0;


    for(uint64_t i = pc_struct.pc_data.depth_min;i <= pc_struct.pc_data.depth_max;i++){

        const unsigned int x_num_ = pc_struct.pc_data.x_num[i];
        const unsigned int z_num_ = pc_struct.pc_data.z_num[i];

        for(z_ = 0;z_ < z_num_;z_++){

            curr_key = 0;

            pc_struct.part_data.access_data.pc_key_set_depth(curr_key,i);
            pc_struct.part_data.access_data.pc_key_set_z(curr_key,z_);

            for(x_ = 0;x_ < x_num_;x_++){

                pc_struct.part_data.access_data.pc_key_set_x(curr_key,x_);
                const size_t offset_pc_data = x_num_*z_ + x_;

                const size_t j_num = pc_struct.pc_data.data[i][offset_pc_data].size();

                y_coord = 0;

                for(j_ = 0;j_ < j_num;j_++){


                    node_val_part = pc_struct.part_data.access_data.data[i][offset_pc_data][j_];

                    if (!(node_val_part&1)){
                        //get the index gap node
                        y_coord++;

                        pc_struct.part_data.access_data.pc_key_set_j(curr_key,j_);

                        //neigh_keys.resize(0);
                        status = pc_struct.part_data.access_node_get_status(node_val_part);
                        part_offset = pc_struct.part_data.access_node_get_part_offset(node_val_part);

                        pc_struct.part_data.access_data.pc_key_set_status(curr_key,status);

                        //loop over the particles
                        for(p = 0;p < pc_struct.part_data.get_num_parts(status);p++){
                            pc_struct.part_data.access_data.pc_key_set_index(curr_key,part_offset+p);
                            pc_struct.part_data.access_data.pc_key_set_partnum(curr_key,p);

                            uint64_t x,z,y,depth,status;

                            pc_struct.part_data.access_data.get_coordinates_part(y_coord,curr_key,x,z,y,depth,status);

                            int k_factor = pow(2,pc_struct.depth_max + 1 - depth);

                            if(z == z_slice/k_factor){

                                //set the cooridnates info
                                pc_struct.part_data.access_data.get_coordinates_part_full(y_coord,curr_key,x_c,z_c,y_c,k,type);

                                //get the intensity
                                parts.Ip.push_back(pc_struct.part_data.get_part(curr_key));
                                parts.k_vec.push_back(k);
                                parts.type_vec.push_back(type);
                                parts.x_c.push_back(x_c);
                                parts.y_c.push_back(y_c);
                                parts.z_c.push_back(z_c);

                            }

                        }

                    } else {

                        y_coord += ((node_val_part & COORD_DIFF_MASK_PARTICLE) >> COORD_DIFF_SHIFT_PARTICLE);
                        y_coord--;
                    }

                }

            }

        }
    }

    return parts;

}




void create_part_eps(ParticlesFull& parts_slice,std::string save_loc,std::string name,std::vector<unsigned int> crange){
    // creates an eps with the part locations adjusted for size

    int num_parts = parts_slice.x_c.size();


    Board board;
    board.setLineWidth(0.25);

    Group g;
    //g << Rectangle( -20, 10, 20, 10, Color::Green, Color::White,,0.1 );

    //g << Rectangle( 0, 5, 10, 10, Color::Green, Color::Blue,,0.1 );

    double col[3];

    for(int i = 0;i < num_parts; i++){

        ParulaColorMix(col,parts_slice.Ip[i],crange[0],crange[1]);

        double size = 2*parts_slice.depth_max*parts_slice.depth_min/((float)pow(1.5,parts_slice.k_vec[i]));

        g << Circle( parts_slice.y_c[i], -parts_slice.x_c[i],size , Color::Null, Color(col[0],col[1],col[2]),0.1 );

    }

    board << g;

    std::string file_name;

    file_name =save_loc + name + "_parts.eps";
    board.saveEPS( file_name.c_str(), Board::A4 );
    //file_name =save_loc + name + ".fig";
    //board.saveFIG( file_name.c_str(), Board::A4 );

    //board.scaleToWidth(25,Board::UseLineWidth);
    //file_name =save_loc + name + ".svg";
    //board.saveSVG( file_name.c_str(), Board::BoundingBox,0.0, Board::UCentimeter );

    std::cout << " done parts to eps" << std::endl;

}

void create_part_eps_type(ParticlesFull& parts_slice,std::string save_loc,std::string name){
    // creates an eps with the part locations adjusted for size

    int num_parts = parts_slice.x_c.size();


    std::vector<float> crange = {0,4};

    Board board;
    board.setLineWidth(0.25);

    Group g;
    //g << Rectangle( -20, 10, 20, 10, Color::Green, Color::White,,0.1 );

    //g << Rectangle( 0, 5, 10, 10, Color::Green, Color::Blue,,0.1 );

    double col[3];

    for(int i = 0;i < num_parts; i++){

        ParulaColorMix(col,parts_slice.type_vec[i],crange[0],crange[1]);

        double size = 2*parts_slice.depth_max*parts_slice.depth_min/((float)pow(1.5,parts_slice.k_vec[i]));

        g << Circle( parts_slice.y_c[i], -parts_slice.x_c[i],size , Color::Null, Color(col[0],col[1],col[2]),0.1 );

    }

    board << g;

    std::string file_name;

    file_name =save_loc + name + "_parts_type.eps";
    board.saveEPS( file_name.c_str(), Board::A4 );
    //file_name =save_loc + name + ".fig";
    //board.saveFIG( file_name.c_str(), Board::A4 );

    //board.scaleToWidth(25,Board::UseLineWidth);
    //file_name =save_loc + name + ".svg";
    //board.saveSVG( file_name.c_str(), Board::BoundingBox,0.0, Board::UCentimeter );

    std::cout << " done type to eps" << std::endl;

}
void create_part_eps_depth(ParticlesFull& parts_slice,std::string save_loc,std::string name){
    // creates an eps with the part locations adjusted for size

    int num_parts = parts_slice.x_c.size();


    std::vector<float> crange = {(float)0,(float)parts_slice.depth_max+1};

    Board board;
    board.setLineWidth(0.25);

    Group g;
    //g << Rectangle( -20, 10, 20, 10, Color::Green, Color::White,,0.1 );

    //g << Rectangle( 0, 5, 10, 10, Color::Green, Color::Blue,,0.1 );

    double col[3];

    for(int i = 0;i < num_parts; i++){

        ParulaColorMix(col,(double) parts_slice.k_vec[i],crange[0],crange[1],true);

        double size = 2*parts_slice.depth_max*parts_slice.depth_min/((float)pow(1.5,parts_slice.k_vec[i]));

        g << Circle( parts_slice.y_c[i], -parts_slice.x_c[i],size , Color::Null, Color(col[0],col[1],col[2]),0.1 );

    }

    board << g;

    std::string file_name;

    file_name =save_loc + name + "_parts_depth.eps";
    board.saveEPS( file_name.c_str(), Board::A4 );
    //file_name =save_loc + name + ".fig";
    //board.saveFIG( file_name.c_str(), Board::A4 );

    //board.scaleToWidth(25,Board::UseLineWidth);
    //file_name =save_loc + name + ".svg";
    //board.saveSVG( file_name.c_str(), Board::BoundingBox,0.0, Board::UCentimeter );

    std::cout << " done depth to eps" << std::endl;

}

















#endif //PARTPLAY_GET_PART_EPS_HPP
