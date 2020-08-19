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
#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED
#include <vector>
#include <unordered_set>
#include <unordered_map>

const long infinite = 99999999999;
typedef std::vector<int> type_vector;
typedef long** type_matrix;

typedef struct point {
	type_vector solution;
	long cost;

	bool operator==(const point &other) const
	{
		return solution == other.solution;
	}
} type_point;

typedef struct optimum_info {
	int basin_size;
} type_opt_info;

typedef struct base_info {
	type_point local_opt;
	int descent_count;
	long best_neighbor_cost;
	long improv_neighbors_count;
} type_base_info;

struct point_hasher {
	std::size_t operator()(const type_point& point) const {
		std::size_t seed = point.solution.size();
		for(auto& i : point.solution) {
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

typedef std::unordered_map<type_point, type_base_info, point_hasher> type_base_map;
typedef std::unordered_map<type_point, type_opt_info, point_hasher> type_opt_map;
typedef std::unordered_set<type_point, point_hasher> type_solution_set;

typedef struct base_sampling_result {
	std::vector<type_point> base_vector;
	type_base_map base_map;
} type_base_sample;

typedef struct local_search_result {
	std::vector<type_point> opt_vector;
	type_opt_map opt_map;
	type_solution_set best_opt_set;
	long best_cost = infinite;
} type_ls_sample;

typedef struct stats_struct {
	std::vector<long> values;
	long sum = 0;
	double mean = 0.0;
	double std_dev = 0.0;
} type_stats;

typedef struct sampling_result {
	type_base_sample base;
	type_ls_sample opt;
} type_sampling;

void transpose(int &a, int &b);

/*--------------------------------------------------------------*/
/*       compute the cost difference if elements i and j        */
/*         are transposed in permutation (solution) p           */
/*--------------------------------------------------------------*/
long compute_delta(int n, type_matrix & a, type_matrix & b,
                   type_vector & p, int i, int j);

/*--------------------------------------------------------------*/
/*      Idem, but the value of delta[i][j] is supposed to       */
/*    be known before the transposition of elements r and s     */
/*--------------------------------------------------------------*/
long compute_delta_part(type_matrix & a, type_matrix & b,
                        type_vector & p, type_matrix & delta,
                        int i, int j, int r, int s);

int hamming_distance(type_point point1, type_point point2);

void add_value_to_stat(type_stats &stat, long value);

void set_mean_std(type_stats &stats);

bool is_solution_present(type_solution_set solution_set, type_point point);

bool is_solution_present(type_base_map base_map, type_point point);

bool is_solution_present(type_opt_map opt_map, type_point point);
#endif
