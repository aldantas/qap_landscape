#include "writer.hpp"
#include <iostream>

void write_vector(type_vector vec, FILE *out_file)
{
	for (int i = 0; i < vec.size(); i++) fwrite(&(vec[i]), sizeof(int), 1, out_file);
}

void write_base_point(type_point point, type_base_info point_info, FILE
		*out_file)
{
	write_vector(point.solution, out_file);
	fwrite(&(point.cost), sizeof(long), 1, out_file);
	write_vector(point_info.local_opt.solution, out_file);
	fwrite(&(point_info.local_opt.cost), sizeof(long), 1, out_file);
	fwrite(&(point_info.descent_count), sizeof(int), 1, out_file);
	fwrite(&(point_info.improv_neighbors_count), sizeof(long), 1, out_file);
	fwrite(&(point_info.best_neighbor_cost), sizeof(long), 1, out_file);
}

void write_base_sample(type_base_sample base_sample, FILE* out_file)
{
	int size = base_sample.base_vector.size();
	fwrite(&(size), sizeof(int), 1, out_file);
	for (auto point: base_sample.base_vector) {
		write_base_point(point, base_sample.base_map[point], out_file);
	}
}

void write_opt_point(type_point point, type_opt_info point_info, FILE *out_file)
{
	write_vector(point.solution, out_file);
	fwrite(&(point.cost), sizeof(long), 1, out_file);
	fwrite(&(point_info.basin_size), sizeof(int), 1, out_file);
}

void write_best_set(type_solution_set best_set, FILE *out_file)
{
	int size = best_set.size();
	fwrite(&(size), sizeof(int), 1, out_file);
	for (auto point: best_set) {
		write_vector(point.solution, out_file);
		fwrite(&(point.cost), sizeof(long), 1, out_file);
	}
}

void write_ls_sample(type_ls_sample ls_sample, FILE* out_file)
{
	int size = ls_sample.opt_vector.size();
	fwrite(&(size), sizeof(int), 1, out_file);
	for (auto point: ls_sample.opt_vector) {
		write_opt_point(point, ls_sample.opt_map[point], out_file);
	}
	write_best_set(ls_sample.best_opt_set, out_file);
	fwrite(&(ls_sample.best_cost), sizeof(long), 1, out_file);
}

void write_results(type_sampling sample, int n, char* file_name)
{
	FILE *out_file = fopen(file_name, "wb");
	fwrite(&(n), sizeof(int), 1, out_file);
	write_base_sample(sample.base, out_file);
	write_ls_sample(sample.opt, out_file);
	fclose(out_file);
}
