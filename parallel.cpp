#include <vector>
#include "omp.h"
#include <mutex>
#include "num_threads.h"
#include <fstream>
#include "own_barrier_latch.h"
#include <thread>
#include "ExperimentsRunner.cpp"
#include "Sums.h"
#include "RandomizeGenerator.h"
#include "classZ.h"

// Method to create csv file from vector that contains scalability_result objects
void to_csv(std::ostream& io, std::vector<scalability_result> v) {
	io << "N,Result,Time,Speedup,Efficiency\n";
	for (unsigned i = 0; i < v.size(); i++) {
		io << i+1 << ',' << v.at(i).result << ',' << v.at(i).t << ',' << v.at(i).s << ',' << v.at(i).e << '\n';
	}
}

void to_csv_rand_result(std::ostream& io, std::vector<scalability_result> v) {
	io << "N,Time,Speedup,Efficiency\n";
	for (unsigned i = 0; i < v.size(); i++) {
		io << i+1 << ',' << v.at(i).t << ',' << v.at(i).s << ',' << v.at(i).e << '\n';
	}
}

int main() {
	
	//randomize experiment
	unsigned sz = 2 << 18; // 2^18 elements in array
	auto randarr = run_experiment_rand(randomize, sz, 0, 1000, 0);
	std::ofstream osrandom("randomize_experiment.csv", std::ios_base::out);
	if (osrandom.is_open()) {
		to_csv_rand_result(osrandom, randarr);
		osrandom.close();
	}
	
	
	/*
	auto sr = run_experiment(sum, 1u, 1u << 25);
	std::ofstream os("sum.csv", std::ios_base::out);
	if (os.is_open()) {
		to_csv(os, sr);
		os.close();
	}

	auto sr1 = run_experiment(sum_omp_reduce, 1u, 1u << 25);
	std::ofstream os1("sum_omp_reduce.csv", std::ios_base::out);
	if (os1.is_open()) {
		to_csv(os1, sr1);
		os1.close();
	}

	auto sr2 = run_experiment(sum_round_robin, 1u, 1u << 25);
	std::ofstream os2("sum_round_robin.csv", std::ios_base::out);
	if (os2.is_open()) {
		to_csv(os2, sr2);
		os2.close();
	}

	auto sr3 = run_experiment(round_robin, 1u, 1u << 25);
	std::ofstream os3("round_robin.csv", std::ios_base::out);
	if (os3.is_open()) {
		to_csv(os3, sr3);
		os3.close();
	}

	auto sr4 = run_experiment(mutex_rb_rr, 1u, 1u << 25);
	std::ofstream os4("mutex_rb_rr.csv", std::ios_base::out);
	if (os4.is_open()) {
		to_csv(os4, sr4);
		os4.close();
	}

	auto sr5 = run_experiment(localization_sum, 1u, 1u << 25);
	std::ofstream os5("localization_sum.csv", std::ios_base::out);
	if (os5.is_open()) {
		to_csv(os5, sr5);
		os5.close();
	}
	
	auto sr6 = run_experiment(sum_cpp_mutex, 1u, 1u << 25);
	std::ofstream os6("sum_cpp_mutex.csv", std::ios_base::out);
	if (os6.is_open()) {
		to_csv(os6, sr6);
		os6.close();
	}

	auto sr7 = run_experiment(sum_round_robin_No_Localization, 1u, 1u << 25);
	std::ofstream os7("sum_round_robin_No_Localization.csv", std::ios_base::out);
	if (os7.is_open()) {
		to_csv(os7, sr7);
		os7.close();
	}
	*/
	/*unsigned* vect = new unsigned[1000000];
	for (unsigned i = 0, j = 0; i < 1000000; i++, j++) {
		vect[j] = i;
	}
	std::cout << localization_sum(vect, 1000000);*/
	

	//std::cout << power(Z<10>(5), 13u).get() << std::endl;
	//std::cout << power(Z<~0u>(5), 13u).get() << std::endl;

	/*const int sz = 1000;
	unsigned* v = new unsigned[sz];
	home_randomize(v, sz, 0, 1000, 2);
	for (int i = 0; i < sz; i++) {
		std::cout << v[i] << " ";
	}*/
	//std::cout << power(Z<2^32>(0x8088405), 10u).get() << std::endl;
	return 0;
}