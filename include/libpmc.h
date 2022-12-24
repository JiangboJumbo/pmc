#ifdef __cplusplus
extern "C" {
#endif



int max_clique(long long nedges, int *ei, int *ej,
                int outsize, int *clique, 
                int index_offset=0,
                bool verbose=true, 
                int algorithm=0, 
                int threads=1,
                bool graph_stats=false,
                string heuristic_strategy="kcore",
                double time_limit_secs=60*60,
                double remove_time_secs = 4.0,
                string edge_sorter = "",
                string vertex_search_order = "deg",
                bool decreasing_order=false
                ); 

#ifdef __cplusplus
}
#endif

