tests = 3

chmod:
	chmod -R +xr .

.PHONY: all test clean
compile:
	./scripts/compile.sh

run:
	make chmod
	./scripts/run.sh ${tests}

server:
	./4-5-points/server 50124 127.0.0.1 50226

buyers:
	./4-5-points/client-buyers 127.0.0.1 50124 tests/test2.in

sellers:
	./4-5-points/client-seller 50226
