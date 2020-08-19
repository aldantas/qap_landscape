#include "common.hpp"
#include "accumulated_escape_probability.hpp"
#include "fitness_distance_correlation.hpp"
#include "negative_slope_coefficient.hpp"
#include "printer.hpp"
#include "reader.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>

char *input_filename = NULL;
int cropped_sample_size = 0;

typedef struct features_struct {
	int n_local_optima;
	int n_best_optima;
	double opt_fitness_var_coef;
	double avg_descent; // divided by instance size
	/* double descent_var_coef; */
	/* double avg_best_basin; */

	double fitness_distance_correlation;
	double avg_distance_to_best; // divided by instance size

	double acumulated_escape_probability;
	/* double negative_slope_coefficient; */

	double base_dispersion_metric;
	double opt_dispersion_metric;
	/* double inter_dispersion_metric; */
} type_features;

typedef struct dispersions {
	double random;
	double elite;
} type_dispersions;

double average_pairwise_distance(std::vector<type_point> points)
{
	double avg_dist = 0;
	int sample_size = points.size();
	for (int i = 0; i < sample_size-1; i++) {
		for (int j = i+1; j < sample_size; j++) {
			avg_dist += hamming_distance(points[i], points[j]);
		}
	}
	long pairs = (sample_size * (sample_size-1)) / 2;
	return avg_dist / pairs;
}

bool compare_points(const type_point &p1, const type_point &p2)
{
	return p1.cost < p2.cost;
}

type_dispersions compute_dm(std::vector<type_point> points, float threshold_level)
{
	int threshold = points.size() * threshold_level;
	if (threshold < 2) threshold = 2;
	std::vector<type_point> sub_sample(points.begin(),
			points.begin()+threshold);
	double random_disperion = average_pairwise_distance(sub_sample);

	std::sort(points.begin(), points.end(), compare_points);
	sub_sample = std::vector<type_point>(points.begin(),
			points.begin()+threshold);
	double elite_disperion = average_pairwise_distance(sub_sample);

	return {random_disperion, elite_disperion};
}

type_stats descent_stats(type_base_map base_map)
{
	type_stats descents;
	for (auto elem: base_map) {
		add_value_to_stat(descents, elem.second.descent_count);
	}
	set_mean_std(descents);
	return descents;
}

double compute_avg_best_basin(type_ls_sample ls_sample)
{
	double avg_basin = 0;
	for (type_point best_point: ls_sample.best_opt_set) {
		avg_basin += ls_sample.opt_map[best_point].basin_size;
	}
	return avg_basin / ls_sample.best_opt_set.size();
}

void print_features(type_features ft)
{
	/* std::cout << ft.n_local_optima << std::endl; */
	/* std::cout << ft.n_best_optima << std::endl; */
	std::cout << std::setprecision(4) << std::fixed;
	std::cout << ft.opt_fitness_var_coef << std::endl;
	/* std::cout << ft.avg_best_basin << std::endl; */
	std::cout << ft.avg_descent << std::endl;
	/* std::cout << ft.descent_var_coef << std::endl; */
	std::cout << ft.fitness_distance_correlation << std::endl;
	std::cout << ft.avg_distance_to_best << std::endl;
	std::cout << ft.acumulated_escape_probability << std::endl;
	/* std::cout << ft.negative_slope_coefficient << std::endl; */
	std::cout << ft.base_dispersion_metric << std::endl;
	std::cout << ft.opt_dispersion_metric << std::endl;
	/* std::cout << ft.inter_dispersion_metric << std::endl; */
}

void print_features_name(type_features ft)
{
	/* std::cout << "n_local_opt: " << ft.n_local_optima << std::endl; */
	/* std::cout << "n_best_opt: " << ft.n_best_optima << std::endl; */
	std::cout << std::setprecision(4) << std::fixed;
	std::cout << "opt_fit_coef: " << ft.opt_fitness_var_coef << std::endl;
	/* std::cout << "avg_best_basin: " << ft.avg_best_basin << std::endl; */
	std::cout << "avg_descent: " << ft.avg_descent << std::endl;
	/* std::cout << "descent_coef: " << ft.descent_var_coef << std::endl; */
	std::cout << "-------" << std::endl;
	std::cout << "fdc: " << ft.fitness_distance_correlation << std::endl;
	std::cout << "avg_dst: " << ft.avg_distance_to_best << std::endl;
	std::cout << "aep: " << ft.acumulated_escape_probability << std::endl;
	/* std::cout << "nsc: " << ft.negative_slope_coefficient << std::endl; */
	std::cout << "-------" << std::endl;
	std::cout << "base_dm: " << ft.base_dispersion_metric << std::endl;
	std::cout << "opt_dm: " << ft.opt_dispersion_metric << std::endl;
	/* std::cout << "inter_dm: " << ft.inter_dispersion_metric << std::endl; */
}

