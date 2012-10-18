cpcpp
=====

cp's c++ stuff

Requirements
============

* Boost (boost::thread and boost::system, required by boost::thread)

Running the tests
=================

    make check

or, if you're feeling frisky

    make test

They'll both do the same thing.  You'll need to have a `GTEST_DIR`
environment variable set.  The Makefile will assume that `GTEST_DIR/include`
has the header files and that the static libraries live (for whatever reason)
directly in `GTEST_DIR`. (Surely this isn't the best way to deploy gtest?)
