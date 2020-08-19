/* QAP-feature extractor - generate a sample of solutions and compute FLA measures */
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
#ifndef NSC_INCLUDED
#define NSC_INCLUDED
#include "common.hpp"

#include <vector>

typedef struct fitness_cloud_point_struct {
	long base_cost;
	long neighbor_cost;
} type_fitness_cloud;

bool compare_cloud_points(const type_fitness_cloud &p1, const type_fitness_cloud &p2);

std::vector<type_fitness_cloud> get_fitness_cloud(type_base_map base_map);

void size_driven_bisection(std::vector<type_fitness_cloud> points, int
		bin_start, int bin_end, int min_points, long min_size,
		std::vector<int> &bins_idx);

double compute_nsc(type_base_map base_map);

#endif /* ifndef NSC_INCLUDED */
