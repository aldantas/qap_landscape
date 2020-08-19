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
#include "negative_slope_coefficient.hpp"

#include <algorithm>

bool compare_cloud_points(const type_fitness_cloud &p1, const type_fitness_cloud &p2)
{
	return p1.base_cost < p2.base_cost;
}

std::vector<type_fitness_cloud> get_fitness_cloud(type_base_map base_map)
{
	std::vector<type_fitness_cloud> fc_points;
	type_fitness_cloud cloud_point;
	for (auto point_tuple: base_map) {
		cloud_point.base_cost = point_tuple.first.cost;
		cloud_point.neighbor_cost = point_tuple.second.best_neighbor_cost;
		fc_points.push_back(cloud_point);
	}
	std::sort(fc_points.begin(), fc_points.end(), compare_cloud_points);
	return fc_points;
}

void size_driven_bisection(std::vector<type_fitness_cloud> points, int
		bin_start, int bin_end, int min_points, long min_size,
		std::vector<int> &bins_idx)
{
	int new_bin_points = (bin_end - bin_start) / 2;
	int split_point = bin_start + new_bin_points;
	bins_idx.push_back(split_point);
	long left_size = points[split_point-1].base_cost - points[bin_start].base_cost;
	long right_size = points[bin_end-1].base_cost - points[split_point].base_cost;
	if (new_bin_points < min_points || left_size <= min_size ||
			right_size <= min_size) {
		return;
	}
	if (left_size >= right_size) {
		bin_end = split_point;
	} else {
		bin_start = split_point;
	}
	size_driven_bisection(points, bin_start, bin_end, min_points, min_size, bins_idx);
}

double compute_nsc(type_base_map base_map)
{
	std::vector<type_fitness_cloud> fc_points = get_fitness_cloud(base_map);

	/* store the beggining index of each bin */
	std::vector<int> bins_idx;
	bins_idx.push_back(0);
	int min_points = 50;
	long min_size = (fc_points.back().base_cost - fc_points.front().base_cost) * 0.05;
	size_driven_bisection(fc_points, 0, fc_points.size(), min_points, min_size, bins_idx);
	/* add the size to get the ending index of the last bin */
	bins_idx.push_back(base_map.size());
	std::sort(bins_idx.begin(), bins_idx.end());

	std::vector<type_fitness_cloud> bin_averages(bins_idx.size() - 1);
	for (int m = 0; m < bins_idx.size() - 1; m++) {
		long begin = bins_idx[m];
		long end = bins_idx[m+1];
		long base_sum = 0;
		long neighbor_sum = 0;
		for (int i = begin; i < end; i++) {
			base_sum += fc_points[i].base_cost;
			neighbor_sum += fc_points[i].neighbor_cost;
		}
		int bin_points = end - begin;
		long bin_size = fc_points[end-1].base_cost - fc_points[begin].base_cost;
		bin_averages[m].base_cost = base_sum / bin_points;
		bin_averages[m].neighbor_cost = neighbor_sum / bin_points;
	}

	double nsc = 0;
	for (int i = 0; i < bin_averages.size() - 1; i++) {
		double slope = bin_averages[i+1].neighbor_cost - bin_averages[i].neighbor_cost;
		slope /= (bin_averages[i+1].base_cost - bin_averages[i].base_cost);
		if (slope > 0) {
			slope = 0;
		}
		nsc += slope;
	}
	return nsc;
}