type_features compute_features(type_sampling sample, int n)
{
	type_features features;
	/* features.n_local_optima = sample.opt.opt_map.size(); */
	/* features.n_best_optima = sample.opt.best_opt_set.size(); */

	type_fd fd_measures = fitness_distance_measures(sample.opt.opt_vector, sample.opt.best_opt_set);
	features.fitness_distance_correlation = compute_fdc(fd_measures);
	features.avg_distance_to_best = fd_measures.dists.mean / n;
	features.opt_fitness_var_coef = fd_measures.costs.std_dev / fd_measures.costs.mean;

	/* features.avg_best_basin = compute_avg_best_basin(sample.opt); */

	type_stats descent_st = descent_stats(sample.base.base_map);
	features.avg_descent = descent_st.mean / n;
	/* features.descent_var_coef = descent_st.std_dev / descent_st.mean; */

	features.acumulated_escape_probability = compute_aep(sample.base.base_vector, sample.base.base_map, n);

	/* features.negative_slope_coefficient = compute_nsc(sample.base.base_map); */

	float dm_threshold_level = 0.05;
	type_dispersions base_dispersion = compute_dm(sample.base.base_vector, dm_threshold_level);
	type_dispersions opt_dispersion = compute_dm(sample.opt.opt_vector, dm_threshold_level);
	features.base_dispersion_metric = base_dispersion.elite - base_dispersion.random;
	features.opt_dispersion_metric = opt_dispersion.elite - opt_dispersion.random;
	/* features.inter_dispersion_metric = opt_dispersion.elite - base_dispersion.elite; */

	return features;
}

int load_problem(char* instance_filename, int &n, type_matrix &a, type_matrix &b)
{
	FILE *file = fopen(instance_filename, "r");

	if(file == NULL)
		return -1;

	//reads the number of facilities
	fscanf(file, "%d\n\n", &n);

	a = new long* [n];
	b = new long* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new long[n];
		b[i] = new long[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(file, "%ld", &a[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(file, "%ld", &b[i][j]);
		}
	}

	fclose(file);
	return 0;
}

long compute_cost(type_vector p, int n, type_matrix a, type_matrix b)
{
	long cost = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cost += a[i][j] * b[p[i]][p[j]];
		}
	}
	return cost;
}

/* type_sampling crop_sample(type_sampling full_sample, int new_size, int n, */
/* 		type_matrix a, type_matrix b) */
type_sampling crop_sample(type_sampling full_sample, int new_size)
{
	type_base_sample base_sample;
	type_ls_sample opt_sample;

	type_base_sample full_base = full_sample.base;
	type_ls_sample full_opt = full_sample.opt;

	if (new_size >= full_base.base_vector.size()) {
		return {full_base, full_opt};
	}

	for (int i = 0; i < new_size; i++) {
		type_point point = full_base.base_vector[i];
		base_sample.base_vector.push_back(point);
		base_sample.base_map[point] = full_base.base_map[point];

		type_point opt_point;
		opt_point = base_sample.base_map[point].local_opt;
		/* opt_point.solution = base_sample.base_map[point].local_opt; */
		/* opt_point.cost = compute_cost(opt_point.solution, n, a, b); */
		opt_sample.opt_vector.push_back(opt_point);
		opt_sample.opt_map[opt_point] = full_opt.opt_map[opt_point];
		if (opt_point.cost < opt_sample.best_cost) {
			opt_sample.best_cost = opt_point.cost;
			opt_sample.best_opt_set.clear();
			opt_sample.best_opt_set.insert(opt_point);
		} else if (opt_point.cost == opt_sample.best_cost) {
			opt_sample.best_opt_set.insert(opt_point);
		}
	}
	return {base_sample, opt_sample};
}

void read_parameters(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'f'://input file
					input_filename = argv[++i];
					break;
				case 'c'://cropped sample size
					cropped_sample_size = atoi(argv[++i]);
					break;
				default:
					printf("Parameter %s not defined.\n", argv[i]);
					exit(-1);
			}
		} else {
			printf("Parameter %s not defined.\n", argv[i]);
			exit(-1);
		}
	}
}

int main(int argc, char *argv[])
{
	int n;
	read_parameters(argc, argv);
	type_sampling sample;
	int sample_size = 0;
	if (input_filename != NULL) {
		sample_size = read_results(sample, n, input_filename);
	} else {
		printf("Usage:\n %s -f [input file_path]\n", argv[0]);
		exit(-1);
	}
	if (cropped_sample_size > 1 && cropped_sample_size < sample_size) {
		sample = crop_sample(sample, cropped_sample_size);
	}

	clock_t start = clock();
	type_features features = compute_features(sample, n);
	clock_t total_time = clock() - start;
	print_features(features);

	return 0;
}
