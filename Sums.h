#pragma once
#include <vector>
unsigned sum_omp_reduce(std::vector<unsigned> v, unsigned n);
unsigned sum(std::vector<unsigned> v, unsigned n);
unsigned sum_round_robin(std::vector<unsigned> v, unsigned n);
unsigned round_robin(std::vector<unsigned> v, unsigned n);
unsigned mutex_rb_rr(std::vector <unsigned> v, unsigned n);
unsigned localization_sum(unsigned* v, unsigned n);
unsigned sum_c_mutex(unsigned* v, unsigned v_size);
unsigned sum_cpp_mutex(std::vector <unsigned> v, unsigned v_size);
unsigned sum_round_robin_No_Localization(unsigned* v, unsigned n);