#include "accumulated_escape_probability.hpp"
#include <iostream>

bool is_fitness_present(std::map<long, type_fitness_prob_cloud> fit_cloud, long fitness)
{
	if (fit_cloud.find(fitness) == fit_cloud.end()) return false;
	else return true;
}

double compute_aep(std::vector<type_point> sample, type_base_map info_map,
		int n)
{
	long nh_size = (long)((n * (n - 1)) / 2);
	std::map<long, type_fitness_prob_cloud> fitness_levels;
	for (int i = 0; i < sample.size(); i++) {
		long fitness = sample[i].cost;
		double escape_rate = (double)info_map[sample[i]].improv_neighbors_count / nh_size;
		if (is_fitness_present(fitness_levels, fitness)) {
			fitness_levels[fitness].sum += escape_rate;
			fitness_levels[fitness].count++;
		} else {
			type_fitness_prob_cloud new_level;
			new_level.sum = escape_rate;
			new_level.count = 1;
			fitness_levels[fitness] = new_level;
		}
	}
	double aep= 0;
	/* std::cout << fitness_levels.size() << std::endl; */
	for (auto level: fitness_levels) {
		aep += level.second.sum / level.second.count;
	}
	/* std::cout << aep << std::endl; */
	return aep / fitness_levels.size();
}
