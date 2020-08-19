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
