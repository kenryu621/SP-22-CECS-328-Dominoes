#include"StudentSolver.h"
#include<iostream>
#include<vector>

int main() {
	std::vector<std::pair<int, int>> test;
	test.push_back(std::pair<int, int>(1, 1));
	test.push_back(std::pair<int, int>(3, 1));
	test.push_back(std::pair<int, int>(2, 1));
	test.push_back(std::pair<int, int>(1, 3));
	test.push_back(std::pair<int, int>(2, 2));
	test.push_back(std::pair<int, int>(1, 2));
	for(std::pair<int,int> test_edge:test){
		std::cout << "(" << test_edge.first << ", " << test_edge.second << ") ";
	}
	std::cout << std::endl;
	StudentSolver::solve(test);
	std::vector<std::pair<int, int>> test2;
	test2.push_back(std::pair<int, int>(1, 2));
	test2.push_back(std::pair<int, int>(1, 3));
	test2.push_back(std::pair<int, int>(1, 5));
	test2.push_back(std::pair<int, int>(1, 4));
	test2.push_back(std::pair<int, int>(2, 4));
	test2.push_back(std::pair<int, int>(2, 6));
	test2.push_back(std::pair<int, int>(3, 5));
	test2.push_back(std::pair<int, int>(4, 5));
	test2.push_back(std::pair<int, int>(4, 6));
	test2.push_back(std::pair<int, int>(5, 6));
	for (std::pair<int, int> test_edge : test2) {
		std::cout << "(" << test_edge.first << ", " << test_edge.second << ") ";
	}
	std::cout << std::endl;
	StudentSolver::solve(test2);

	std::vector<std::pair<int, int>> test3;
	test3.push_back(std::pair<int, int>(1, 2));
	test3.push_back(std::pair<int, int>(1, 3));
	test3.push_back(std::pair<int, int>(1, 8));
	test3.push_back(std::pair<int, int>(1, 7));
	test3.push_back(std::pair<int, int>(2, 3));
	test3.push_back(std::pair<int, int>(3, 4));
	test3.push_back(std::pair<int, int>(4, 7));
	test3.push_back(std::pair<int, int>(4, 9));
	test3.push_back(std::pair<int, int>(4, 5));
	test3.push_back(std::pair<int, int>(9, 5));
	test3.push_back(std::pair<int, int>(9, 7));
	test3.push_back(std::pair<int, int>(9, 6));
	test3.push_back(std::pair<int, int>(7, 8));
	test3.push_back(std::pair<int, int>(3, 7));
	test3.push_back(std::pair<int, int>(6, 7));
	for (std::pair<int, int> test_edge : test3) {
		std::cout << "(" << test_edge.first << ", " << test_edge.second << ") ";
	}
	std::cout << std::endl;
	StudentSolver::solve(test3);
	std::vector<std::pair<int, int>> test4;
	test4.push_back(std::pair<int, int>(1, 1));
	test4.push_back(std::pair<int, int>(3, 1));
	test4.push_back(std::pair<int, int>(2, 1));
	test4.push_back(std::pair<int, int>(1, 3));
	test4.push_back(std::pair<int, int>(1, 3));
	test4.push_back(std::pair<int, int>(2, 2));
	test4.push_back(std::pair<int, int>(1, 2));
	test4.push_back(std::pair<int, int>(1, 2));
	for (std::pair<int, int> test_edge : test4) {
		std::cout << "(" << test_edge.first << ", " << test_edge.second << ") ";
	}
	std::cout << std::endl;
	StudentSolver::solve(test4);
	return 0;
}