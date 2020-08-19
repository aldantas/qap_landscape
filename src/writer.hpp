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
