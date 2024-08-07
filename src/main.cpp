#include <iostream>
#include <filesystem>
#include <ostream>

#include "compiler.hpp"

namespace fs = std::filesystem;

static int parse(char* argv[], int argc) {
	if (*argv[1] == *"new") {
		if (argv[2] == NULL) {
			std::cout << "You need to define the name of the project" << std::endl;
			return 1;
		}

		std::ifstream check_file;

		check_file.open("Allan.toml");
		if (check_file.good()) {
			std::cout << "Already created a project" << std::endl;
			return 1;
		} else {

			std::ofstream allan("Allan.toml");

			allan << "[package]" << std::endl
				<< "name = " << '"' << argv[2] << '"' << std::endl;

			allan.close();

			fs::create_directory("bin");
			fs::create_directory("build");
			fs::create_directory("includes");
			fs::create_directory("src");

			std::ofstream main_file("src/main.cpp");

			main_file << "#include <iostream>" << std::endl << std::endl
				<< "int main() {" << std::endl
				<< "	std::cout << " << '"' << "Hello, World!" << '"' << " << std::endl;" << std::endl // This is the weird piece of code I have written
				<< "}" << std::endl;

			main_file.close();
		}
	}

	if (*argv[1] == *"build") {
		Builder builder = Builder();
		builder.build();
	}

	return 0; 
}

int main(int argc, char* argv[]) {
	// This is just an if statement. I just saw that switch statements are faster
	switch (argc)
	{
	case 1:
		std::cout << "Welcome to the c++ package Manager. These are the following commands" << std::endl << std::endl;
		std::cout << "- new `name`(Creates a new project in the current dir)" << std::endl;
		std::cout << "- build(Builds a project)" << std::endl;
		std::cout << "- run(Builds and runs a project" << std::endl;
		return 0;
		break;
	
	default:
		return parse(argv, argc);
		break; 
	}
}