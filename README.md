PaPaRa 2.0 with MPI
===================

Implementation of the PaPaRa 2.0 algorithm, with rudimental MPI support. See
http://sco.h-its.org/exelixis/web/software/papara/index.html
for details.

Basic Instructions
------------------

Build with `sh build_papara2.sh` which will produce the executable `papara`,
or with `sh build_papara2_mpi.sh` which will produce the executable `papara_mpi`, if you want
MPI support.
To be able to compile the sources you need a resonably recent version of the boost (www.boost.org)
libraries.

Invoke PaPaRa using

    ./papara -t <ref tree> -s <phylip RA> -q <fasta QS>

The phylip file (option `-s <phylip RA>`) must contain the reference alignment, consistent with the
reference tree (option `-t <ref tree>`). The FASTA file (option `-q <fasta QS>`) contains the
unaligned QS. Optionally, all sequences which are in `<phylip RA>` but do not occur in the
`<ref tree>` are also interpreted as QS.

The alignment parameters can be modified using the (optional) option `-p <user options>`.
`<user options>` is a string and must have the following form:
`<gap_open>:<gap_extend>:<mismatch>:<match_cgap>`, so the default parameters used given in the paper
correspond to the user option `-p -3:-1:2:-3`.

The output alignment will be written to `papara_alignment.default`; you can change the file suffix
"default" by supplying a run-name with parameter `-n`.
You can invoke the multi threaded version by adding the option `-j <num threads>`.

MPI Support
-----------

This version is intended for cluster usage if you want to align multiple files of roughly the same
size at the same time. It is ideal for equally sized chunks of bigger alignments.

The MPI version is invoked using

    mpirun -n T ./papara_mpi -t <ref tree> -s <phylip RA> -q <fasta QS 1>[,<fasta QS 2>...]

where `T` is the number of MPI nodes to run on. Note that each node can still use multiple threads,
so you can combine this with the `-j` option.

The fasta query files need to be separated by commas, without whitespaces. This means that your
filenames cannot contain commas. If you specify fewer files than MPI nodes, the surplus nodes
will do nothing.
**Caveat:** If you however have more files than nodes, the surplus files will not be processed!
This will hopefully change in the future - right now, this is a crude first MPI version of PaPaRa.
Also be aware that the output of all nodes is mashed up, thus usually unreadable. Use the log
files to see what each node outputs.
