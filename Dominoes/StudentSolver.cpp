#include "StudentSolver.h"
#include <iostream>

void remove_duplicate(int num, std::vector<int>& list) {
	for (int i = 0; i < list.size() - 1; ++i) {
		if (list[i] == num) {
			list.erase(list.begin() + i);
			list.pop_back();
			break;
		}
	}
}

void create_graph_and_count(std::vector<std::pair<int, int>>& edges, std::map<int, std::vector<std::pair<int, int>*>>& vertices, std::vector<int>& keys, std::vector<int>& odd_num) {
	for (std::pair<int, int>& edge : edges) {
		for (int i = 0; i < 2; i++) {
			int num_in_pair = (i == 0) ? edge.first : edge.second;
			if (vertices.find(num_in_pair) == vertices.end()) {
				vertices[num_in_pair] = std::vector<std::pair<int, int>*>{ &edge };
				keys.push_back(num_in_pair);
				odd_num.push_back(num_in_pair);
			}
			else {
				vertices[num_in_pair].push_back(&edge);
				odd_num.push_back(num_in_pair);
				remove_duplicate(num_in_pair, odd_num);
			}
			if (edge.second == edge.first) {
				odd_num.push_back(num_in_pair);
				remove_duplicate(num_in_pair, odd_num);
				break;
			}
			else continue;
		}
	}
}

void find_cycles(std::vector<std::pair<int, int>>& edges, std::vector<std::vector<std::pair<int, int>>>& cycle_collection, std::map<int, std::vector<std::pair<int, int>*>>& vertices, std::vector<int>& vertex_keys, std::vector<int>& odd_num_vertex) {
	std::vector<int> discovered_vertex;
	std::vector<std::pair<int, int>> temp_cycle, found_cycle;
	int second_in_discovered;
	if (odd_num_vertex.size() == 2) {
		bool found_shortest_path = false;
		for (std::pair<int, int>& edge : edges) {
			if (edge == std::pair<int, int>(odd_num_vertex[0], odd_num_vertex[1]) || edge == std::pair<int, int>(odd_num_vertex[1], odd_num_vertex[0])) {
				cycle_collection.push_back(std::vector<std::pair<int, int>>{edge});
				edge = std::pair<int, int>(-1, -1);
				found_shortest_path = true;
				break;
			}
			else continue;
		}
		if (!found_shortest_path) {
			std::vector<std::pair<int, int>*> curr_vertex;
			std::pair<int, int>* curr_ptr;
			while (!found_shortest_path) {
				int second_int;
				int curr_key = odd_num_vertex[0];
				curr_vertex = vertices[curr_key];
				int ptr_idx = 0;
				bool all_visited = false;
				while (!all_visited && !found_shortest_path) {
					curr_ptr = curr_vertex[ptr_idx];
					while (*curr_ptr == std::pair<int, int>(-1, -1) || (*curr_ptr).first == (*curr_ptr).second) {
						if (++ptr_idx == curr_vertex.size()) {
							all_visited = true;
							break;
						}
						else {
							if ((*curr_ptr).first == (*curr_ptr).second && *curr_ptr != std::pair<int, int>(-1, -1)) {
								cycle_collection.push_back(std::vector<std::pair<int, int>>{*curr_ptr});
								*curr_ptr = std::pair<int, int>(-1, -1);
							}
							curr_ptr = curr_vertex[ptr_idx];
							continue;
						}
					}
					if (all_visited) {
						break;
					}
					else {
						if ((*curr_ptr).first != curr_key) (*curr_ptr) = std::pair<int, int>((*curr_ptr).second, (*curr_ptr).first);
						discovered_vertex.push_back((*curr_ptr).first);
						temp_cycle.push_back(*curr_ptr);
						int second_int = (*curr_ptr).second;
						*curr_ptr = std::pair<int, int>(-1, -1);
						second_in_discovered = -1;
						if (second_int != odd_num_vertex[1]) {
							for (int i = 0; i < discovered_vertex.size(); ++i) {
								if (second_int == discovered_vertex[i]) {
									second_in_discovered = i;
									break;
								}
								else continue;
							}
						}
						else {
							second_in_discovered = 0;
							found_shortest_path = true;
						}
						if (second_in_discovered != -1) {
							if (second_in_discovered == 0) {
								if (found_shortest_path) {
									cycle_collection.insert(cycle_collection.begin(), temp_cycle);
								}
								else {
									cycle_collection.push_back(temp_cycle);
								}
								temp_cycle.clear();
								discovered_vertex.clear();
								curr_key = odd_num_vertex[0];
							}
							else {
								found_cycle = std::vector<std::pair<int, int>>(temp_cycle.begin() + second_in_discovered, temp_cycle.end());
								for (int i = 0; i < found_cycle.size(); ++i) {
									temp_cycle.pop_back();
									discovered_vertex.pop_back();
								}
								cycle_collection.push_back(found_cycle);
								found_cycle.clear();
								curr_key = temp_cycle[temp_cycle.size() - 1].second;
							}
							ptr_idx = 0;
							curr_vertex = vertices[curr_key];
							curr_ptr = curr_vertex[ptr_idx];
						}
						else {
							ptr_idx = 0;
							curr_key = second_int;
							curr_vertex = vertices[second_int];
						}
					}
				}
			}
		}
	}
	else if (odd_num_vertex.size() > 2) {
		return;
	}
	for (int key : vertex_keys) {
		int curr_key = key;
		std::vector<std::pair<int, int>*> curr_vertex = vertices[curr_key];
		std::pair<int, int>* curr_ptr;
		int ptr_idx = 0;
		bool all_visited = false;
		while (!all_visited) {
			curr_ptr = curr_vertex[ptr_idx];
			while (*curr_ptr == std::pair<int, int>(-1, -1) || (*curr_ptr).first == (*curr_ptr).second) {
				if (++ptr_idx == curr_vertex.size()) {
					all_visited = true;
					break;
				}
				else {
					if ((*curr_ptr).first == (*curr_ptr).second && *curr_ptr != std::pair<int, int>(-1, -1)) {
						cycle_collection.push_back(std::vector<std::pair<int, int>>{*curr_ptr});
						*curr_ptr = std::pair<int, int>(-1, -1);
					}
					curr_ptr = curr_vertex[ptr_idx];
					continue;
				}
			}
			if (all_visited) {
				break;
			}
			else {
				if ((*curr_ptr).first != curr_key) (*curr_ptr) = std::pair<int, int>((*curr_ptr).second, (*curr_ptr).first);
				discovered_vertex.push_back((*curr_ptr).first);
				temp_cycle.push_back(*curr_ptr);
				int second_int = (*curr_ptr).second;
				*curr_ptr = std::pair<int, int>(-1, -1);
				second_in_discovered = -1;
				for (int i = 0; i < discovered_vertex.size(); ++i) {
					if (second_int == discovered_vertex[i]) {
						second_in_discovered = i;
						break;
					}
					else continue;
				}
				if (second_in_discovered != -1) {
					if (second_in_discovered == 0) {
						cycle_collection.push_back(temp_cycle);
						temp_cycle.clear();
						discovered_vertex.clear();
						curr_key = key;
					}
					else {
						found_cycle = std::vector<std::pair<int, int>>(temp_cycle.begin() + second_in_discovered, temp_cycle.end());
						for (int i = 0; i < found_cycle.size(); ++i) {
							temp_cycle.pop_back();
							discovered_vertex.pop_back();
						}
						cycle_collection.push_back(found_cycle);
						found_cycle.clear();
						curr_key = temp_cycle[temp_cycle.size() - 1].second;
					}
					ptr_idx = 0;
					curr_vertex = vertices[curr_key];
					curr_ptr = curr_vertex[ptr_idx];
				}
				else {
					ptr_idx = 0;
					curr_key = second_int;
					curr_vertex = vertices[second_int];
				}
			}
		}
	}
}

