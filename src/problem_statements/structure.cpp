//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─structure.cpp

#if PROBLEM_STATEMENT == TRUSS
#include "../../include/problem_statements/structure.hpp"

// Graph grammar characteristics
#if RULE_SET == SHEA_FRAME
    const  unsigned long  Solution::number_of_move_ops   = 6;
#elif RULE_SET == SHEA_TRUSS
    const  unsigned long  Solution::number_of_move_ops   = 7;
#elif RULE_SET == MCCOMB
    const  unsigned long  Solution::number_of_move_ops   = 7;
#endif

const  unsigned long  Solution::number_of_objectives = 2;
//const  std::vector<long double>    Solution::goal    = {175.0, -1.25};

// Material constants
const  long double    Solution::E               = 209*std::pow(10,9); // Pa
const  long double    Solution::Fy              = 344*std::pow(10,6); // Pa
const  long double    Solution::density             = 7870; // kg/m3

// Member radius and wall thickness
const std::vector< long double > Solution::member_radius  = {0.005, 0.010, 0.015, 0.020, 0.025,
                                                             0.030, 0.035, 0.040, 0.045, 0.050};
const std::vector< long double > Solution::wall_thickness = {0.005/7.5, 0.010/7.5, 0.015/7.5, 0.020/7.5, 0.025/7.5,
                                                             0.030/7.5, 0.035/7.5, 0.040/7.5, 0.045/7.5, 0.050/7.5};

