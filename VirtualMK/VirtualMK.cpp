#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <cstdlib>

std::map<std::string, int> instructionSet = {
	{"HLT", 0},
	{"PSH", 1},
	{"POP", 2},
	{"ADD", 3},
	{"SUB", 4},
	{"MUL", 5},
	{"DIV", 6},
	{"POW", 7},
	{"SQR", 8},
	{"LOG", 9},
	{"LON", 10},
	{"EXP", 11},
	{"MOV", 12},
	{"SET", 13},
	{"PRT", 14},
	{"NOP", 15}
};

std::map<std::string, int> registerSet = {
	{"S", 0},
	{"A", 1},
	{"B", 2},
	{"C", 3},
	{"D", 4},
	{"E", 5},
	{"F", 6}
};

std::vector<std::string> code;
std::vector<double> stack;
std::vector<double> registers(registerSet.size(), 0);

std::vector<std::string>::iterator instructionPointer;

auto isRunning = true;
auto commandCount = 0;

template<typename T>
constexpr void printVector(std::vector<T>& vec) noexcept {
	if (!vec.empty()) {
		for (auto e : vec) {
			std::cout << e << " ";
		}
	}
	else {
		std::cout << "empty";
	}
	std::cout << std::endl;
}

template<typename T>
constexpr void reversePrintVector(std::vector<T>& vec) noexcept {
	if (!vec.empty()) {
		for (auto e = vec.rbegin(); e != vec.rend(); ++e) {
			std::cout << *e << " ";
		}
	}
	else {
		std::cout << "empty";
	}
	std::cout << std::endl;
}

void printRegisters() noexcept {
	char c = 64;
	std::cout << "Registers: ";
	for (auto e = registers.begin() + 1; e != registers.end(); ++e) {
		++c;
		std::cout << c << " = " << *e << "  ";
	}
	std::cout << std::endl;
}

void execution() noexcept {
	isRunning = false;
	std::cout << std::endl << "Finished execution \n \n" << "Stack: ";
	reversePrintVector(stack);
	printRegisters();
	std::cout << std::endl;
	exit(0);
}

std::vector<std::string>::iterator pointerIncrement(std::vector<std::string>::iterator& it) noexcept {
	if (commandCount == 0) {
		return it;
	}
	else if (it + 1 == code.end()) {
		std::cout << ++commandCount << " | error: not enough instructions" << std::endl;
		execution();
	}
	return ++it;
}

int getInstruction(std::vector<std::string>::iterator& ip) noexcept {
	pointerIncrement(ip);
	++commandCount;
	if (instructionSet.find(*ip) == instructionSet.end()) {
		std::cout << commandCount << " | error: instruction unknown: " << *ip << std::endl;
		execution();
	}
	return instructionSet[*ip];
}

int getRegister(std::vector<std::string>::iterator& ip) noexcept {
	pointerIncrement(ip);
	++commandCount;
	if (registerSet.find(*ip) == registerSet.end()) {
		std::cout << commandCount << " | error: register unknown: " << *ip << std::endl;
		execution();
	}
	return registerSet[*ip];
}

double getNumber(std::vector<std::string>::iterator& ip) noexcept {
	pointerIncrement(ip);
	++commandCount;
	try {
		return std::stod(*ip);
	}
	catch (...) {
		std::cout << commandCount << " | error: number incorrect : " << *ip << std::endl;
		execution();
		return -1;
	}
}

