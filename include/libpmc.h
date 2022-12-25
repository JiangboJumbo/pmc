#ifdef __cplusplus
extern "C" {
#endif

int max_clique(long long nedges, int *ei, int *ej,
                int outsize, int *clique, 
                int verbose,  // should be 0 by default
                int algorithm, // should be 0 by default 
                int offset, // should be 0 by default (defines counting offset)
                // int threads,   // will be omp_get_max_threads() by default
                //bool graph_stats=false,
                //string heuristic_strategy="kcore",
                double time_limit_secs, // should be 60*60 by default
                double remove_time_secs  // should be 4.0 by default
                //string edge_sorter = "",
                //string vertex_search_order = "deg",
                //bool decreasing_order=false
                ); 

#ifdef __cplusplus
}
#endif

