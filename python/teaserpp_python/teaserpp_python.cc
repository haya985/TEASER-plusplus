/**
 * Copyright 2020, Massachusetts Institute of Technology,
 * Cambridge, MA 02139
 * All Rights Reserved
 * Authors: Jingnan Shi, et al. (see THANKS for the full author list)
 * See LICENSE for the license information
 */

#include <string>
#include <sstream>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "teaser/registration.h"

namespace py = pybind11;

/**
 * Python interface with pybind11
 */
PYBIND11_MODULE(teaserpp_python, m) {
  m.doc() = "Python binding for TEASER++";

  // Python bound for teaser::RegistrationSolution
  py::class_<teaser::RegistrationSolution>(m, "RegistrationSolution")
      .def_readwrite("scale", &teaser::RegistrationSolution::scale)
      .def_readwrite("translation", &teaser::RegistrationSolution::translation)
      .def_readwrite("rotation", &teaser::RegistrationSolution::rotation)
      .def("__repr__", [](const teaser::RegistrationSolution& a) {
        std::ostringstream print_string;

        print_string << "<RegistrationSolution with scale=" << a.scale << "\n"
                     << "translation=\n"
                     << a.translation << "\n"
                     << "rotation=\n"
                     << a.rotation << "\n"
                     << ">";
        return print_string.str();
      });

  // Python bound for teaser::RobustRegistraionSolver
  py::class_<teaser::RobustRegistrationSolver> solver(m, "RobustRegistrationSolver");

  // Python bound for teaser::RobustRegistrationSolver functions
  solver.def(py::init<>())
      .def(py::init<const teaser::RobustRegistrationSolver::Params&>())
      .def("getParams", &teaser::RobustRegistrationSolver::getParams)
      .def("reset", &teaser::RobustRegistrationSolver::reset)
      .def("solve", py::overload_cast<const Eigen::Matrix<double, 3, Eigen::Dynamic>&,
                                      const Eigen::Matrix<double, 3, Eigen::Dynamic>&>(
                        &teaser::RobustRegistrationSolver::solve))
      .def("getSolution", &teaser::RobustRegistrationSolver::getSolution)
      .def("getGNCRotationCostAtTermination",
           &teaser::RobustRegistrationSolver::getGNCRotationCostAtTermination)
      .def("getScaleInliersMask", &teaser::RobustRegistrationSolver::getScaleInliersMask)
      .def("getScaleInliersMap", &teaser::RobustRegistrationSolver::getScaleInliersMap)
      .def("getScaleInliers", &teaser::RobustRegistrationSolver::getScaleInliers)
      .def("getRotationInliersMask", &teaser::RobustRegistrationSolver::getRotationInliersMask)
      .def("getRotationInliersMap", &teaser::RobustRegistrationSolver::getRotationInliersMap)
      .def("getRotationInliers", &teaser::RobustRegistrationSolver::getRotationInliers)
      .def("getTranslationInliersMask",
           &teaser::RobustRegistrationSolver::getTranslationInliersMask)
      .def("getTranslationInliersMap", &teaser::RobustRegistrationSolver::getTranslationInliersMap)
      .def("getTranslationInliers", &teaser::RobustRegistrationSolver::getTranslationInliers)
      .def("getInlierMaxClique", &teaser::RobustRegistrationSolver::getInlierMaxClique)
      .def("getInlierGraph", &teaser::RobustRegistrationSolver::getInlierGraph)
      .def("getSrcTIMsMap", &teaser::RobustRegistrationSolver::getSrcTIMsMap)
      .def("getDstTIMsMap", &teaser::RobustRegistrationSolver::getDstTIMsMap)
      .def("getMaxCliqueSrcTIMs", &teaser::RobustRegistrationSolver::getMaxCliqueSrcTIMs)
      .def("getMaxCliqueDstTIMs", &teaser::RobustRegistrationSolver::getMaxCliqueDstTIMs)
      .def("getSrcTIMs", &teaser::RobustRegistrationSolver::getSrcTIMs)
      .def("getDstTIMs", &teaser::RobustRegistrationSolver::getDstTIMs);

  // Python bound for teaser::RobustRegistrationSolver::ROTATION_ESTIMATE_ALGORITHM
  py::enum_<teaser::RobustRegistrationSolver::ROTATION_ESTIMATION_ALGORITHM>(
      solver, "ROTATION_ESTIMATION_ALGORITHM")
      .value("GNC_TLS", teaser::RobustRegistrationSolver::ROTATION_ESTIMATION_ALGORITHM::GNC_TLS)
      .value("FGR", teaser::RobustRegistrationSolver::ROTATION_ESTIMATION_ALGORITHM::FGR);

  // Python bound for teaser::RobustRegistrationSolver::ROTATION_ESTIMATE_ALGORITHM
  py::enum_<teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE>(solver,
                                                                     "INLIER_SELECTION_MODE")
      .value("PMC_EXACT", teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::PMC_EXACT)
      .value("PMC_HEU", teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::PMC_HEU)
      .value("KCORE_HEU", teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::KCORE_HEU)
      .value("NONE", teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::NONE);

  // Python bound for teaser::RobustRegistrationSolver::Params
  py::class_<teaser::RobustRegistrationSolver::Params>(solver, "Params")
      .def(py::init<>())
      .def_readwrite("noise_bound", &teaser::RobustRegistrationSolver::Params::noise_bound)
      .def_readwrite("cbar2", &teaser::RobustRegistrationSolver::Params::cbar2)
      .def_readwrite("estimate_scaling",
                     &teaser::RobustRegistrationSolver::Params::estimate_scaling)
      .def_readwrite("rotation_estimation_algorithm",
                     &teaser::RobustRegistrationSolver::Params::rotation_estimation_algorithm)
      .def_readwrite("rotation_gnc_factor",
                     &teaser::RobustRegistrationSolver::Params::rotation_gnc_factor)
      .def_readwrite("rotation_max_iterations",
                     &teaser::RobustRegistrationSolver::Params::rotation_max_iterations)
      .def_readwrite("inlier_selection_mode",
                     &teaser::RobustRegistrationSolver::Params::inlier_selection_mode)
      .def_readwrite("kcore_heuristic_threshold",
                     &teaser::RobustRegistrationSolver::Params::kcore_heuristic_threshold)
      .def_readwrite("rotation_cost_threshold",
                     &teaser::RobustRegistrationSolver::Params::rotation_cost_threshold)
      .def_readwrite("use_max_clique", &teaser::RobustRegistrationSolver::Params::use_max_clique)
      .def_readwrite("max_clique_exact_solution",
                     &teaser::RobustRegistrationSolver::Params::max_clique_exact_solution)
      .def_readwrite("max_clique_time_limit",
                     &teaser::RobustRegistrationSolver::Params::max_clique_time_limit)
      .def("__repr__", [](const teaser::RobustRegistrationSolver::Params& a) {
        std::ostringstream print_string;

        std::string rot_alg =
            a.rotation_estimation_algorithm ==
                    teaser::RobustRegistrationSolver::ROTATION_ESTIMATION_ALGORITHM::FGR
                ? "FGR"
                : "GNC-TLS";

        std::string inlier_selection_alg;
        if (a.inlier_selection_mode ==
            teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::PMC_EXACT) {
          inlier_selection_alg = "PMC_EXACT";
        }
        if (a.inlier_selection_mode ==
            teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::PMC_HEU) {
          inlier_selection_alg = "PMC_HEU";
        }
        if (a.inlier_selection_mode ==
            teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::KCORE_HEU) {
          inlier_selection_alg = "KCORE_HEU";
        }
        if (a.inlier_selection_mode ==
            teaser::RobustRegistrationSolver::INLIER_SELECTION_MODE::NONE) {
          inlier_selection_alg = "NONE";
        }

        print_string << "<Params with noise_bound=" << a.noise_bound << "\n"
                     << "cbar2=" << a.cbar2 << "\n"
                     << "estimate_sccaling=" << a.estimate_scaling << "\n"
                     << "rotation_estimation_algorithm=" << rot_alg << "\n"
                     << "inlier_selection_mode=" << inlier_selection_alg << "\n"
                     << ">";
        return print_string.str();
      });
}