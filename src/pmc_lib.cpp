/**
 ============================================================================
 Name        : Parallel Maximum Clique (PMC) Library
 Author      : Ryan A. Rossi   (rrossi@purdue.edu)
 Description : A general high-performance parallel framework for computing
               maximum cliques. The library is designed to be fast for large
               sparse graphs.

 Copyright (C) 2012-2013, Ryan A. Rossi, All rights reserved.

 Please cite the following paper if used:
   Ryan A. Rossi, David F. Gleich, Assefaw H. Gebremedhin, Md. Mostofa
   Patwary, A Fast Parallel Maximum Clique Algorithm for Large Sparse Graphs
   and Temporal Strong Components, arXiv preprint 1302.6256, 2013.

 See http://ryanrossi.com/pmc for more information.
 ============================================================================
 */

#include "pmc.h"

using namespace std;
using namespace pmc;

extern "C" {

    
// a list of edges, where index_offset is the starting index
int max_clique(long long nedges, int *ei, int *ej,
                int outsize, int *clique, 
                int verbose, 
                int algorithm, 
                int offset,
                // int threads,
                // bool graph_stats,
                // string heuristic_strategy,
                double time_limit_secs,
                double remove_time_secs
                // string edge_sorter,
                // string vertex_search_order,
                // bool decreasing_order
                ) 
{

    input in;
    in.algorithm = algorithm;
    in.threads = omp_get_max_threads(); // evaluates to 1 when _OPENMP is not defined
    in.graph_stats = false; //graph_stats;
    in.lb = 0;
    in.ub = 0;
    in.heu_strat = "kcore"; //heuristic_strategy;
    in.verbose = verbose > 0;
    in.time_limit = time_limit_secs;
    in.remove_time = remove_time_secs;
    in.edge_sorter = ""; // edge_sorter;
    in.vertex_search_order = "deg"; // vertex_search_order;
    in.decreasing_order = false; // decreasing_order;

    if (in.heu_strat == "0" && in.algorithm == -1){
        in.algorithm = 0;
    }

    if (in.threads <= 0) in.threads = 1;

    // std::cout << "threads num: " << in.threads << "\n";

    pmc_graph G(nedges, ei, ej, offset); 
    
    //! ensure wait time is greater than the time to recompute the graph data structures
    if (G.num_edges() > 1000000000 && in.remove_time < 120)  in.remove_time = 120;
    else if (G.num_edges() > 250000000 && in.remove_time < 10) in.remove_time = 10;
    if (verbose) {
        cout << "explicit reduce is set to " << in.remove_time << " seconds" <<endl;
    }

    double seconds = get_time();
    G.compute_cores();
    if (in.ub == 0) {
        in.ub = G.get_max_core() + 1;
        if (verbose){
        cout << "K: " << in.ub <<endl;
        cout << "k-cores time: " << get_time() - seconds << ", ub: " << in.ub << endl;
        }
    }
    
    //! lower-bound of max clique
    vector<int> C;
    if (in.lb == 0 && in.heu_strat != "0") { // skip if given as input
        pmc_heu maxclique(G,in);
        in.lb = maxclique.search(G, C);
        if (verbose) {
        cout << "Heuristic found clique of size " << in.lb;
        cout << " in " << get_time() - seconds << " seconds" <<endl;
        cout << "[pmc: heuristic]  ";
        print_max_clique(C);
        }
    }

    //! check solution found by heuristic
    if (in.lb == in.ub && !in.MCE) {
        if (verbose){
          cout << "Heuristic found optimal solution." << endl;
        }
    }
    else if (in.algorithm >= 0) {
        switch(in.algorithm) {
            case 0: {
                //! k-core pruning, neigh-core pruning/ordering, dynamic coloring bounds/sort
                if (G.num_vertices() < in.adj_limit) {
                    G.create_adj();
                    pmcx_maxclique finder(G,in);
                    finder.search_dense(G,C);
                    break;
                }
                else {
                    pmcx_maxclique finder(G,in);
                    finder.search(G,C);
                    break;
                }
            }
            case 1: {
                //! k-core pruning, dynamic coloring bounds/sort
                if (G.num_vertices() < in.adj_limit) {
                    G.create_adj();
                    pmcx_maxclique_basic finder(G,in);
                    finder.search_dense(G,C);
                    break;
                }
                else {
                    pmcx_maxclique_basic finder(G,in);
                    finder.search(G,C);
                    break;
                }
            }
            case 2: {
                //! simple k-core pruning (four new pruning steps)
                pmc_maxclique finder(G,in);
                finder.search(G,C);
                break;
            }
            default:
                if (verbose){
                cout << "algorithm " << in.algorithm << " not found." <<endl;
                }
                break;
        }
        if (verbose){
          seconds = (get_time() - seconds);
          cout << "Time taken: " << seconds << " SEC" << endl;
          cout << "Size (omega): " << C.size() << endl;
          print_max_clique(C);
        }
    }
    
    // save the output
    for(int i = 0; i < C.size() && i < outsize; i++)
        clique[i] = C[i] + offset;

    return C.size();
    return 0;
}

};