// Problem definition
#if PROBLEM_NUMBER == 0
    const  std::vector<long double>    Solution::goal    = {200.0, -1.00};

    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
        {{"x", -5.00}, {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", -2.00}, {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", -200000.00}, {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", 1.00},  {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", 3.00},  {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", -200000.00}, {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", 5.00},  {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},

        {{"x", -3.50}, {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", -0.50}, {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 2.00},  {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 4.00},  {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

        {{"x", 1.00},  {"y", 4.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

        {{"x", -2.00}, {"y", 4.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 3.00},  {"y", 4.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

        {{"x", -5.00}, {"y", 3.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 5.00},  {"y", 3.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

    };

    // Problem definition
    std::vector< std::map<std::string, long double> > Solution::seed_edge_parameters = {
        {{"initial",  0}, {"terminal", 1}, {"radius", 4}},
        {{"initial",  1}, {"terminal", 2}, {"radius", 4}},
        {{"initial",  2}, {"terminal", 3}, {"radius", 4}},
        {{"initial",  3}, {"terminal", 4}, {"radius", 4}},

        {{"initial",  5}, {"terminal", 6}, {"radius", 4}},
        {{"initial",  6}, {"terminal", 7}, {"radius", 4}},
        {{"initial",  7}, {"terminal", 8}, {"radius", 4}},

        {{"initial",  0}, {"terminal", 5}, {"radius", 4}},
        {{"initial",  5}, {"terminal", 1}, {"radius", 4}},
        {{"initial",  1}, {"terminal", 6}, {"radius", 4}},
        {{"initial",  6}, {"terminal", 2}, {"radius", 4}},
        {{"initial",  2}, {"terminal", 7}, {"radius", 4}},
        {{"initial",  7}, {"terminal", 3}, {"radius", 4}},
        {{"initial",  3}, {"terminal", 8}, {"radius", 4}},
        {{"initial",  8}, {"terminal", 4}, {"radius", 4}},

        {{"initial",  6}, {"terminal", 9}, {"radius", 4}},
        {{"initial",  7}, {"terminal", 9}, {"radius", 4}},

        {{"initial",  5}, {"terminal", 10}, {"radius", 4}},
        {{"initial",  6}, {"terminal", 10}, {"radius", 4}},
        {{"initial",  9}, {"terminal", 10}, {"radius", 4}},

        {{"initial",  7}, {"terminal", 11}, {"radius", 4}},
        {{"initial",  8}, {"terminal", 11}, {"radius", 4}},
        {{"initial",  9}, {"terminal", 11}, {"radius", 4}},

        {{"initial",  0}, {"terminal", 12}, {"radius", 4}},
        {{"initial",  5}, {"terminal", 12}, {"radius", 4}},
        {{"initial",  10}, {"terminal", 12}, {"radius", 4}},

        {{"initial",  4}, {"terminal", 13}, {"radius", 4}},
        {{"initial",  8}, {"terminal", 13}, {"radius", 4}},
        {{"initial",  11}, {"terminal", 13}, {"radius", 4}},
    };

#elif PROBLEM_NUMBER == 1
    const  std::vector<long double>    Solution::goal    = {350.0, -1.00};


    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
            {{"x", 0.00}, {"y", 0.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
            {{"x", 5.00}, {"y", 0.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
            {{"x", 2.50}, {"y", 15.00}, {"z", 0.00}, {"Fx", 20000.00}, {"Fy", -100000.00}, {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},

            {{"x", 0.00}, {"y", 5.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2.50}, {"y", 5.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

            {{"x", 0.00}, {"y", 10.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2.50}, {"y", 10.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

            {{"x", 5.00}, {"y", 5.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 5.00}, {"y", 10.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

            {{"x", 2.50}, {"y", 1.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

            {{"x", 0.83}, {"y", 3.33},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 3.33}, {"y", 6.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 4.17}, {"y", 3.33},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 1.67}, {"y", 6.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

            {{"x", 0.83}, {"y", 8.33},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 3.33}, {"y", 11.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 4.17}, {"y", 8.33},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 1.67}, {"y", 11.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}}
    };

    std::vector< std::map<std::string, long double> > Solution::seed_edge_parameters = {
            {{"initial", 0},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 0},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 3},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 1},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 3},  {"terminal", 5},  {"radius", 4}},
            {{"initial", 2},  {"terminal", 5},  {"radius", 4}},

            {{"initial", 6},  {"terminal", 5},  {"radius", 4}},
            {{"initial", 6},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 6},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 6},  {"terminal", 2},  {"radius", 4}},

            {{"initial", 7},  {"terminal", 1},  {"radius", 4}},
            {{"initial", 7},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 7},  {"terminal", 6},  {"radius", 4}},

            {{"initial", 8},  {"terminal", 2},  {"radius", 4}},
            {{"initial", 8},  {"terminal", 6},  {"radius", 4}},
            {{"initial", 8},  {"terminal", 7},  {"radius", 4}},

            {{"initial", 9},  {"terminal", 0},  {"radius", 4}},
            {{"initial", 9},  {"terminal", 1},  {"radius", 4}},
            {{"initial", 9},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 10},  {"terminal", 0},  {"radius", 4}},
            {{"initial", 10},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 10},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 11},  {"terminal", 6},  {"radius", 4}},
            {{"initial", 11},  {"terminal", 7},  {"radius", 4}},
            {{"initial", 11},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 12},  {"terminal", 1},  {"radius", 4}},
            {{"initial", 12},  {"terminal", 7},  {"radius", 4}},
            {{"initial", 12},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 13},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 13},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 13},  {"terminal", 6},  {"radius", 4}},

            {{"initial", 14},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 14},  {"terminal", 5},  {"radius", 4}},
            {{"initial", 14},  {"terminal", 6},  {"radius", 4}},

            {{"initial", 15},  {"terminal", 8},  {"radius", 4}},
            {{"initial", 15},  {"terminal", 2},  {"radius", 4}},
            {{"initial", 15},  {"terminal", 6},  {"radius", 4}},

            {{"initial", 16},  {"terminal", 6},  {"radius", 4}},
            {{"initial", 16},  {"terminal", 7},  {"radius", 4}},
            {{"initial", 16},  {"terminal", 8},  {"radius", 4}},

            {{"initial", 17},  {"terminal", 2},  {"radius", 4}},
            {{"initial", 17},  {"terminal", 5},  {"radius", 4}},
            {{"initial", 17},  {"terminal", 6},  {"radius", 4}},
    };

#elif PROBLEM_NUMBER == 2
const  std::vector<long double>    Solution::goal    = {350.0, -1.00};


    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
            {{"x", 0.00}, {"y", 0.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
            {{"x", 2*5.00}, {"y", 0.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
            {{"x", 2*2.50}, {"y", 10.00}, {"z", 0.00}, {"Fx", 100000.00}, {"Fy", -100000.00}, {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},

            {{"x", 0.00}, {"y", 5.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2*2.50}, {"y", 5.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2*5.00}, {"y", 5.00},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

            {{"x", 2*2.50}, {"y", 1.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2*0.83}, {"y", 3.33},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2*3.33}, {"y", 6.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2*4.17}, {"y", 3.33},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
            {{"x", 2*1.67}, {"y", 6.67},  {"z", 0.00}, {"Fx", 0.00},     {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}}
    };

    std::vector< std::map<std::string, long double> > Solution::seed_edge_parameters = {
            {{"initial", 0},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 0},  {"terminal", 7},  {"radius", 4}},
            {{"initial", 0},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 0},  {"terminal", 6},  {"radius", 4}},

            {{"initial", 4},  {"terminal", 6},  {"radius", 4}},

            {{"initial", 1},  {"terminal", 6},  {"radius", 4}},
            {{"initial", 1},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 1},  {"terminal", 9},  {"radius", 4}},
            {{"initial", 1},  {"terminal", 5},  {"radius", 4}},

            {{"initial", 7},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 7},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 3},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 4},  {"terminal", 5},  {"radius", 4}},
            {{"initial", 5},  {"terminal", 9},  {"radius", 4}},
            {{"initial", 9},  {"terminal", 4},  {"radius", 4}},

            {{"initial", 2},  {"terminal", 3},  {"radius", 4}},
            {{"initial", 2},  {"terminal", 10}, {"radius", 4}},
            {{"initial", 2},  {"terminal", 4},  {"radius", 4}},
            {{"initial", 2},  {"terminal", 8},  {"radius", 4}},
            {{"initial", 2},  {"terminal", 5},  {"radius", 4}},

            {{"initial", 3},  {"terminal", 10}, {"radius", 4}},
            {{"initial", 10}, {"terminal", 4},  {"radius", 4}},

            {{"initial", 4},  {"terminal", 8},  {"radius", 4}},
            {{"initial", 8},  {"terminal", 5},  {"radius", 4}}
    };

#elif PROBLEM_NUMBER == 3

    const  std::vector<long double>    Solution::goal    = {250.0, -1.00};

    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
        {{"x", -5.00}, {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", -2.00}, {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", -200000.00}, {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", 1.00},  {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", 3.00},  {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", -200000.00}, {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},
        {{"x", 5.00},  {"y", 0.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 1}, {"ry", 1}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", false}},

        {{"x", -3.50}, {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", -0.50}, {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 2.00},  {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 4.00},  {"y", 2.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

        {{"x", 1.00},  {"y", 4.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

        {{"x", -2.00}, {"y", 4.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 3.00},  {"y", 4.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

        {{"x", -5.00}, {"y", 3.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},
        {{"x", 5.00},  {"y", 3.00}, {"z", 0.00}, {"Fx", 0.00}, {"Fy", 0.00},       {"Fz", 0.00}, {"Mz", 0.00}, {"rx", 0}, {"ry", 0}, {"rz", 1}, {"mx", 0}, {"my", 0}, {"mz", 0}, {"editable", true}},

    };

    // Problem definition
    std::vector< std::map<std::string, long double> > Solution::seed_edge_parameters = {
        {{"initial",  0}, {"terminal", 1}, {"radius", 4}},
        {{"initial",  1}, {"terminal", 2}, {"radius", 4}},
        {{"initial",  2}, {"terminal", 3}, {"radius", 4}},
        {{"initial",  3}, {"terminal", 4}, {"radius", 4}},

        {{"initial",  5}, {"terminal", 6}, {"radius", 4}},
        {{"initial",  6}, {"terminal", 7}, {"radius", 4}},
        {{"initial",  7}, {"terminal", 8}, {"radius", 4}},

        {{"initial",  0}, {"terminal", 5}, {"radius", 4}},
        {{"initial",  5}, {"terminal", 1}, {"radius", 4}},
        {{"initial",  1}, {"terminal", 6}, {"radius", 4}},
        {{"initial",  6}, {"terminal", 2}, {"radius", 4}},
        {{"initial",  2}, {"terminal", 7}, {"radius", 4}},
        {{"initial",  7}, {"terminal", 3}, {"radius", 4}},
        {{"initial",  3}, {"terminal", 8}, {"radius", 4}},
        {{"initial",  8}, {"terminal", 4}, {"radius", 4}},

        {{"initial",  6}, {"terminal", 9}, {"radius", 4}},
        {{"initial",  7}, {"terminal", 9}, {"radius", 4}},

        {{"initial",  5}, {"terminal", 10}, {"radius", 4}},
        {{"initial",  6}, {"terminal", 10}, {"radius", 4}},
        {{"initial",  9}, {"terminal", 10}, {"radius", 4}},

        {{"initial",  7}, {"terminal", 11}, {"radius", 4}},
        {{"initial",  8}, {"terminal", 11}, {"radius", 4}},
        {{"initial",  9}, {"terminal", 11}, {"radius", 4}},

        {{"initial",  0}, {"terminal", 12}, {"radius", 4}},
        {{"initial",  5}, {"terminal", 12}, {"radius", 4}},
        {{"initial",  10}, {"terminal", 12}, {"radius", 4}},

        {{"initial",  4}, {"terminal", 13}, {"radius", 4}},
        {{"initial",  8}, {"terminal", 13}, {"radius", 4}},
        {{"initial",  11}, {"terminal", 13}, {"radius", 4}},
    };

#endif

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;


// Null constructor
Solution::Solution(void) {}


// A real constructor
Solution::Solution(bool) {
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create seed graph
    create_seed_graph();

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}

void Solution::create_seed_graph(void){
    // Draw a uniform int to decide how many joints to add
    #if PROBLEM_NUMBER == 0
        int joints_to_add = uniform_int(14, 8);
    #elif PROBLEM_NUMBER == 1
        int joints_to_add = uniform_int(18, 7);
    #elif PROBLEM_NUMBER == 2
        int joints_to_add = uniform_int(11, 5);
    #elif PROBLEM_NUMBER == 3
        int joints_to_add = uniform_int(14, 8);
    #endif

    // Add all joints
    for(int i=0; i < joints_to_add; i++) {
        // Add the node
        add_node();

        // Add the values
        nodes[node_id_counter].parameters["x"] = seed_node_parameters[i]["x"] + uniform(0.25, -0.25)*seed_node_parameters[i]["editable"];
        nodes[node_id_counter].parameters["y"] = seed_node_parameters[i]["y"] + uniform(0.25, -0.25)*seed_node_parameters[i]["editable"];
        nodes[node_id_counter].parameters["z"] = seed_node_parameters[i]["z"];
        nodes[node_id_counter].parameters["rx"] = seed_node_parameters[i]["rx"];
        nodes[node_id_counter].parameters["ry"] = seed_node_parameters[i]["ry"];
        nodes[node_id_counter].parameters["rz"] = seed_node_parameters[i]["rz"];
        nodes[node_id_counter].parameters["Fx"] = seed_node_parameters[i]["Fx"];
        nodes[node_id_counter].parameters["Fy"] = seed_node_parameters[i]["Fy"];
        nodes[node_id_counter].parameters["Fz"] = seed_node_parameters[i]["Fz"];
        nodes[node_id_counter].parameters["editable"] = seed_node_parameters[i]["editable"];
    }

    // Connect these joints
    for(int i=0; i < seed_edge_parameters.size(); i++) {
        if(node_exists(static_cast<int> (seed_edge_parameters[i]["initial"])) && node_exists(static_cast<int> (seed_edge_parameters[i]["terminal"]))){
            add_member(static_cast<int>(seed_edge_parameters[i]["initial"]),
                       static_cast<int>(seed_edge_parameters[i]["terminal"]),
                       static_cast<int>(seed_edge_parameters[i]["radius"]),
                       true);
        }
    }
}

void Solution::compute_quality(void) {
    // Define some things
    long double FOS_penalty;
    mass = 0;
    FOS = LDBL_MAX;


    // Compute the force-based solution for the truss
    compute_truss_forces();

    if (is_valid()) {

        // Compute the mass
        for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); ++it1) {
            mass += edges[it1->first].parameters["m"];
            if (edges[it1->first].parameters["FOS_lim"] < FOS) {
                FOS = edges[it1->first].parameters["FOS_lim"];
            }
        }

        // Compute FOS penalty
        if(FOS == LDBL_MAX) {
            mass = 100*goal[0];
            FOS = 0.01;
        }
    } else {
        mass = 100*goal[0];
        FOS = 0.01;
    }

    // Adjust with respect to goals
    long double quality_mass = mass;
//    if(mass > goal[0]) {
//        quality_mass += std::pow((mass - goal[0]), 2);
//    }
    quality_mass /= goal[0];

    long double quality_fos = -FOS/goal[1];
    if(FOS < -goal[1]) {
        quality_fos = -10*std::log(-FOS/goal[1]) + 1;
    } else {
        quality_fos = 2 - quality_fos;
    }

    quality = {quality_mass, quality_fos};
}


// This function computes forces and factors of safety trusses
void Solution::compute_truss_forces(void) {
    // Initialize things
    std::vector<std::vector<long double> > K(static_cast<unsigned long>(3 * number_of_nodes),
                                             std::vector<long double>(static_cast<unsigned long>(3 * number_of_nodes),
                                                                      0.0));

    // Get the vector that will relate entries in the node map to entries in the global stiffness matrix
    std::map<int, int> node_id_map;
    int counter = 0;
    for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        node_id_map[it->first] = counter;
        counter++;
    }

    // Define a matrix that will later to be used to hold deflections and other things
    std::vector<std::vector<long double> > deflections(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));
    std::vector<std::vector<long double> > loads(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));

    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        int idx = node_id_map[it1->first];
        deflections[0][idx] = 1 - nodes[it1->first].parameters["rx"];
        deflections[1][idx] = 1 - nodes[it1->first].parameters["ry"];
        deflections[2][idx] = 1 - nodes[it1->first].parameters["rz"];
        loads[0][idx] = nodes[it1->first].parameters["Fx"];
        loads[1][idx] = nodes[it1->first].parameters["Fy"];
        loads[2][idx] = nodes[it1->first].parameters["Fz"];
    }

    // Find out which joints can deflect
    std::vector<long double> ff;
    std::vector<long double> loads_ff;
    counter = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            if (deflections[j][i] == 1) {
                ff.push_back(counter);
                loads_ff.push_back(loads[j][i]);
            }
            counter++;
        }
    }

    // Build the global stiffess matrix
    int idx1, idx2, key1, key2;
    long double ux, uy, uz;
    std::vector<int> ee(6, 0);
    std::vector<long double> uu(6, 0.0);
    for (std::map<int, Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        int k = (it->first);
        key1 = edges[k].initial_node;
        key2 = edges[k].terminal_node;
        idx1 = node_id_map[key1];
        idx2 = node_id_map[key2];
        ux = (nodes[key1].parameters["x"] - nodes[key2].parameters["x"]) / edges[k].parameters["L"];
        uy = (nodes[key1].parameters["y"] - nodes[key2].parameters["y"]) / edges[k].parameters["L"];
        uz = (nodes[key1].parameters["z"] - nodes[key2].parameters["z"]) / edges[k].parameters["L"];
        long double EAL = E * edges[k].parameters["A"] / edges[k].parameters["L"];
        edges[k].parameters["kx"] = EAL*ux;
        edges[k].parameters["ky"] = EAL*uy;
        edges[k].parameters["kz"] = EAL*uz;
        uu = {ux, uy, uz, -ux, -uy, -uz};
        ee = {3 * idx1, 3 * idx1 + 1, 3 * idx1 + 2, 3 * idx2, 3 * idx2 + 1, 3 * idx2 + 2};
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                K[ee[i]][ee[j]] += EAL * uu[i] * uu[j];
            }
        }
    }

    // Solve for displacements
    int ffs = static_cast<int>(ff.size());
    std::vector<std::vector<long double> > Kff(ff.size(), std::vector<long double>(ff.size() + 1, 0.0));
    for (int i = 0; i < ffs; i++) {
        for (int j = 0; j < ffs; j++) {
            Kff[i][j] = K[ff[i]][ff[j]];
        }
        Kff[i][ffs] = loads_ff[i];
    }

    std::vector<long double> deflections_compact = gauss(Kff);

    // Compute the condition number
    for(int i=0; i<ffs; i++){
        Kff[i][ffs] = deflections_compact[i];
    }
    std::vector<long double> backed_out_loads = matrix_vector_mult(Kff);
    cond = 0;
    for(int i=0; i<ffs; i++){
        cond += std::abs(loads_ff[i] - backed_out_loads[i]);
    }


    // Fit the compacted deflection matrix back into the original
    counter = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            if (deflections[j][i] == 1) {
                deflections[j][i] = deflections_compact[counter];
                counter++;
            }
        }
    }

    // From displacements, solve for forces
    for (std::map<int, Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        // Define a few things
        int k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];

        // Define the force
        edges[k].parameters["F"] =   edges[k].parameters["kx"] * (deflections[0][idx1] - deflections[0][idx2])
                                   + edges[k].parameters["ky"] * (deflections[1][idx1] - deflections[1][idx2])
                                   + edges[k].parameters["kz"] * (deflections[2][idx1] - deflections[2][idx2]);

        // Calculate factor of safety against yielding
        edges[k].parameters["FOS_y"] = std::abs((Fy*edges[k].parameters["A"])/edges[k].parameters["F"]);

        // Calculate factor of safety against buckling
        if (edges[k].parameters["F"] < 0) {
            edges[k].parameters["FOS_b"] = -(std::pow(M_PI, 2) * E * edges[k].parameters["I"]/std::pow(edges[k].parameters["L"], 2))/edges[k].parameters["F"];
        } else {
            edges[k].parameters["FOS_b"] = 1000;
        }

        // Save the limiting factor of safety
        if(edges[k].parameters["FOS_b"] < edges[k].parameters["FOS_y"]){
            edges[k].parameters["FOS_lim"] = edges[k].parameters["FOS_b"];
        } else {
            edges[k].parameters["FOS_lim"] = edges[k].parameters["FOS_y"];
        }
    }
}


