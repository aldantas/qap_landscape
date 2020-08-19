#ifndef PRINTER_INCLUDED
#define PRINTER_INCLUDED value
#include "common.hpp"

void print_vector(type_vector p);

void print_matrix(type_matrix p, int n);

void print_base_point(type_point point, type_base_map base_map, int n);

void print_opt_point(type_point point, type_opt_map opt_map);

void print_best_set(type_ls_sample ls_sample);
#endif /* ifndef PRINTER_INCLUDED */
