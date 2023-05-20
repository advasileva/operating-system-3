tests = 3

chmod:
	chmod -R +xr .

.PHONY: all test clean
compile:
	./scripts/compile.sh

run:
	make chmod
	./scripts/run.sh ${tests}