void operations(std::vector<std::string>::iterator& ip) noexcept {
	int regFirst, regSecond, regTarget;
	switch (getInstruction(ip)) {
	case 0: //HLT
		execution();
		break;

	case 1: //PSH
		stack.emplace_back(getNumber(ip));
		break;

	case 2: //POP
		if (!stack.empty()) {
			std::cout << "popped value: " << stack.back() << std::endl;
			stack.pop_back();
		}
		else {
			std::cout << commandCount << " | error: could not pop value, stack is empty " << std::endl;
		}
		break;

	case 3: //ADD
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (stack.size() >= 2) {
				registers[0] = stack.back();
				stack.pop_back();
				stack.back() = registers[0] + stack.back();
			}
			else {
				std::cout << commandCount << " | error: stack has not enough values" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			if (regFirst != regSecond) {
				switch (regSecond) {
				case 0:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;

				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					regTarget = getRegister(ip);
					switch (regTarget) {
					case 0:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;

					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						registers[regTarget] = registers[regFirst] + registers[regSecond];
						break;

					default:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;
					}
					break;

				default:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;
				}
			}
			else {
				std::cout << commandCount << " | error: register is incorrect" << std::endl;
				execution();
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 4: //SUB
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (stack.size() >= 2) {
				registers[0] = stack.back();
				stack.pop_back();
				stack.back() = registers[0] - stack.back();
			}
			else {
				std::cout << commandCount << " | error: stack has not enough values" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			if (regFirst != regSecond) {
				switch (regSecond) {
				case 0:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;

				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					regTarget = getRegister(ip);
					switch (regTarget) {
					case 0:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;

					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						registers[regTarget] = registers[regFirst] - registers[regSecond];
						break;

					default:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;
					}
					break;

				default:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;
				}
			}
			else {
				std::cout << commandCount << " | error: register is incorrect" << std::endl;
				execution();
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 5: //MUL
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (stack.size() >= 2) {
				registers[0] = stack.back();
				stack.pop_back();
				stack.back() = registers[0] * stack.back();
			}
			else {
				std::cout << commandCount << " | error: stack has not enough values" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			if (regFirst != regSecond) {
				switch (regSecond) {
				case 0:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;

				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					regTarget = getRegister(ip);
					switch (regTarget) {
					case 0:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;

					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						registers[regTarget] = registers[regFirst] * registers[regSecond];
						break;

					default:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;
					}
					break;

				default:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;
				}
			}
			else {
				std::cout << commandCount << " | error: register is incorrect" << std::endl;
				execution();
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 6: //DIV
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (stack.size() >= 2) {
				if (*(stack.end() - 1) != 0 && *(stack.end() - 2) != 0) {
					registers[0] = stack.back();
					stack.pop_back();
					stack.back() = registers[0] / stack.back();
				}
				else {
					std::cout << commandCount << " | error: could not be divide by zero" << std::endl;
				}
			}
			else {
				std::cout << commandCount << " | error: stack has not enough values" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			if (registers[regFirst] != 0 && registers[regSecond] != 0) {
				if (regFirst != regSecond) {
					switch (regSecond) {
					case 0:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;

					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						regTarget = getRegister(ip);
						switch (regTarget) {
						case 0:
							std::cout << commandCount << " | error: register is incorrect" << std::endl;
							execution();
							break;

						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
						case 6:
							registers[regTarget] = registers[regFirst] / registers[regSecond];
							break;

						default:
							std::cout << commandCount << " | error: register is incorrect" << std::endl;
							execution();
							break;
						}
						break;

					default:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;
					}
				}
				else {
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
				}
			}
			else {
				std::cout << commandCount << " | error: could not be divide by zero" << std::endl;
				getRegister(ip);
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 7: //POW
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (stack.size() >= 2) {
				registers[0] = stack.back();
				stack.pop_back();
				stack.back() = std::pow(registers[0], stack.back());
			}
			else {
				std::cout << commandCount << " | error: stack has not enough values" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			if (regFirst != regSecond) {
				switch (regSecond) {
				case 0:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;

				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					regTarget = getRegister(ip);
					switch (regTarget) {
					case 0:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;

					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						registers[regTarget] = std::pow(registers[regFirst], registers[regSecond]);
						break;

					default:
						std::cout << commandCount << " | error: register is incorrect" << std::endl;
						execution();
						break;
					}
					break;

				default:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;
				}
			}
			else {
				std::cout << commandCount << " | error: register is incorrect" << std::endl;
				execution();
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 8: //SQR
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (!stack.empty()) {
				if (stack.back() >= 0) {
					stack.back() = std::sqrt(stack.back());
				}
				else {
					std::cout << commandCount << " | error: could not calculate square root from negative number: " << stack.back() << std::endl;
				}
			}
			else {
				std::cout << commandCount << " | error: stack is empty" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			if (registers[regFirst] >= 0) {
				registers[regFirst] = std::sqrt(registers[regFirst]);
			}
			else {
				std::cout << commandCount << " | error: could not calculate square root from negative number: " << registers[regFirst] << std::endl;
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 9: //LOG
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (!stack.empty()) {
				if (stack.back() != 0) {
					stack.back() = std::log10(stack.back());
				}
				else {
					std::cout << commandCount << " | error: value on stack is zero" << std::endl;
				}
			}
			else {
				std::cout << commandCount << " | error: stack is empty" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			if (registers[regFirst] != 0) {
				registers[regFirst] = std::log10(registers[regFirst]);
			}
			else {
				std::cout << commandCount << " | error: register value is zero" << std::endl;
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 10: //LON
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (!stack.empty()) {
				if (stack.back() != 0) {
					stack.back() = std::log(stack.back());
				}
				else {
					std::cout << commandCount << " | error: value on stack is zero" << std::endl;
				}
			}
			else {
				std::cout << commandCount << " | error: stack is empty" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			if (registers[regFirst] != 0) {
				registers[regFirst] = std::log(registers[regFirst]);
			}
			else {
				std::cout << commandCount << " | error: register value is zero" << std::endl;
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 11: //EXP
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (!stack.empty()) {
				stack.back() = std::exp(stack.back());
			}
			else {
				std::cout << commandCount << " | error: stack is empty" << std::endl;
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			registers[regFirst] = std::exp(registers[regFirst]);
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 12: //MOV
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (!stack.empty()) {
				regSecond = getRegister(ip);
				switch (regSecond) {
				case 0:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;

				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					std::swap(registers[regSecond], stack.back());
					break;

				default:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;
				}
			}
			else {
				std::cout << commandCount << " | error: stack is empty" << std::endl;
				execution();
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			switch (regSecond) {
			case 0:
				if (!stack.empty()) {
					std::swap(registers[regFirst], stack.back());
				}
				else {
					std::cout << commandCount << " | error: stack is empty" << std::endl;
					execution();
				}
				break;

			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				if (regFirst != regSecond) {
					std::swap(registers[regFirst], registers[regSecond]);
				}
				else {
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
				}
				break;

			default:
				std::cout << commandCount << " | error: register is incorrect" << std::endl;
				execution();
				break;
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 13: //SET
		regFirst = getRegister(ip);
		switch (regFirst) {
		case 0:
			if (!stack.empty()) {
				regSecond = getRegister(ip);
				switch (regSecond) {
				case 0:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;

				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					stack.back() = registers[regSecond];
					break;

				default:
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
					break;
				}
			}
			else {
				std::cout << commandCount << " | error: stack is empty" << std::endl;
				execution();
			}
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			regSecond = getRegister(ip);
			switch (regSecond) {
			case 0:
				if (!stack.empty()) {
					registers[regFirst] = stack.back();
				}
				else {
					std::cout << commandCount << " | error: stack is empty" << std::endl;
					execution();
				}
				break;

			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				if (regFirst != regSecond) {
					registers[regFirst] = registers[regSecond];
				}
				else {
					std::cout << commandCount << " | error: register is incorrect" << std::endl;
					execution();
				}
				break;

			default:
				std::cout << commandCount << " | error: register is incorrect" << std::endl;
				execution();
				break;
			}
			break;

		default:
			std::cout << commandCount << " | error: register is incorrect" << std::endl;
			execution();
			break;
		}
		break;

	case 14: //PRT
		std::cout << std::endl << "Stack: ";
		reversePrintVector(stack);
		printRegisters();
		std::cout << std::endl;
		break;

	case 15: // NOP
		std::cout << "do nothing" << std::endl;
		break;

	default:
		std::cout << commandCount << " | error: unknown instruction: " << instructionSet[*ip] << std::endl;
		break;
	}
}

int main(int argc, char** argv)
{
	if (argc <= 1) {
		std::cout << "error: no input file" << std::endl;
		return -1;
	}
	std::string filename = argv[1];

	if (filename.find(".mk") == std::string::npos) {
		std::cout << "error: wrong file extension" << std::endl;
		return -1;
	}
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "error: could not read file " << filename << std::endl;
		return -1;
	}
	std::string command;

	while (file >> command) {
		std::transform(command.begin(), command.end(), command.begin(), toupper);
		code.emplace_back(command);
	}
	file.close();

	instructionPointer = code.begin();;

	while (isRunning) {
		operations(instructionPointer);
	}

	return 0;
}