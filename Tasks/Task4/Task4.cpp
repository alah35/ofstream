int check_atm(int val, const std::vector<int> &v) {
	int counter = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == val)
			counter++;
	}
	return counter;
}

bool is_possible(int sum, const std::vector<int> &vS, const int *bn) {
    if (sum % 100 != 0 && sum > 0 && sum <= 5000000)
        return false;

    for (int i = 5; i >= 0; i--) {
        if (sum >= bn[i]) {
            int numBanknotes = check_atm(bn[i], vS);
            if (numBanknotes != 0)
                sum <= numBanknotes * bn[i] ? sum %= bn[i] : sum %= numBanknotes * bn[i];
            else
                continue;
        }
    }
    return sum == 0;
}

void produce_money(const int sum, std::vector<int> &vS, const int *bn) {
    for (int i = 5; i >= 0; i--) {
        int n = sum / bn[i];
            for (int j = 0; j < vS.size() && n != 0; j++) {
                if (vS[j] == bn[i])
                    vS[j] = 0;
            }
        }
    }

int task4() {
    std::string atmAddress = "/home/alah/HomeWorks/ofstream/Tasks/Task4/atm_state.bin";
    char action = ' ';
    std::vector<int> atmState(1000);
    int banknotes[] = {100, 200, 500, 1000, 2000, 5000};
    while (action != '!') {
        std::cout << "ATM is waiting.." << std::endl;
        std::cin >> action;
        switch (action) {
            case '+': {
                std::ofstream input(atmAddress, std::ios::binary | std::ios::app);
                for (int i = 0; i < 1000; i++) {
                    atmState[i] = banknotes[rand() % 6];
                    input.write((char *) &atmState[i], sizeof(int));
                }
                input.close();
           	}
                break;
	    	case '-': {
				  std::cout << "How much money you want to withdraw?" << std::endl;
				int sum;
				std::cin >> sum;
				if (is_possible(sum, atmState, banknotes))
                    std::cout << "+++++" << std::endl;
            }
		  	break;
	    	case '!':
		 	std::cout << "ATM is closed" << std::endl;
		 	break; 
	    	default:
		 	std::cout << "Wrong command. Try again." << std::endl;
		 	break;
	    }
	}
}