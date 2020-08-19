/* QAP-landscape - generate a sample of solutions and compute FLA measures */
/* Copyright (C) 2019  Augusto Lopez Dantas */

/* This program is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU General Public License */
/* as published by the Free Software Foundation; either version 2 */
/* of the License, or (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to the Free Software */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */
#include "printer.hpp"

#include <iostream>

void print_vector(type_vector p)
{
	for (int i = 0; i < p.size(); i++) {
		std::cout << p[i]+1 << " ";
	}
	std::cout << std::endl;
}

void print_matrix(type_matrix p, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i < j) {
				std::cout << p[i][j] << " ";
			}
		}
	}
	std::cout << std::endl;
}

void print_base_point(type_point point, type_base_map base_map, int n)
{
	std::cout << "Base:" << std::endl;
	print_vector(point.solution);
	std::cout << "Cost: " << point.cost << std::endl;
	std::cout << "Descent: " << base_map[point].descent_count << std::endl;
	std::cout << "Local Optimum:" << std::endl;
	print_vector(base_map[point].local_opt.solution);
	std::cout << "Local Optimum Cost: " << base_map[point].local_opt.cost << std::endl;
}

void print_opt_point(type_point point, type_opt_map opt_map)
{
	print_vector(point.solution);
	std::cout << "Cost: " << point.cost << std::endl;
	std::cout << "Basin: " << opt_map[point].basin_size << std::endl;
}

void print_best_set(type_ls_sample ls_sample)
{
	type_solution_set best_set = ls_sample.best_opt_set;
	type_opt_map opt_map = ls_sample.opt_map;
	std::cout << "Best set size: " << best_set.size() << std::endl;
	for (auto point: best_set) {
		print_vector(point.solution);
		std::cout << "Cost: " << point.cost << std::endl;
		std::cout << "Basin: " << opt_map[point].basin_size << std::endl;
	}
}