// This function computes forces and factors of safety for frames
void Solution::compute_frame_forces(void){
    // Initialize things
    std::vector<std::vector<long double> > K_global(static_cast<unsigned long>(3 * number_of_nodes),
                                             std::vector<long double>(static_cast<unsigned long>(3 * number_of_nodes),
                                                                      0.0));
    std::vector<std::vector<long double> > deflections(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));
    std::vector<std::vector<long double> > loads(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));
    std::vector<std::vector<long double> > K(6, std::vector<long double>(6, 0.0));
    std::vector<int> ee(6, 0);
    std::vector<long double> ff;
    std::vector<long double> loads_ff;
    std::map<int, int> node_id_map;
    long double lx, ly, theta, A, I, L, EAL, twEIL3, EIL2, EIL1, lx2, ly2, lxy;
    int idx, idx1, idx2, k, n1, n2, counter=0;

    // Get the vector that will relate entries in the node map to entries in the global stiffness matrix
    for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        node_id_map[it->first] = counter;
        counter++;
    }

    // Define a matrix that will later to be used to hold deflections and other things
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        idx = node_id_map[it1->first];
        deflections[0][idx] = 1 - nodes[it1->first].parameters["rx"];
        deflections[1][idx] = 1 - nodes[it1->first].parameters["ry"];
        deflections[2][idx] = 1 - nodes[it1->first].parameters["mz"];
        loads[0][idx] = nodes[it1->first].parameters["Fx"];
        loads[1][idx] = nodes[it1->first].parameters["Fy"];
        loads[2][idx] = nodes[it1->first].parameters["Mz"];
    }

    // Find out which joints can deflect
    counter = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            if (deflections[j][i] == 1) {
                ff.push_back(counter);
                loads_ff.push_back(loads[j][i]);
            }
            counter++;
        }
    }


    // Define the global stiffness matrix
    for (std::map<int, Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        // Define things for the member
        k = (it->first);
        A = edges[k].parameters["A"];
        I = edges[k].parameters["I"];
        L = edges[k].parameters["L"];
        n1 = edges[k].initial_node;
        n2 = edges[k].terminal_node;
        EAL = E*A/L;                        edges[k].parameters["EAL"] = EAL;
        twEIL3 = 12*E*I/std::pow(L, 3);     edges[k].parameters["twEIL3"] = twEIL3;
        EIL2 = E*I/std::pow(L, 2);          edges[k].parameters["EIL2"] = EIL2;
        EIL1 = E*I/L;                       edges[k].parameters["EIL1"] = EIL1;

        // Figure out the angle of the member in the x-y plane
        theta = std::atan2(nodes[n1].parameters["y"] - nodes[n2].parameters["y"], nodes[n1].parameters["x"] - nodes[n2].parameters["x"]);
        lx = std::cos(theta);               edges[k].parameters["lx"] = lx;
        lx2 = std::pow(lx, 2);
        ly = std::sin(theta);               edges[k].parameters["ly"] = ly;
        ly2 = std::pow(ly, 2);
        lxy = lx*ly;

        // For each member, define a 6x6 stiffness matrix
        // First row
        K[0][0] = EAL*lx2 + twEIL3*ly2;          // Symmetric condition
        K[0][1] = (EAL - twEIL3)*lxy;               K[1][0] = K[0][1];
        K[0][2] = -6*EIL2*ly;                       K[2][0] = K[0][2];
        K[0][3] = -K[0][1];                         K[3][0] = K[0][3];
        K[0][4] = -K[0][1];                         K[4][0] = K[0][4];
        K[0][5] = K[0][2];                          K[5][0] = K[0][5];
        // Second row
        K[1][1] = EAL*ly2 + twEIL3*lx2;          // Symmetric condition
        K[1][2] = 6*EIL2*lx;                        K[2][1] = K[1][2];
        K[1][3] = K[0][4];                          K[3][1] = K[1][3];
        K[1][4] = -K[1][1];                         K[4][1] = K[1][4];
        K[1][5] = K[1][2];                          K[5][1] = K[1][5];
        // Third row
        K[2][2] = 4*EIL1;                        // Symmetric condition
        K[2][3] = -K[0][2];                         K[3][2] = K[2][3];
        K[2][4] = -K[2][1];                         K[4][2] = K[2][4];
        K[2][5] = 2*EIL1;                           K[5][2] = K[2][5];
        // Fourth row
        K[3][3] = K[0][0];                       // Symmetric condition
        K[3][4] = K[0][1];                          K[4][3] = K[3][4];
        K[3][5] = K[2][3];                          K[5][3] = K[3][5];
        // Fifth row
        K[4][4] = K[1][1];                       // Symmetric condition
        K[4][5] = -K[1][2];                         K[5][4] = K[4][5];
        // Sixth row
        K[5][5] = 4*EIL1;

        // Now, assemble the global matrix
        idx1 = node_id_map[n1];
        idx2 = node_id_map[n2];
        ee = {3 * idx1, 3 * idx1 + 1, 3 * idx1 + 2, 3 * idx2, 3 * idx2 + 1, 3 * idx2 + 2};
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                K_global[ee[i]][ee[j]] += K[i][j];
            }
        }
    }

    // Solve for displacements
    int ffs = static_cast<int>(ff.size());
    std::vector<std::vector<long double> > Kff(ff.size(), std::vector<long double>(ff.size() + 1, 0.0));
    for (int i = 0; i < ffs; i++) {
        for (int j = 0; j < ffs; j++) {
            Kff[i][j] = K_global[ff[i]][ff[j]];
        }
        Kff[i][ffs] = loads_ff[i];
    }

    std::vector<long double> deflections_compact = gauss(Kff);

    // Compute the condition number
    for(int i=0; i<ffs; i++){
        Kff[i][ffs] = deflections_compact[i];
    }
    std::vector<long double> backed_out_loads = matrix_vector_mult(Kff);
    cond = 0;
    for(int i=0; i<ffs; i++){
        cond += std::abs(loads_ff[i] - backed_out_loads[i]);
    }


    // Fit the compacted deflection matrix back into the original
    counter = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            if (deflections[j][i] == 1) {
                deflections[j][i] = deflections_compact[counter];
                counter++;
            }
        }
    }



    // From displacements, solve for forces
    // TODO: Finish this
    for (std::map<int, Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        // Define a few things
        k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];

        // Define the axial force
        edges[k].parameters["F"] = 0;

        // Define the maximum shear force
        edges[k].parameters["V"] = 0;

        // Define the maximum moment
        edges[k].parameters["M"] = 0;

        // Calculate factor of safety against normal yielding
        edges[k].parameters["FOS_y"] = std::abs((Fy*edges[k].parameters["A"])/edges[k].parameters["F"]);

        // Calculate the factor of safety against buckling
        edges[k].parameters["FOS_b"] = 0;

        // Calculate the factor of safety against bending
        edges[k].parameters["FOS_m"] = 0;

        // Calculate the factor of safety against shear failure
        edges[k].parameters["FOS_v"] = 0;

        // Save the limiting factor of safety
        edges[k].parameters["FOS_lim"] = vector_minimum({edges[k].parameters["FOS_y"], edges[k].parameters["FOS_b"], edges[k].parameters["FOS_v"], edges[k].parameters["FOS_m"]});
    }
}

