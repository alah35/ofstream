void check_atm() {
    std::ifstream showing("/home/alah/HomeWorks/ofstream/Tasks/Task4/atm_state.bin", std::ios_base::binary);
    int number;
    for (int i = 0; i < 1000; i++) {
        showing.read((char *) &number, sizeof(int));
        std::cout << number << std::endl;
    }
    showing.close();
}

int amount_banknotes(int val, const std::vector<int> &v) {
	int counter = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == val)
			counter++;
	}
	return counter;
}

bool is_possible(int sum, const std::vector<int> &vS, const int *bn) {
    if (sum <= 0 || sum % 100 != 0 || sum > 5000000)
        return false;

    for (int i = 5; i >= 0; i--) {
        if (sum >= bn[i]) {
            int numBanknotes = amount_banknotes(bn[i], vS);
            if (numBanknotes != 0)
                sum <= numBanknotes * bn[i] ? sum %= bn[i] : sum -= numBanknotes * bn[i];
            else
                continue;
        }
    }
    return sum == 0;
}

void produce_money(std::string path, int sum, std::vector<int> &vS, const int *bn) {
    for (int i = 5; i >= 0; i--) {
        int n = sum / bn[i], buf;
        sum %= bn[i];
        for (int j = 0; j < vS.size() && n != 0; j++) {
            if (vS[j] == bn[i]) {
                vS[j] = 0;
                n--;
            }
        }
    }
    std::ofstream producing(path, std::ios_base::binary);
    for (int i = 0; i < vS.size(); i++) {
        producing.write((char *) &vS[i], sizeof(int));
    }
    producing.close();
    std::cout << "The money was produced." << std::endl;
}

void fill_atm(std::string path, std::vector<int> &vS, const int *bn) {
	std::ofstream filling(path, std::ios_base::binary);
	for (int i = 0; i < vS.size(); i++) {
		if (vS[i] == 0) {
			vS[i] = bn[rand() % 6];
			filling.write((char*) &vS[i], sizeof(int));
		} else
			filling.seekp(sizeof(int));
	}
    filling.close();
}

int task4() {
    std::string atmAddress = "/home/alah/HomeWorks/ofstream/Tasks/Task4/atm_state.bin";
    char action = ' ';
    std::vector<int> atmState(1000, 0);
    const int banknotes[] = {100, 200, 500, 1000, 2000, 5000};
    while (action != '!') {
        std::cout << "ATM is waiting.." << std::endl;
        std::cin >> action;
        switch (action) {
            case '+': {
                fill_atm(atmAddress, atmState, banknotes);
                break;
                case '-': {
                    std::cout << "How much money you want to withdraw?" << std::endl;
                    int sum;
                    std::cin >> sum;
                    if (is_possible(sum, atmState, banknotes)) {
                        produce_money(atmAddress, sum, atmState, banknotes);
                        check_atm();
                    }
                    else
                        std::cout << "Unable to withdraw this amount" << std::endl;
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
}