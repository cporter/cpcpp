
all:

doc docs:
	doxygen Doxyfile


.PHONY: test

check test:
	cd test ; $(MAKE)

clean:
	cd test ; $(MAKE) clean
