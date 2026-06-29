/*Copyright (C) 2018-2022,2026 Marco M. Mosca

This file is part of crystal-lattice.

crystal-lattice is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

crystal-lattice is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with crystal-lattice. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _GEOM_H
#define _GEOM_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <cassert>

#define math_sign(X) ((X) < 0.f) ? -1 : 1

constexpr double pi = 3.14159265358979323846;

/**
 * @brief Rounds the value `i` to the `n-th` decimal.
 * @param i Value to be rounded.
 * @param n `n-th` decimal to which `i` is rounded to.
 * @return Rounded value.
 */
double roundToNthDecimal(double i, int n);

/**
 * @brief Gets the vector components of the Cartesian system identified by the cell parameters.
 * @param cell_parameters Unit cell parameters in the order
 *        `{||a||, ||b||, ||c||, alpha, beta, gamma}`.
 *        The first three values are edge lengths and the last three are
 *        their opposite angles (degrees).
 * @return The new Cartesian system with vector bases as columns.
 */
Eigen::Matrix3d getCartesianSystem(std::vector<double> cell_parameters);

#endif // !_GEOM_H
