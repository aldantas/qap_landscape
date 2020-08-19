/* QAP-landscape - generate a sample of solutions and compute FLA measures */
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
#ifndef PRINTER_INCLUDED
#define PRINTER_INCLUDED value
#include "common.hpp"

void print_vector(type_vector p);

void print_matrix(type_matrix p, int n);

void print_base_point(type_point point, type_base_map base_map, int n);

void print_opt_point(type_point point, type_opt_map opt_map);

void print_best_set(type_ls_sample ls_sample);
#endif /* ifndef PRINTER_INCLUDED */
