all:
	$(MAKE) -C build -f Makefile

test:
	$(MAKE) -C build -f Makefile test

clean:
	$(MAKE) -C build -f Makefile clean
