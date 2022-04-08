template <typename T>
void check_stream(T &fs) {
	while (!fs.is_open()) {
		std::cout << "Wrong path. Try again: " << std::endl;
		std::string path;
		std::cin >> path;
		fs.open("path");
	}
}

int fill_river(std::vector<std::string> &v, std::string path, size_t s) {
	std::ofstream river(path);
	
	check_stream(river);

	for (int i = 0; i < s; i++) {
		river << v[rand() % v.size()] << std::endl;
	}
	river.close();
}

int control_sum(std::string wordToFind, std::string path) {
	int sum = 0;
	std::ifstream ifs(path);
    check_stream(ifs);
    while (!ifs.eof()) {
        std::string buf;
        ifs >> buf;
		if (buf == wordToFind)
			sum++;
	}
	ifs.close();
	return sum;
}

int task3() {
    std::string addressBasket = "/home/alah/HomeWorks/ofstream/Tasks/Task3/basket.txt";
    std::string addressRiver = "/home/alah/HomeWorks/ofstream/Tasks/Task3/river.txt";
	std::ofstream basket(addressBasket,
			std::ofstream::trunc);
	basket.close(); // delete last fishing results
	std::vector<std::string> kindOfFishes = {"salmon", "tuna", "carp", "sawfish", "shark",
	"eel", "dorado", "muskie", "brown"};
	fill_river(kindOfFishes, addressRiver, 30);	//we are too lazy to do it ourself


    bool fishing = true;
    while (fishing) {
        int counter = 0;
        std::ifstream river(addressRiver);
        check_stream(river);
        std::string fishToCatch;
		std::cout << "Which kind of fish do you want to cath?" << std::endl;
		std::cin >> fishToCatch;
	    while (!river.eof()) {
		    std::string fishName;
		    river >> fishName;
		    if (fishName == fishToCatch) {
			    std::ofstream
				    basket(addressBasket,
					    	std::ios_base::app);
			    check_stream(basket);
			    basket << fishName << std::endl;
			    basket.close();
			    counter++;
			    std::cout << "You caught a " << fishToCatch << std::endl;
            }
        }
        std::cout << "You caught " << counter << " fishes during this fishing!" << std::endl;
        river.close();

        if (control_sum(fishToCatch,addressRiver) != counter) {
            std::cout << "Error, you caught an meta-fish. Matrix will be restarted" << std::endl;
            return -1;
        }

        std::cout << "Do you want to continue the fishing? [y/n]:" << std::endl;
        char ans;
        std::cin >> ans;
        fishing = ans == 'y';
    }
}
