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
#ifndef BEST_IMPROB_INCLUDED
#define BEST_IMPROB_INCLUDED value
#include "common.hpp"

type_matrix copy_matrix(type_matrix original, int n);

void update_matrix_of_move_cost(int i_retained, int j_retained,long n, type_matrix & delta, type_vector & p, type_matrix & a, type_matrix & b);

void apply_move(type_vector & p,long n, type_matrix & delta, long &
		current_cost, type_matrix a, type_matrix b,int i_retained, int
		j_retained);

void allocate_memory_and_initialize(type_vector & p, long n, type_matrix &
		delta, long & current_cost, type_matrix a, type_matrix b);

bool best_improvement_move(type_vector &p, long n, type_matrix & delta, long &
		current_cost, type_matrix a, type_matrix b);


int best_improvement_ls(type_vector &solution, long &cost, type_matrix
		initial_delta, type_matrix a, type_matrix b, int n);
#endif /* ifndef BEST_IMPROV_INCLUDED */
