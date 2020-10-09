// An example showing TEASER++ registration with the Stanford bunny model
// std
#include <iostream>

// teaser dependencies
#include <Eigen/Core>
#include <teaser/registration.h>

// visualization
#include "polyscope/polyscope.h"
#include "polyscope/point_cloud.h"

// IO 
#include "IO/readPLY.hpp"

// Macro constants for generating noise and outliers
#define NOISE_BOUND 0.05
#define N_OUTLIERS 1700
#define OUTLIER_TRANSLATION_LB 5
#define OUTLIER_TRANSLATION_UB 10


int main() {

    Eigen::MatrixXd src_V, trg_V;
    Eigen::MatrixXi F;

    readPLY("../data/1000point_model.ply", src_V, F);
    readPLY("../data/1000point_scene.ply", trg_V, F);

    std::cout << "Size of src_V: [" << src_V.rows() << ", " << src_V.cols() << "]\n";
    std::cout << "Size of trg_V: [" << trg_V.rows() << ", " << trg_V.cols() << "]\n";

    // polyscope init
    polyscope::init();

    // plot before registration
    polyscope::registerPointCloud("source", src_V.transpose());
    polyscope::registerPointCloud("target", trg_V.transpose());
    polyscope::show();



    // Run TEASER++ registration
    // Prepare solver parameters
    teaser::RobustRegistrationSolver::Params params;
    params.noise_bound = 0.0337;
    params.cbar2 = 1;
    params.estimate_scaling = false;
    params.rotation_max_iterations = 100;
    params.rotation_gnc_factor = 1.4;
    params.rotation_estimation_algorithm =
        teaser::RobustRegistrationSolver::ROTATION_ESTIMATION_ALGORITHM::GNC_TLS; // GNC_TLS or FGR
    params.rotation_cost_threshold = 0.005;

    // Solve with TEASER++
    teaser::RobustRegistrationSolver solver(params);
    solver.solve(src_V, trg_V);

    auto solution = solver.getSolution();


    // extract solution
    double scale = solution.scale;
    Eigen::MatrixXd rot = solution.rotation;
    Eigen::VectorXd tra = solution.translation;
    
    // perform rotation and translation
    src_V = rot  * src_V;
    src_V = src_V.colwise() + tra;

    // plot after registration
    polyscope::registerPointCloud("source", src_V.transpose());
    polyscope::registerPointCloud("target", trg_V.transpose());
    polyscope::show();

}