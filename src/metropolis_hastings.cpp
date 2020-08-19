#include "common.hpp"
#include "best_improv.hpp"
#include "printer.hpp"
#include "writer.hpp"

#include <iostream>
#include <ctime>
#include <random>

std::random_device rd; // obtain a random number from hardware
std::mt19937 eng(rd()); // seed the generator

char *input_filename = NULL;
char *output_filename = NULL;
int sample_size = 5000;

int randint(int min, int max)
{
	std::uniform_int_distribution<> distr(min, max); // define the range
	return distr(eng);
}

double rand01()
{
	std::uniform_real_distribution<> distr(0.0, 1.0); // define the range
	return distr(eng);
}

void read_parameters(int argc, char **argv)
{
	if(argc < 3){
		printf("Usage:\n %s -f [input file_path]\n", argv[0]);
		exit(-1);
	}

	int i=1;
	if(argv[i][0] != '-'){
		printf("Parameter %s not defined.\n", argv[i]);
		exit(-1);
	} else if(argv[i][1] != 'f'){
		printf("Expected first parameter -f [input file_path], found %s .\n", argv[i]);
		exit(-1);
	}

	i++;
	input_filename = argv[i]; //input file path

	for(i=3;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'o'://output file path
					output_filename = argv[++i];
					break;
				case 's'://define sample size
					sample_size = atoi(argv[++i]);
					break;
				default:
					printf("Parameter %s not defined.\n", argv[i]);
					exit(-1);
			}
		}else{
			printf("Parameter %s not defined.\n", argv[i]);
			exit(-1);
		}
	}
}

int load_problem(int &n, type_matrix &a, type_matrix &b)
{
	FILE *file = fopen(input_filename, "r");

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

void compute_cost(type_point &point, type_base_info &info, type_matrix delta,
		type_matrix a, type_matrix b, int n)
{
	type_vector p = point.solution;
	point.cost = 0;
	long delta_idx = 0;
	long best_delta = infinite;
	info.improv_neighbors_count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			point.cost += a[i][j] * b[p[i]][p[j]];
			if (i < j) {
				delta[i][j] = compute_delta(n, a, b, p, i, j);
				if (delta[i][j] <= 0) {
					info.improv_neighbors_count++;
				}
				if (delta[i][j] < best_delta) {
					best_delta = delta[i][j];
				}
			}
		}
	}
	info.best_neighbor_cost = best_delta + point.cost;
}

void generate_random_solution(type_point &point, type_base_info &info,
		type_matrix &delta, type_matrix a, type_matrix b, int n)
{
	int i;
	for (i = 0; i < n; i++) point.solution.push_back(i);
	for (i = 0; i < n; i++) {
		transpose(point.solution[i], point.solution[randint(i, n-1)]);
	}
	compute_cost(point, info, delta, a, b, n);
}

double accept_probability(long current_cost, long candidate_cost)
{
	double alpha_value = (double)current_cost / (double)candidate_cost;
	return alpha_value < 1 ? alpha_value : 1;
}

void local_search_sampling(type_point base_point, type_base_info &base_info,
		type_ls_sample &ls_sample, type_matrix delta, type_matrix a,
		type_matrix b, int n)
{
	type_point opt_point = base_point;
	int descent_count = best_improvement_ls(opt_point.solution,
			opt_point.cost, delta, a, b, n);
	base_info.descent_count = descent_count;
	base_info.local_opt = opt_point;

	if (is_solution_present(ls_sample.opt_map, opt_point)) {
		ls_sample.opt_map[opt_point].basin_size++;
	} else {
		ls_sample.opt_vector.push_back(opt_point);
		/* set basin size */
		ls_sample.opt_map[opt_point] = {1};
	}
	if (opt_point.cost < ls_sample.best_cost) {
		ls_sample.best_cost = opt_point.cost;
		ls_sample.best_opt_set.clear();
		ls_sample.best_opt_set.insert(opt_point);
	} else if (opt_point.cost == ls_sample.best_cost) {
		ls_sample.best_opt_set.insert(opt_point);
	}
}

type_sampling metropolis_hastings_sampling(int sample_size, type_matrix a,
		type_matrix b, int n)
{
	std::vector<type_point> sample(sample_size);
	type_base_map solutions_info_map;

	type_ls_sample ls_sample;
	type_matrix delta = new long*[n];
	for (int i = 0; i < n; i = i+1) {
		delta[i] = new long[n];
	}

	/* type_base_info base_info = new_base_info(n); */
	type_base_info base_info;
	generate_random_solution(sample[0], base_info, delta, a, b, n);
	local_search_sampling(sample[0], base_info, ls_sample, delta, a, b, n);
	solutions_info_map[sample[0]] = base_info;

	float u, alpha;
	for (int k = 1; k < sample_size; k++) {
		/* base_info = new_base_info(n); */
		do {
			generate_random_solution(sample[k], base_info, delta, a, b, n);
			/* compute_cost(n, sample[k], a, b); */
			u = rand01();
			alpha = accept_probability(sample[k-1].cost,
					sample[k].cost);
		} while (u > alpha && is_solution_present(solutions_info_map,
					sample[k]));
		local_search_sampling(sample[k], base_info, ls_sample, delta, a, b, n);
		solutions_info_map[sample[k]] = base_info;
	}

	// free memory
	for (int i=0; i < n; i = i+1)
	{
		delete[] delta[i];
	}
	delete[] delta;
	return {{sample, solutions_info_map}, ls_sample};
}

int main(int argc, char *argv[])
{
	int n;                    // problem size
	type_matrix a, b;         // flows and distances matrices
	type_vector solution;     // solution (permutation)
	read_parameters(argc, argv);
	load_problem(n, a, b);

	clock_t start = clock();
	type_sampling sample_result = metropolis_hastings_sampling(sample_size, a, b, n);
	clock_t total_time = clock() - start;
	std::cout<<"Total Time: " << (total_time)/static_cast<double>(CLOCKS_PER_SEC) << std::endl;

	if (output_filename != NULL) {
		write_results(sample_result, n, output_filename);
	}

	return 0;
}
