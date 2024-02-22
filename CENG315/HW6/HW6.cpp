#include "the6.h"

// do not add extra libraries here


int find_structure(std::vector< std::vector<std::pair<int,int> > > &bond_energies, std::vector< std::vector<std::pair<int,int> > > &lowest_energy_structure) {
    int sizeb = bond_energies.size();
    lowest_energy_structure = std::vector< std::vector<std::pair<int,int> > >(sizeb);
    std::vector<bool> visited(sizeb, false);
    std::priority_queue< std::pair<int, std::pair<int,int> >, std::vector< std::pair<int, std::pair<int,int> > >, std::greater< std::pair<int, std::pair<int,int> > > > pq;
    
    
    visited[0] = true;
    for (auto &edge : bond_energies[0]) {
        pq.push({edge.second, {0, edge.first}});
    }
    
    
    int toten = 0;
    while (!pq.empty()) {
        auto [energy, vertices] = pq.top(); pq.pop();
        auto [u, v] = vertices;
        
        if (visited[v] == true) continue;
        
        
        else{
            visited[v] = true;
            toten += energy;
            lowest_energy_structure[u].push_back({v, energy});
            lowest_energy_structure[v].push_back({u, energy});
            
            for (auto &edge : bond_energies[v]) {
                if (!visited[edge.first]) {
                    pq.push({edge.second, {v, edge.first}});
                }
            }
        }
    }
    
    return toten;
}



int find_longest_chain(std::vector<std::vector<std::pair<int, int>>>& molecule_structure, std::vector<int>& chain) {
    int longsiz = 0;
    int verticies = molecule_structure.size();
    std::vector<std::vector<int>> adjacency_list(verticies);

    for (int i = 0; i < verticies; i++) {
        for (size_t j = 0; j < molecule_structure[i].size(); ++j) {
            int neighbor = molecule_structure[i][j].first;
            adjacency_list[i].push_back(neighbor);
        }
    }

    for (int start_vertex = 0; start_vertex < verticies; start_vertex++) {
        std::vector<int> distance(verticies, -1);
        std::vector<int> parent(verticies, -1);
        std::vector<bool> visited(verticies, false);

        std::vector<int> q;
        q.push_back(start_vertex);
        visited[start_vertex] = 1;
        distance[start_vertex] = 0;

        int farthest_vertex = start_vertex;
        for (size_t idx = 0; idx < q.size(); ++idx) {
            int current = q[idx];
    
    
    
            for (size_t i = 0; i < adjacency_list[current].size(); ++i) {
                int neighbor = adjacency_list[current][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push_back(neighbor);
                    distance[neighbor] = distance[current] + 1;
                    parent[neighbor] = current;

                    if (distance[neighbor] > distance[farthest_vertex]) {
                        farthest_vertex = neighbor;
                    }
                    
                }
            }
        }
        if (distance[farthest_vertex] > longsiz) {
            longsiz = distance[farthest_vertex];
            chain.clear();
            int current_vertex = farthest_vertex;
            while (current_vertex != -1) {
                chain.push_back(current_vertex);
                current_vertex = parent[current_vertex];
            }
            
            
            std::reverse(chain.begin(), chain.end());
        }
    }

    return longsiz + 1; 
}
