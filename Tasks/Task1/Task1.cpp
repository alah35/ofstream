bool isValidDate(std::string s) {
    if (s[2] != '.' || s[5] != '.') {
        std::cout << "Wrong date format.";
        return false;
    }

	int day = std::stoi(s.substr(0, 2));
	if (day <= 0 || day > 31) {
		std::cout << "Wrong day number." << std::endl;
        return false;
	}

	int month = std::stoi(s.substr(3, 2));
	if (month <= 0 || month > 12) {
		std::cout << "Wrong month number." << std::endl;
		return false;
	}

	int year = std::stoi(s.substr(6, 4));
	if (year < 0) {
		std::cout << "Wrong year number." << std::endl;
	return false;
	}
	return true;
}

bool isValidSalary(std::string s) {
    if (std::stoi(s) < 0) {
        std::cout << "Wrong salary number.";
        return false;
    }
	return true;
}

void changeData(std::string &s) {
    std::cout << "Enter new value:" << std::endl;
    std::cin >> s;
}

void task1() {
	std::ofstream table("/home/alah/HomeWorks/ofstream/Tasks/Task1/table.txt");
	std::string name, surname, date, salary;
	
	int n;
	std::cout << "How many records do you want to make?" << std::endl;
	std::cin >> n;
	while (n > 0) {
        	if (!table.is_open()) {
            		std::cout << "Error. Wrong Path";
            		break;
        	}	
		std::cout << "Number " << n + 1 << ":" << std::endl;
		std::cout << "Enter the name: " << std::endl;
		std::cin >> name;
		std::cout << "Enter the surname: " << std::endl;
		std::cin >> surname;
		std::cout << "Enter the date (dd.mm.yyyy): " << std::endl;
		std::cin >> date;
		while (!isValidDate(date))
            changeData(date);
		std::cout << "Enter the salary: " << std::endl;
		std::cin >> salary;
        while(!isValidSalary(salary)) {
            changeData(salary);
        }
		table << name << " " << surname << " " << " " << date  << " " << salary << std::endl;
		n--;
	}
	table.close();
}	
