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
#ifndef AEP_INCLUDED
#define AEP_INCLUDED
#include "common.hpp"

#include <map>
#include <vector>

typedef struct fitness_prob_cloud_point_struct {
	double sum;
	int count;
} type_fitness_prob_cloud;

bool is_fitness_present(std::map<long, type_fitness_prob_cloud> fit_cloud, long fitness);

double compute_aep(std::vector<type_point> sample, type_base_map info_map, int n);
#endif /* ifndef AEP_INCLUDED */
