#include "reader.hpp"

void read_base_point(type_point &point, type_base_map &point_map, FILE
		*in_file, int n)
{
	point.solution.resize(n);
	for (int i = 0; i < n; i++) {
		fread(&(point.solution[i]), sizeof(int), 1, in_file);
	}
	fread(&(point.cost), sizeof(long), 1, in_file);
	type_base_info point_info;
	point_info.local_opt.solution.resize(n);
	for (int i = 0; i < n; i++) {
		fread(&(point_info.local_opt.solution[i]), sizeof(int), 1, in_file);
	}
	fread(&(point_info.local_opt.cost), sizeof(long), 1, in_file);
	fread(&(point_info.descent_count), sizeof(int), 1, in_file);
	fread(&(point_info.improv_neighbors_count), sizeof(long), 1, in_file);
	fread(&(point_info.best_neighbor_cost), sizeof(long), 1, in_file);
	point_map[point] = point_info;
}

int read_base_sample(type_base_sample &base_sample, FILE* in_file, int n)
{
	int sample_size;
	fread(&(sample_size), sizeof(int), 1, in_file);
	base_sample.base_vector.resize(sample_size);
	for (int i = 0; i < sample_size; i++) {
		read_base_point(base_sample.base_vector[i], base_sample.base_map, in_file, n);
	}
	return sample_size;
}

void read_opt_point(type_point &point, type_opt_map &point_map, FILE *in_file,
		int n)
{
	point.solution.resize(n);
	for (int i = 0; i < n; i++) {
		fread(&(point.solution[i]), sizeof(int), 1, in_file);
	}
	fread(&(point.cost), sizeof(long), 1, in_file);
	type_opt_info point_info;
	fread(&(point_info.basin_size), sizeof(int), 1, in_file);
	point_map[point] = point_info;
}

void read_best_set(type_solution_set &best_set, FILE *in_file, int n)
{
	int best_set_size;
	fread(&(best_set_size), sizeof(int), 1, in_file);
	type_point best_point;
	best_point.solution.resize(n);
	for (int k = 0; k < best_set_size; k++) {
		for (int i = 0; i < n; i++) {
			fread(&(best_point.solution[i]), sizeof(int), 1, in_file);
		}
		fread(&(best_point.cost), sizeof(long), 1, in_file);
		best_set.insert(best_point);
	}
}

void read_ls_sample(type_ls_sample &ls_sample, FILE* in_file, int n)
{
	int sample_size;
	fread(&(sample_size), sizeof(int), 1, in_file);
	ls_sample.opt_vector.resize(sample_size);
	for (int i = 0; i < sample_size; i++) {
		read_opt_point(ls_sample.opt_vector[i], ls_sample.opt_map,
				in_file, n);
	}
	read_best_set(ls_sample.best_opt_set, in_file, n);
	fread(&(ls_sample.best_cost), sizeof(long), 1, in_file);
}

int read_results(type_sampling &sample, int &n, char* file_name)
{
	FILE *in_file = fopen(file_name, "rb");
	fread(&(n), sizeof(int), 1, in_file);
	int sample_size = read_base_sample(sample.base, in_file, n);
	type_point t = sample.base.base_vector[0];
	read_ls_sample(sample.opt, in_file, n);
	fclose(in_file);
	return sample_size;
}
