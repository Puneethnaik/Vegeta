install: clean 
	bash ./build-script.sh

clean:
	@echo "Cleaning the bin directory"
	rm -rf ./bin/prod/*
	rm -rf ./bin/test/*

test: build_test_files
	@echo "Testing files one by one..."


build_test_files: clean
	@echo "compiling test files in /test/ directory"
	

