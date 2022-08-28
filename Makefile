# These are just shortcuts, please use cmake for a compatible build

default:
	cd build && make

test: 
	cd build && make test_naive && test_naive
	cd build && make naive && cd ../ && ./run-tests.sh