#if RULE_SET == SHEA_FRAME
void Solution::apply_move_operator(int rule_number) {
    switch(rule_number) {
        case 0:
            move_joint();
            break;
        case 1:
            change_size_single();
            break;
        case 2:
            add_member();
            break;
        case 3:
            remove_member();
            break;
        case 4:
            biad_to_triad();
            break;
        case 5:
            triad_to_biad();
            break;
        default:
            break;
    }

    // Compute the quality
    compute_quality();

    // Increment solution counters and things?
    solution_counter++;
    solution_id++;
}


// This adds a bar triad
void Solution::biad_to_triad(void){
    // Define some things
    std::vector<long double> weights;
    std::vector<std::vector< int > > list;
    int cs;

    // Step through all nodes and remember which have at least 2 connections
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1){
        cs = static_cast<int> (nodes[it1->first].incoming_edges.size() + nodes[it1->first].outgoing_edges.size());
        // TODO Only add edge pairs that are adjacent in terms of angle
        if(cs >= 2 ){
            std::vector< std::vector<int> > connected;
            for(int i=0; i<nodes[it1->first].incoming_edges.size(); i++){
                connected.push_back({edges[nodes[it1->first].incoming_edges[i]].initial_node, nodes[it1->first].incoming_edges[i]});
            }
            for(int i=0; i<nodes[it1->first].outgoing_edges.size(); i++){
                connected.push_back({edges[nodes[it1->first].outgoing_edges[i]].terminal_node, nodes[it1->first].outgoing_edges[i]});
            }
            for(int i=0; i<cs; i++){
                for(int j=i+1; j<cs; j++){
                    list.push_back(std::vector<int> {it1->first, connected[i][0], connected[i][1], connected[j][0], connected[j][1]});
                    weights.push_back(1.0);
                }
            }
        }
    }

    // Select a node to operate on
    if(weights.size()) {
        int idx = weighted_choice(weights);

        // Remove edges
        int d1 = static_cast<int> (edges[list[idx][2]].parameters["r"]);
        int d2 = static_cast<int> (edges[list[idx][4]].parameters["r"]);
        remove_edge(list[idx][2]);
        remove_edge(list[idx][4]);

        // Add joint
        add_joint((nodes[list[idx][0]].parameters["x"] + nodes[list[idx][1]].parameters["x"] + nodes[list[idx][3]].parameters["x"])/3,
                  (nodes[list[idx][0]].parameters["y"] + nodes[list[idx][1]].parameters["y"] + nodes[list[idx][3]].parameters["y"])/3,
                  (nodes[list[idx][0]].parameters["z"] + nodes[list[idx][1]].parameters["z"] + nodes[list[idx][3]].parameters["z"])/3,
                  true);

        // Connect joint
        add_member(node_id_counter, list[idx][0], (d1 + d2)/2, true);
        add_member(node_id_counter, list[idx][1], d1, true);
        add_member(node_id_counter, list[idx][3], d2, true);
    }
}


