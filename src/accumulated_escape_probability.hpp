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
