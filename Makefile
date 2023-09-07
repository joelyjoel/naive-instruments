# These are just shortcuts, please use cmake for a compatible build

default:
	cmake -S . -B build
	cmake --build build

test: 
	cmake -S . -B build
	cmake --build build && bin/test_naive
	bash ./tests/run-all.sh
