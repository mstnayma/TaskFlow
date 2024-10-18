#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <map>
#include <vector>

enum TokenType {
    KEYWORD, IDENTIFIER, STRINGLITERAL, INTLITERAL, OPERATOR, ASSIGNMENT, ERROR
};

std::map<std::string, TokenType> keywords = {
    {"task", KEYWORD},
    {"run", KEYWORD},
    {"every", KEYWORD},
    {"if", KEYWORD},
    {"fails", KEYWORD},
    {"send", KEYWORD},
    {"to", KEYWORD}
};

struct Token {
    TokenType type;
    std::string value;
};

class Scanner {
public:
    Scanner(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
    }

    std::vector<Token> scan() {
        std::vector<Token> tokens;
        std::string line;
        int lineNum = 1;

        while (std::getline(file, line)) {
            size_t index = 0;
            while (index < line.size()) {
                char current = line[index];

                if (std::isspace(current)) {
                    index++;
                } else if (std::isalpha(current) || current == '_') {
                    std::string identifier;
                    while (index < line.size() && (std::isalnum(line[index]) || line[index] == '_')) {
                        identifier += line[index++];
                    }
                    if (keywords.count(identifier)) {
                        tokens.push_back({KEYWORD, identifier});
                    } else {
                        tokens.push_back({IDENTIFIER, identifier});
                    }
                } else if (std::isdigit(current)) {
                    std::string number;
                    while (index < line.size() && std::isdigit(line[index])) {
                        number += line[index++];
                    }
                    tokens.push_back({INTLITERAL, number});
                } else if (current == '"') {
                    index++;
                    std::string strLiteral;
                    while (index < line.size() && line[index] != '"') {
                        if (line[index] == '\\' && index + 1 < line.size()) {
                            strLiteral += line[index + 1];
                            index += 2;
                        } else {
                            strLiteral += line[index++];
                        }
                    }
                    if (index < line.size()) {
                        tokens.push_back({STRINGLITERAL, strLiteral});
                        index++;
                    } else {
                        throw std::runtime_error("Error: Unmatched quote in string literal at line " + std::to_string(lineNum));
                    }
                } else if (current == '{' || current == '}' || current == '(' || current == ')' || current == ':' || current == ',') {
                    tokens.push_back({OPERATOR, std::string(1, current)});
                    index++;
                } else if (current == ':') {
                if (index + 1 < line.size() && line[index + 1] == '=') {
                    tokens.push_back({ASSIGNMENT, ":="});
                    index += 2; // Skip the next character
                } else {
                    throw std::runtime_error("Unexpected character ':' at line " + std::to_string(lineNum));
                }
            } else if (current == '=') {
                tokens.push_back({OPERATOR, "="});
                index++;
            } else if (current == '+' || current == '-' || current == '*' || current == '/') {
                tokens.push_back({OPERATOR, std::string(1, current)});
                index++;
            } else {
                throw std::runtime_error("Unexpected character '" + std::string(1, current) + "' at line " + std::to_string(lineNum));
            }
        }
        lineNum++;
    }
    return tokens;
}

private:
    std::ifstream file;
};

void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::cout << "<" << (token.type == KEYWORD ? "KEYWORD" : token.type == IDENTIFIER ? "IDENTIFIER" :
                              token.type == STRINGLITERAL ? "STRINGLITERAL" : token.type == INTLITERAL ? "INTLITERAL" :
                              token.type == ASSIGNMENT ? "ASSIGNMENT" : "OPERATOR")
                  << ", " << token.value << ">" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.tfl>" << std::endl;
        return 1;
    }

    try {
        Scanner scanner(argv[1]);
        std::vector<Token> tokens = scanner.scan();
        printTokens(tokens);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
