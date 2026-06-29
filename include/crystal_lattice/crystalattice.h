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
#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include <stdio.h>
#include <Eigen/Dense>
#include <string>
#include <vector>

#include <crystal_lattice/geom.h>
#include <crystal_lattice/unitcellreduction.h>
#include <periodic_point_cloud/periodicpointcloud.h>

/** 
 * @brief Unit Cell of a 3D crystal.
 */
class LatticeUnitCell {
public:
	/**
     * @brief Unit cell parameters in the order
     * 	`{||a||, ||b||, ||c||, alpha, beta, gamma}`.
     * 	The first three values are edge lengths and the last three are
     * 	their opposite angles (degrees).
     */
	std::vector<double> cell_parameters;
	/**
     * @brief The vector components of a unit cell.
     */
	Eigen::Vector3d v_a, v_b, v_c;
	
	/**
     * @brief Computes the volume of the unit cell.
     * @return The volume in cubic Angstroms.
     */
	double getVolume();
};

/** 
 * @brief Represents the 3D underlying periodic structure of a crystal.
 * 
 * Allows the unit cell parameters reduction through Niggli's algorithm.
 * 
 * Example:
 * ```
 * Lattice lattice;
 * int extension = 3;
 * 
 * lattice.setCellParameters({10, 10, 10, 90, 90, 90});
 * lattice.updateParametersToReducedMode();
 * ```
 * If unit cell reduction is not needed use the following instead
 * ```
 * lattice.updateParametersToOriginalMode();
 * ```
 * Then span the 3D lattice by `extension` and retrieve the periodic points
 * ```
 * lattice.spanTheLattice(extension);
 * std::vector<Eigen::Vector3d> pointcloud = ppc.getPointCloud();
 * ```
 */
class Lattice : public LatticeUnitCell, public PeriodicPointCloud {
private:	
	
	void updateCellParameters();
	bool updateReducedCellParameters();

public:
	Lattice() : PeriodicPointCloud(3) {};

	/**
	 * @brief Gets the cell parameters that identify a lattice.
	 * @return The vector of cell parameters.
	 */
	std::vector<double> getCellParameters();

	/**
	 * @brief Sets the six cell parameters that identify the unit cell.
	 * @param cell_params: Unit cell parameters in the order
     * 	`{||a||, ||b||, ||c||, alpha, beta, gamma}`.
     * 	The first three values are edge lengths and the last three are
     * 	their opposite angles (degrees).
	 */
	void setCellParameters(std::vector<double> cell_params);

	/**
     * @brief Updates the vector components to the Reduced Unit Cell system.
     */
	bool updateParametersToReducedMode();

	/**
     * @brief Updates the vector components to the Unit Cell system.
     */
	void updateParametersToOrginalMode();

	/**
	 * @brief Generates the point cloud of a Lattice around the origin.
	 * @param n: Extend the periodic point cloud of a lattice by `n`.
	 * @param positive: If True, the unit cell will be extended only towards positive directions
	 */
	void spanTheLattice(int n, bool positive = false);

	/**
     * @brief Clear the instance of a Lattice.
     */
	void clearTheLattice();
};

#endif // !_STRUCTURE_H
