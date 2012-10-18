
CXXFLAGS=-I$(GTEST_DIR)/include
LDFLAGS=-L$(GTEST_DIR)
LDLIBS=-lgtest -lgtest_main -lboost_thread-mt -lboost_system-mt

TESTS = cq_test

check test: $(TESTS)
	@./runall.sh $(TESTS)

clean:
	rm -f *.o $(TESTS)