void find_euler_cycle(std::vector<std::vector<std::pair<int, int>>>& cycle_collection, std::vector<std::pair<int, int>>& cycle, std::vector<std::pair<int, int>>& euler_cycle, std::vector<int>& visited_cycle, int edge_idx_in_cycle) {
	for (int i = 0; i < cycle.size(); ++i) {
		for (int collection_iter = 0; collection_iter < cycle_collection.size(); ++collection_iter) {
			if (visited_cycle.size() == cycle_collection.size()) {
				break;
			}
			else {
				bool visited_flag = false;
				for (int visited : visited_cycle) {
					if (visited == collection_iter) {
						visited_flag = true;
						break;
					}
				}
				if (visited_flag) {
					continue;
				}
				else {
					for (int cycle_iter = 0; cycle_iter < cycle_collection[collection_iter].size(); ++cycle_iter) {
						if (cycle_collection[collection_iter][cycle_iter].first == cycle[edge_idx_in_cycle].first) {
							visited_cycle.push_back(collection_iter);
							find_euler_cycle(cycle_collection, cycle_collection[collection_iter], euler_cycle, visited_cycle, cycle_iter);
							break;
						}
					}
				}
			}
		}
		euler_cycle.push_back(cycle[edge_idx_in_cycle++]);
		if (edge_idx_in_cycle == cycle.size()) {
			edge_idx_in_cycle -= cycle.size();
		}
	}
}

std::vector<std::pair<int, int>> StudentSolver::solve(std::vector<std::pair<int, int>> edges) {
	std::map<int, std::vector<std::pair<int, int>*>> vertices;
	std::vector<int> vertex_keys;
	std::vector<int> odd_num_vertex;
	create_graph_and_count(edges, vertices, vertex_keys, odd_num_vertex);
	std::vector<std::vector<std::pair<int, int>>> cycle_collection;
	if (odd_num_vertex.size() > 2) { return std::vector<std::pair<int, int>>{}; }
	else { find_cycles(edges, cycle_collection, vertices, vertex_keys, odd_num_vertex); }

	// Now we have the cycle collection, begin euler path
	std::vector<std::pair<int, int>> euler_cycle;
	std::vector<int> visited_cycle;
	visited_cycle.push_back(0);
	int edge_idx_in_cycle = 0;
	find_euler_cycle(cycle_collection, cycle_collection[0], euler_cycle, visited_cycle, 0);
	return euler_cycle;
}