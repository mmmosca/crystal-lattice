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
#include <crystal_lattice/geom.h>


double roundToNthDecimal(double i, int n) {
	return std::round(i * n * 10)/(n * 10);
}

Eigen::Matrix3d getCartesianSystem(std::vector<double> params) {
	
	assert(params.size() == 6);

	Eigen::Matrix3d vector_matrix;
	double a_norm = params[0],
		b_norm = params[1],
		c_norm = params[2],
		alpha = params[3],
		beta = params[4],
		gamma = params[5],
		rad_alpha = alpha * pi / 180,
		rad_beta = beta * pi / 180,
		rad_gamma = gamma * pi / 180;

	double factor, zx_sqrt, Volume;
	vector_matrix.col(0) << a_norm, 0, 0;
	vector_matrix.col(1) << b_norm * cos(rad_gamma), b_norm * sin(rad_gamma), 0;

	factor = (cos(rad_alpha) - cos(rad_gamma)*cos(rad_beta)) / sin(rad_gamma);
	Volume = a_norm * b_norm * c_norm * std::sqrt(1-std::pow(cos(rad_alpha),2)-std::pow(cos(rad_beta), 2)-std::pow(cos(rad_gamma), 2)+ 2 * cos(rad_alpha) * cos(rad_beta) * cos(rad_gamma));
	vector_matrix.col(2) << c_norm * cos(rad_beta), c_norm * factor, Volume / (a_norm*b_norm*sin(rad_gamma));

	return vector_matrix;
}
