build:
	g++ -g -fsanitize=address main.cpp app_manager.cpp console_manager.cpp line.cpp symbol.cpp random_engine.cpp validator.cpp explosion.cpp figure.cpp utils.cpp -o solution.out
run:
	./solution.out
brun:
	make build
	make run
rargs:
	make build
	./solution.out 1 10 30 n 10 1 3
destroy:
	rm ./solution.out
help:
	./solution.out --help