// This remove a bar triad
void Solution::triad_to_biad(void){
    // Define some things
    std::vector<int> editable = get_node_ids("editable", true);
    std::vector<long double> weights;
    std::vector<std::vector< int > > list;
    int cs;

    // step through all nodes adn remember which have three connections exactly
    for(int i=0; i<editable.size(); i++){
        if(nodes[editable[i]].incoming_edges.size() + nodes[editable[i]].outgoing_edges.size()== 3){

            // Find out which nodes are connected
            std::vector<int> connected = get_neighbors(editable[i]);

            // Push back move options
            list.push_back({editable[i], connected[0], connected[1], connected[2]}); weights.push_back(1.0);
            list.push_back({editable[i], connected[1], connected[2], connected[0]}); weights.push_back(1.0);
            list.push_back({editable[i], connected[2], connected[0], connected[1]}); weights.push_back(1.0);
        }
    }

    // Select what will be removed
    if(weights.size() > 0){
        int idx = weighted_choice(weights);

        // Delete the central node
        remove_node(list[idx][0]);

        // Add edges
        add_member(list[idx][1], list[idx][2], 4, true);
        add_member(list[idx][2], list[idx][3], 4, true);
    }
}
#endif

#if RULE_SET == SHEA_TRUSS
void Solution::apply_move_operator(int rule_number){
    switch(rule_number) {
        case 0:
            move_joint();
            break;
        case 1:
            change_size_single();
            break;
        case 2:
            flip_flop();
            break;
        case 3:
            add_bisection();
            break;
        case 4:
            remove_bisection();
            break;
        case 5:
            add_trisection();
            break;
        case 6:
            remove_trisection();
        default:
            break;
    }

    // Compute the quality
    compute_quality();

    // Increment solution counters and things?
    solution_counter++;
    solution_id++;
}


