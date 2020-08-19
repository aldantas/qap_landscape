#ifndef READER_INCLUDED
#define READER_INCLUDED value
#include "common.hpp"

#include <cstdio>
#include <vector>

void read_base_point(type_point &point, type_base_map &point_map, FILE
		*in_file, int n);

int read_base_sample(type_base_sample &base_sample, FILE* in_file, int n);

void read_opt_point(type_point &point, type_opt_map &point_map, FILE *in_file,
		int n);

void read_best_set(type_solution_set &best_set, FILE *in_file, int n);

void read_ls_sample(type_ls_sample &ls_sample, FILE* in_file, int n);

int read_results(type_sampling &sample, int &n, char* file_name);
#endif /* ifndef READER_INCLUDED */
