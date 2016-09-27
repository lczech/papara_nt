#!/bin/sh

mpic++ -o papara_mpi -O3 -D__MPI -msse4a -std=c++11 -I. -I ivy_mike/src/ -I ublasJama-1.0.2.3 papara.cpp pvec.cpp pars_align_seq.cpp pars_align_gapp_seq.cpp parsimony.cpp sequence_model.cpp papara2_main.cpp blast_partassign.cpp align_utils.cpp ivy_mike/src/time.cpp ivy_mike/src/tree_parser.cpp ivy_mike/src/getopt.cpp ivy_mike/src/demangle.cpp ivy_mike/src/multiple_alignment.cpp ublasJama-1.0.2.3/EigenvalueDecomposition.cpp -lpthread
