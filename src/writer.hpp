#ifndef WRITER_INCLUDED
#define WRITER_INCLUDED value
#include "common.hpp"

#include <cstdlib>
#include <cstdio>
#include <vector>

void write_vector(type_vector vec, FILE *out_file);

void write_base_point(type_point point, type_base_info point_info, FILE *out_file);

void write_base_sample(type_base_sample base_sample, FILE* out_file);

void write_opt_point(type_point point, type_opt_info point_info, FILE *out_file);

void write_best_set(type_solution_set best_set, FILE *out_file);

void write_ls_sample(type_ls_sample ls_sample, FILE* out_file);

void write_results(type_sampling sample, int n, char* file_name);
#endif /* ifndef WRITER_INCLUDED */
