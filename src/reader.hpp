/* QAP-feature extractor - generate a sample of solutions and compute FLA measures */
/* Copyright (C) 2019  Augusto Lopez Dantas */

/* This program is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU General Public License */
/* as published by the Free Software Foundation; either version 2 */
/* of the License, or (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to the Free Software */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */
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