// Comment
void Solution::flip_flop(void){
    //Initialize a few things
    std::vector<int> common;
    std::vector< std::vector<int> > list;
    std::vector<long double> weights;
    int cs;

    // Find the valid things
    for(std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); ++it1){
        common = find_common_neighbors(edges[it1->first].initial_node, edges[it1->first].terminal_node);
        cs = static_cast<int> (common.size());
        if(cs >=2){
            for(int i=0; i<cs; i++){
                for(int j=i+1; j<cs; j++){
                    list.push_back(std::vector<int> {it1->first, common[i], common[j]});
                    weights.push_back(1.0);
                }
            }
        }
    }

    // Select a flip-flop at random
    if(weights.size() > 0){
        int idx = weighted_choice(weights);

        // Delete the edge
        remove_edge(list[idx][0]);

        // Add the edge
        add_member(list[idx][1], list[idx][2], 4, true);
    }
}


// Comment
void Solution::add_bisection(void){

    //Initialize a few things
    std::vector<int> common;
    std::vector< std::vector<int> > list;
    std::vector<long double> weights;
    int cs;

    // Find the valid things
    for(std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); ++it1){
        common = find_common_neighbors(edges[it1->first].initial_node, edges[it1->first].terminal_node);
        cs = static_cast<int> (common.size());
        for(int i=0; i<cs; i++){
            list.push_back(std::vector<int> {it1->first, common[i]});
            weights.push_back(1.0/edges[it1->first].parameters["FOS_b"]);
        }
    }

    // Select a bisection to add at random
    if(weights.size() > 0){
        int idx = weighted_choice(weights);

        // Pull information from the doomed edge
        int n1 = edges[list[idx][0]].initial_node;
        int n2 = edges[list[idx][0]].terminal_node;
        int d = static_cast<int>(edges[list[idx][0]].parameters["r"]);

        // Add a joint at the midpoint
        add_joint((nodes[n1].parameters["x"] + nodes[n2].parameters["x"])/2,
                  (nodes[n1].parameters["y"] + nodes[n2].parameters["y"])/2,
                  (nodes[n1].parameters["z"] + nodes[n2].parameters["z"])/2,
                  true);

        // Remove the doomed edge
        remove_edge(list[idx][0]);

        // Save its children
        add_member(node_id_counter, list[idx][1], 4, true);
        add_member(node_id_counter, n1, d, true);
        add_member(node_id_counter, n2, d, true);
    }
}


void Solution::remove_bisection(void) {
    //Initialize a few things
    std::vector<std::vector<int> > list;
    std::vector<long double> weights;

    // Find the valid bisections
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        if (nodes[it1->first].parameters["editable"]) {
            if (nodes[it1->first].incoming_edges.size() + nodes[it1->first].outgoing_edges.size() == 3) {
                // Get total FOS of edges
                long double this_weight = 0;
                for(int i=0; i<nodes[it1->first].outgoing_edges.size(); i++){
                    this_weight = edges[nodes[it1->first].outgoing_edges[i]].parameters["FOS_lim"];
                }
                for(int i=0; i<nodes[it1->first].incoming_edges.size(); i++){
                    this_weight = edges[nodes[it1->first].incoming_edges[i]].parameters["FOS_lim"];
                }
                std::vector<int> neighbors = get_neighbors(it1->first);
                list.push_back({it1->first, neighbors[0], neighbors[1]}); weights.push_back(this_weight);
                list.push_back({it1->first, neighbors[2], neighbors[0]}); weights.push_back(this_weight);
                list.push_back({it1->first, neighbors[1], neighbors[2]}); weights.push_back(this_weight);
            }
        }
    }

    // Select a bisection at random
    if (weights.size() > 0) {
        int idx = weighted_choice(weights);

        // Remove that bisection
        remove_node(list[idx][0]);

        // Add the member back
        add_member(list[idx][1], list[idx][2], 4, true);
    }
}

// Comment
void Solution::add_trisection(void){
    //Initialize a few things
    std::vector<int> common;
    std::vector< std::vector<int> > list;
    std::vector<long double> weights;
    int cs;

    // Find the valid things
    for(std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); ++it1){
        common = find_common_neighbors(edges[it1->first].initial_node, edges[it1->first].terminal_node);
        cs = static_cast<int> (common.size());
        for(int i=0; i<cs; i++){
            list.push_back(std::vector<int> {edges[it1->first].initial_node, edges[it1->first].terminal_node, common[i]});
            weights.push_back(1.0);
        }
    }

    // Select a flip-flop at random
    if(weights.size() > 0){
        int idx = weighted_choice(weights);

        // Add a node in the middle of all the other nodes
        add_joint((nodes[list[idx][0]].parameters["x"] + nodes[list[idx][1]].parameters["x"] + nodes[list[idx][2]].parameters["x"])/3,
                  (nodes[list[idx][0]].parameters["y"] + nodes[list[idx][1]].parameters["y"] + nodes[list[idx][2]].parameters["y"])/3,
                  (nodes[list[idx][0]].parameters["z"] + nodes[list[idx][1]].parameters["z"] + nodes[list[idx][2]].parameters["z"])/3,
                  true);

        // Add three connecting edges
        add_member(node_id_counter, list[idx][0], 4, true);
        add_member(node_id_counter, list[idx][1], 4, true);
        add_member(node_id_counter, list[idx][2], 4, true);
    }
}


// Comment
void Solution::remove_trisection(void){
    //Initialize a few things
    std::vector<int> list;
    std::vector<long double> weights;

    // Find the valid trisecitons
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1){
        // Check if node is editable
        if (nodes[it1->first].parameters["editable"]){
            // Check if it has three connections
            if(nodes[it1->first].incoming_edges.size() + nodes[it1->first].outgoing_edges.size() == 3) {
                // Find neighboring nodes
                std::vector<int> neighbors = get_neighbors(it1->first);

                // Check if its connections are connected
                if (   undirected_edge_exists(neighbors[0], neighbors[1])
                    && undirected_edge_exists(neighbors[2], neighbors[1])
                    && undirected_edge_exists(neighbors[0], neighbors[2])) {
                    list.push_back(it1->first);

                    // Get total FOS of edges
                    long double this_weight = 0;
                    for(int i=0; i<nodes[it1->first].outgoing_edges.size(); i++){
                        this_weight = edges[nodes[it1->first].outgoing_edges[i]].parameters["FOS_lim"];
                    }
                    for(int i=0; i<nodes[it1->first].incoming_edges.size(); i++){
                        this_weight = edges[nodes[it1->first].incoming_edges[i]].parameters["FOS_lim"];
                    }

                    weights.push_back(this_weight);
                }
            }
        }
    }

    // Select a bisection at random
    if (weights.size() > 0){
        int idx = weighted_choice(weights);
        // Remove that trisection
        remove_node(list[idx]);
    }
}
#endif

