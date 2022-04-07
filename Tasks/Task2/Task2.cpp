int task2() {
	int height, width;
	std::cout << "Enter the height of the picture:" << std::endl;
	std::cin >> height;
	std::cout << "Enter the width of the picture:" << std::endl;
	std::cin >> width;
	
	while (height <= 0 || width <= 0) {
		std::cout << "Wrong sizes. Try again." << std::endl;
		std::cin >> height >> width;
	}

	std::ofstream picture("/home/alah/HomeWorks/ofstream/Tasks/Task2/picture.txt");
	if (!picture.is_open()) {
		std::cout << "Wrong path." << std::endl;
        return -1;
    }
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			picture << rand() % 2;
		}
		picture << std::endl;
	}
	picture.close();
	return 0;
}
