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
