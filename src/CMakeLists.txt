# Add the pmc sources
set(
    pmc_src
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_clique_utils.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_cores.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_driver.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_graph.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_heu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_lib.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_maxclique.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmc_utils.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmcx_maxclique.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pmcx_maxclique_basic.cpp"
)

# Pass the source list upto the main CMakeLists scope
set(
  pmc_src
  "${pmc_src}"
  PARENT_SCOPE
)
