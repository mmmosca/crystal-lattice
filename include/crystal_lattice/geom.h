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
#include <assert.h>


#define ROUND_D	20
#define math_sign(X) ((X) < 0.f) ? -1 : 1
#define MAX(X,Y)	((X)>=(Y)) ? (X) : (Y)
#define MIN(X,Y)	((X)<=(Y)) ? (X) : (Y)

enum class Axis {X,Y,Z};

using namespace std;

constexpr double pi = 3.14159265358979323846;

double roundToNthDecimal(double i, int n);

/* 
*	This function returns the Cartesian vector components of the 3 unit cell axis 
*	param1 : vector of lengths (a, b, c) and angles (alpha, beta, gamma)
*/
Eigen::Matrix3d getCartesianSystem(std::vector<double> params);

#endif // !_GEOM_H