#if RULE_SET == MCCOMB
void Solution::apply_move_operator(int rule_number){
    switch(rule_number) {
        case 0:
            add_joint_and_attach();
            break;
        case 1:
            remove_joint();
            break;
        case 2:
            add_member();
            break;
        case 3:
            remove_member();
            break;
        case 4:
            change_size_single();
            break;
        case 5:
            change_size_all();
            break;
        case 6:
            move_joint();
            break;
        default:
            break;
    }

    // Compute the quality
    compute_quality();

    // Increment solution counters and things?
    solution_counter++;
    solution_id++;

}
#endif


// This deterministically adds a member as specified. Primarily a utility function.
void Solution::add_member(int n1, int n2, int r, bool editable){
    if(!undirected_edge_exists(n1, n2)) {
        // Add the edge to the graph
        add_edge(n1, n2);

        // Add parameters to the edges
        edges[edge_id_counter].parameters["editable"] = editable;
        edges[edge_id_counter].parameters["r"] = r;
        edges[edge_id_counter].parameters["t"] = r;
        update_length(edge_id_counter);
        update_sectional_properties(edge_id_counter);
    }
}


// This function adds a member between two random joints
void Solution::add_member(void){
    // Define some things
    if(number_of_nodes*number_of_nodes > number_of_edges) {
        long double min_distance = LDBL_MAX;
        long double new_distance;
        int n1 = -1;
        int n2 = -1;
        for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
            for (std::map<int, Node>::iterator it2 = std::next(it1, 1); it2 != nodes.end(); it2++) {
                if (!undirected_edge_exists(it1->first, it2->first)) {
                    if(!(std::abs((it1->first)-(it2->first)) > 1 && (it1->first)<5 && (it2->first)<5)) {
                        new_distance = euclidean_distance(it1->first, it2->first);
                        if (new_distance < min_distance) {
                            n1 = it1->first;
                            n2 = it2->first;
                            min_distance = new_distance;
                        }
                    }
                }
            }
        }

        // Add the member
        if (!(n1 == -1 && n2 == -1)){
            add_member(n1, n2, 4, true);
        }
    }
}


// This function adds a joint to the space.
void Solution::add_joint(long double x, long double y, long double z, bool editable){
    // Add the node
    add_node();

    // Add the coordinates
    nodes[node_id_counter].parameters["x"] = x;
    nodes[node_id_counter].parameters["y"] = y;
    nodes[node_id_counter].parameters["z"] = z;

    // Add other miscellaneous parameters, assuming joint is free
    nodes[node_id_counter].parameters["Fx"] = 0;
    nodes[node_id_counter].parameters["Fy"] = 0;
    nodes[node_id_counter].parameters["Fz"] = 0;
    nodes[node_id_counter].parameters["rx"] = 0;
    nodes[node_id_counter].parameters["ry"] = 0;
    nodes[node_id_counter].parameters["rz"] = 1;

    // Moveable or not
    nodes[node_id_counter].parameters["editable"] = editable;
}


// This function removes a member at random
void Solution::remove_member(void) {
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);

    // Make a selection
    if(editable.size() > 0){
        // Instantiate a weighting vector
        std::vector<long double> weights(editable.size(), 0.0);

        // Step through the avaialable members to fill the weighting vector
        for(int i=0; i<editable.size(); i++) {
            weights[i] = edges[editable[i]].parameters["FOS_lim"];
        }

        // Remove the edge that is chosen!
        remove_edge(editable[weighted_choice(weights)]);
    }
}


// This function removes a joint at random (as well as connected members)
void Solution::remove_joint(void) {
    // Define some things
    std::vector<int> editable = get_node_ids("editable", true);

    // Make a selection
    if(editable.size() > 0){
        // Instantiate a weighting vector
        std::vector<long double> weights(editable.size(), 0.0);

        // Fill the weighting vector
        for (int i=0; i<editable.size(); i++){
            for(int j=0; j<nodes[editable[i]].incoming_edges.size(); j++) {
                weights[i] += edges[nodes[editable[i]].incoming_edges[j]].parameters["FOS_lim"];
            }
            for(int j=0; j<nodes[editable[i]].outgoing_edges.size(); j++) {
                weights[i] += edges[nodes[editable[i]].outgoing_edges[j]].parameters["FOS_lim"];
            }
        }

        // Remove the chosen joint
        remove_node(editable[weighted_choice(weights)]);
    }
}


// Changes the size of a single member chosen at random
void Solution::change_size_single(void){
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 0.0);

    // Instantiate the vector of weights
    for(int i=0; i<editable.size(); i++) {
        weights[i] = std::abs(edges[editable[i]].parameters["FOS_lim"] - 1.25);
    }
    if (FOS < 1.25) {
        for (int i = 0; i < editable.size(); i++) {
            if (edges[editable[i]].parameters["FOS_lim"] > 1.25) {
                weights[i] = 0.0;
            }
        }
    }

    // Make a selection
    int idx = weighted_choice(weights);

    // Increase the size of the selected edge
    int inc_dec = uniform_int(1, 0)*2 - 1;

    if ((edges[editable[idx]].parameters["r"] + inc_dec) < member_radius.size()
        && (edges[editable[idx]].parameters["r"] + inc_dec) >= 0){
        edges[editable[idx]].parameters["r"] += inc_dec;
        edges[editable[idx]].parameters["t"] += inc_dec;
        update_sectional_properties(editable[idx]);
    }
}


// Changes the size of all members
void Solution::change_size_all(void){
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);

    // Decide whether ot increase or decrease
    long double inc_dec = 0.0001; // Instantiate to non-zero to break ties
    for (int i=0; i<editable.size(); i++){
        if(edges[editable[i]].parameters["FOS_lim"] < 1.25) {
            inc_dec += 1;
        } else {
            inc_dec -= 1;
        }
    }
    inc_dec /= std::abs(inc_dec);

    for(int i=0; i<editable.size(); i++){
        if ((edges[editable[i]].parameters["r"] + inc_dec) < member_radius.size()
            && (edges[editable[i]].parameters["r"] + inc_dec) >= 0){
            edges[editable[i]].parameters["r"] += inc_dec;
            edges[editable[i]].parameters["t"] += inc_dec;
            update_sectional_properties(editable[i]);
        }
    }
}


