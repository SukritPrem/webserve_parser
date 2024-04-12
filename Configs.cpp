#include "Configs.hpp"

cfg::Configs::Configs(std::string const &filename) : AConfigs("configs")
{
    std::ifstream file(filename);
    if (!file.is_open()) 
        throw (std::runtime_error("Error con not open " + filename));
	
    std::string str = file.rdbuf();
    std::istringstream iss(file.rdbuf());
    AConfig *dir;

	while(!file.eof()) {
		try {
			file.peek();
			std::string directive;
			file >> directive;
			if (file.eof() && file.fail()) break;
			if (directive == "worker_processes")
				dir = new Worker_processes(file);
			else
				throw(std::runtime_error("Error: unknow directive " + directive));
			_configs.push_back(dir);
		} catch (std::exception const &e) {
			file.close();
			throw ;
		}
	}
	std::cout << "size: " << _configs.size() << std::endl;
	file.close();
}

cfg::Configs::~Configs()
{

}