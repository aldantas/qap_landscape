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
#include "fitness_distance_correlation.hpp"

type_fd fitness_distance_measures(std::vector<type_point> points_vec,
		type_solution_set best_opt_set)
{

	int m = points_vec.size();
	int n = points_vec[0].solution.size();
	type_fd fd_measures;

	/* calculate pairwise distances and fitness-distances to closest pseudo
	 * optima */
	for (int i = 0; i < m; i++) {
		long cost = points_vec[i].cost;
		add_value_to_stat(fd_measures.costs, cost);
		/* if the solution itself is a pseudo global optima */
		if (is_solution_present(best_opt_set, points_vec[i])) {
			add_value_to_stat(fd_measures.dists, 0);
		} else {
			long shortest_opt_dist = infinite;
			for (auto best_point: best_opt_set) {
				int dist = hamming_distance(points_vec[i], best_point);
				if (dist < shortest_opt_dist) {
					shortest_opt_dist = dist;
				}
			}
			add_value_to_stat(fd_measures.dists, shortest_opt_dist);
		}
	}
	set_mean_std(fd_measures.dists);
	set_mean_std(fd_measures.costs);
	return fd_measures;
}

double compute_fdc(type_fd &fd_stats)
{
	type_stats dists_stats = fd_stats.dists;
	type_stats costs_stats = fd_stats.costs;
	int m = dists_stats.values.size();
	double prod_sum = 0;
	for (int i = 0; i < m; i++) {
		long dist_diff = dists_stats.values[i] - dists_stats.mean;
		long cost_diff = costs_stats.values[i] - costs_stats.mean;
		prod_sum += dist_diff * cost_diff;
	}
	if (prod_sum == 0) {
		return 1.0;
	} else {
		prod_sum /= m;
		return prod_sum / (dists_stats.std_dev * costs_stats.std_dev);
	}
}
