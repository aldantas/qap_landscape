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
#ifndef FDC_INCLUDED
#define FDC_INCLUDED
#include "common.hpp"

typedef struct fd_struct {
	type_stats dists;
	type_stats costs;
} type_fd;

type_fd fitness_distance_measures(std::vector<type_point> points_vec,
		type_solution_set best_opt_set);

double compute_fdc(type_fd &fd_stats);
#endif /* ifndef FDC_INCLUDED */
