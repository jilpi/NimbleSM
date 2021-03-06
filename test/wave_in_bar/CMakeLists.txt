
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.in
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.in COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.g
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.g COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.g.3.0
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.g.3.0 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.g.3.1
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.g.3.1 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.g.3.2
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.g.3.2 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.gold.e
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.gold.e COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.exodiff
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.exodiff COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/PostProcess.py
               ${CMAKE_CURRENT_BINARY_DIR}/PostProcess.py COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/analytic_solution.py
               ${CMAKE_CURRENT_BINARY_DIR}/analytic_solution.py COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/analytic_solution_free_end.txt
               ${CMAKE_CURRENT_BINARY_DIR}/analytic_solution_free_end.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/analytic_solution_midpoint.txt
               ${CMAKE_CURRENT_BINARY_DIR}/analytic_solution_midpoint.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wave_in_bar.gnuplot
               ${CMAKE_CURRENT_BINARY_DIR}/wave_in_bar.gnuplot COPYONLY)

add_test(wave_in_bar_serial python ../run_exodiff_test.py --executable "${NimbleSM_Serial}" --input-deck wave_in_bar.in)

if(NIMBLE_HAVE_DARMA)
  add_test(wave_in_bar_darma_np1 python ../run_exodiff_test.py --executable "${NimbleSM_Darma}" --input-deck wave_in_bar.in --num-ranks 1 --num-virtual-ranks 1 --charm-run ${charmrun})
  add_test(wave_in_bar_darma_np3 python ../run_exodiff_test.py --executable "${NimbleSM_Darma}" --input-deck wave_in_bar.in --num-ranks 2 --num-virtual-ranks 3 --charm-run ${charmrun})
endif()

if(NIMBLE_HAVE_MPI)
  add_test(wave_in_bar_mpi_np1 python ../run_exodiff_test.py --executable "${NimbleSM_MPI}" --input-deck wave_in_bar.in --num-ranks 1)
  add_test(wave_in_bar_mpi_np3 python ../run_exodiff_test.py --executable "${NimbleSM_MPI}" --input-deck wave_in_bar.in --num-ranks 3)
endif()

if(NIMBLE_HAVE_KOKKOS)
  add_test(wave_in_bar_kokkos_np1 python ../run_exodiff_test.py --executable "${NimbleSM_Kokkos}" --input-deck wave_in_bar.in --num-ranks 1)
  add_test(wave_in_bar_kokkos_np3 python ../run_exodiff_test.py --executable "${NimbleSM_Kokkos}" --input-deck wave_in_bar.in --num-ranks 3)
endif()

if(NIMBLE_HAVE_TRILINOS)
  add_test(wave_in_bar_tpetra_np1 python ../run_exodiff_test.py --executable "${NimbleSM_Tpetra}" --input-deck wave_in_bar.in --num-ranks 1)
  add_test(wave_in_bar_tpetra_np3 python ../run_exodiff_test.py --executable "${NimbleSM_Tpetra}" --input-deck wave_in_bar.in --num-ranks 3)
endif()

if(NIMBLE_HAVE_QTHREADS)
  add_test(wave_in_bar_qthreads_np1_ns1_nwps1 python ../run_exodiff_test.py --executable "${NimbleSM_Qthreads}" --input-deck wave_in_bar.in --num-ranks 1 --qthreads-num-shepherds 1 --qthreads-num-workers-per-shepherd 1)
  add_test(wave_in_bar_qthreads_np3_ns1_nwps1 python ../run_exodiff_test.py --executable "${NimbleSM_Qthreads}" --input-deck wave_in_bar.in --num-ranks 3 --qthreads-num-shepherds 1 --qthreads-num-workers-per-shepherd 1)
endif()