// This function randomly moves a joint.
void Solution::move_joint(void){
    // Define a couple of things
    std::vector<int> editable = get_node_ids("editable", true);
    if(editable.size() > 0){

        // Select one to move at random
        std::vector<long double> weights(editable.size(), 1.0);
        int key = editable[weighted_choice(weights)];

        // Move it somehow
        long double step_size = 2.0;
        int max_iter = 8;
        long double best_quality = quality[0];
        std::vector< std::vector< long double> > unit_direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for(int i=0; i<max_iter; i++){
            for(int j=0; j<4; j++){
                // Try a move in the j^th direction
                nodes[key].parameters["x"] += unit_direction[j][0]*step_size;
                nodes[key].parameters["y"] += unit_direction[j][1]*step_size;

                // Compute quality
                compute_quality();

                // If improved, keep and break. Else, reverse.
                if(quality[0] < best_quality) {
                    best_quality = quality[0];
                    break;
                } else {
                    nodes[key].parameters["x"] -= unit_direction[j][0]*step_size;
                    nodes[key].parameters["y"] -= unit_direction[j][1]*step_size;
                };

                // If j == 4 without improvement, halve step size
                if (j==4) {
                    step_size /= 2.0;
                }

                // If the step size gets too small, exit. Its good enough.
                if (step_size < 0.1) {
                    i = max_iter;
                }
            }
        }

        //Update length related properties for the node that we moved.
        for(int i=0; i < nodes[key].outgoing_edges.size(); i++){
            update_length(nodes[key].outgoing_edges[i]);
        }
        for(int i=0; i < nodes[key].incoming_edges.size(); i++){
            update_length(nodes[key].incoming_edges[i]);
        }
    }
}


// Function to add a joint and attach it to the nearest available joints.
void Solution::add_joint_and_attach(void){
    // Add the new joint
    add_joint(uniform(5, -5), uniform(3, -3), 0.0, true);

    // Find distance between current joint and other joints
    std::vector<long double> distances;
    std::vector<int> reverse_map;
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++){
        distances.push_back(euclidean_distance(node_id_counter, it1->first));
        reverse_map.push_back(it1->first);
    }

    // Connect the newest joint to the three nearest existing joints
    long idx;
    for(int i=0; i<3; i++){
        idx = vector_argmin(distances);
        distances[idx] = LDBL_MAX;
        add_member(node_id_counter, reverse_map[idx], 4, true);
    }
}


void Solution::update_length(int e){
    // Update the length
    edges[e].parameters["L"] = euclidean_distance(edges[e].initial_node, edges[e].terminal_node);

    // Compute the mass of the member
    calculate_member_mass(e);
}


void Solution::update_sectional_properties(int e){
    // Update the area
    long double outer = member_radius[edges[e].parameters["r"]];
    long double inner = outer - wall_thickness[edges[e].parameters["t"]];
    edges[e].parameters["A"] = M_PI*(std::pow(outer, 2) - std::pow(inner, 2));

    // Update the area moment of inertia
    edges[e].parameters["I"] = M_PI*(std::pow(2*outer, 4) - std::pow(2*inner, 4))/64;

    // Compute the mass of the member
    calculate_member_mass(e);
}


// Updates the mass of the member
void Solution::calculate_member_mass(int e){
    // Compute the mass of the member
    edges[e].parameters["m"] = edges[e].parameters["L"]*edges[e].parameters["A"]*density;
}


// Function to ensure that the solution is valid
bool Solution::is_valid(void) {
    // Make sure forces nodes are connected by 2, and supports are connected by at least 1
    bool LOADS = true;
    bool SUPPORTS = true;
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
        if(nodes[it->first].parameters["editable"] == false){
            if(  std::abs(nodes[it->first].parameters["Fx"])
               + std::abs(nodes[it->first].parameters["Fy"])
               + std::abs(nodes[it->first].parameters["Fz"]) !=0) {
                if(nodes[it->first].incoming_edges.size() + nodes[it->first].outgoing_edges.size() < 2){
                    LOADS = false;
                    break;
                }
            } else {
                if(nodes[it->first].incoming_edges.size() + nodes[it->first].outgoing_edges.size() < 1){
                    SUPPORTS = false;
                    break;
                }
            }
        }
    }

    // Make sure at least statically determinant
    bool STABLE = false;
    int number_of_reactions = 0;
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
        number_of_reactions += nodes[it->first].parameters["rx"];
        number_of_reactions += nodes[it->first].parameters["ry"];
        number_of_reactions += nodes[it->first].parameters["rz"];
    }
    if (number_of_edges + number_of_reactions >= 3*number_of_nodes) {
        STABLE = true;
    }

    // Mkae sure the stiffness matrix isn't singular
    if(cond > std::pow(10, -5) || is_nan(cond)) {
        STABLE = false;
    }

    return LOADS && SUPPORTS && STABLE;
}

// Save in an X3D file format
void Solution::save_as_x3d(std::string save_to_file) {
    WriteX3D x3d;
    int n1, n2;

    // Open the file
    x3d.open_file(save_to_file);

    // Add the fos
    std::string the_fos;
    the_fos.append("fos = ");
    the_fos.append(std::to_string(FOS));
    x3d.add_html("h1", the_fos);

    // Add the mass
    std::string the_mass;
    the_mass.append("mass = ");
    the_mass.append(std::to_string(mass));
    x3d.add_html("h1", the_mass);

    // Add the SWR
    std::string the_swr;
    the_swr.append("SWR = ");
    the_swr.append(std::to_string((FOS/std::abs(goal[1]))*(goal[0]/mass)));
    x3d.add_html("h1", the_swr);

    // Add the SWR
    std::string the_q;
    the_q.append("Q = ");
    the_q.append(std::to_string(apply_weighting(quality, {0.5, 0.5})));
    x3d.add_html("h1", the_q);

    #if PROBLEM_NUMBER == 0
        x3d.start_scene(0, 1, 10);
    #elif PROBLEM_NUMBER == 1
        x3d.start_scene(2.5, 7.5, 30);
    #elif PROBLEM_NUMBER == 2
        x3d.start_scene(5, 5, 20);
    #elif PROBLEM_NUMBER == 3
        x3d.start_scene(0, 1, 10);
    #endif
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        x3d.write_sphere(nodes[it1->first].parameters["x"], nodes[it1->first].parameters["y"], nodes[it1->first].parameters["z"], 0.25);
    }

    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        n1 = edges[it1->first].initial_node;
        n2 = edges[it1->first].terminal_node;
        x3d.write_line(nodes[n1].parameters["x"], nodes[n1].parameters["y"], nodes[n1].parameters["z"],
                       nodes[n2].parameters["x"], nodes[n2].parameters["y"], nodes[n2].parameters["z"],
                       static_cast<int> (edges[it1->first].parameters["r"]));
    }

    x3d.close_scene();
    x3d.close_file();
}

#endif
