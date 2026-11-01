#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>



struct fileObject {
    std::string filename;
    std::vector<std::pair<std::string, std::vector<int>>> words;
};
class file_system {
private:
    std::vector<std::pair<std::string, std::vector<int>>> count;
public:
    void open_content (std::string filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        std::ostringstream ss;
        ss << file.rdbuf();
        file.close();
        std::string content = ss.str();

        std::cout << "Text file read into string object." << std::endl;

        parse_content(content, count, filename);
    }
    void parse_content (std::string content, std::vector<std::pair<std::string, std::vector<int>>>& count, std::string filename) {
        std::cout << "Parsing string object...";

        std::string temp_word = "";
        int word_count = 0;

        for (int i = 0; i < content.length(); i++) {
            char c = std::tolower(static_cast<unsigned char>(content[i]));
            if (isalnum(c) || c == '-') {
                temp_word += c;
            } else if (!temp_word.empty()) {
                insertOrUpdate(temp_word, word_count);
                temp_word = "";
                ++word_count;
            }
        }
            if (!temp_word.empty()) {
                insertOrUpdate(temp_word, word_count);
            }
        std::sort(count.begin(), count.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        std::cout << "Done parsing string object." << std::endl;

        saveInsertedWords("output.txt", count);
    }
    void insertOrUpdate (const std::string& word, int word_count) {
        for (auto& entry : count) {
            if (entry.first == word) {
                entry.second.push_back(word_count);
                return;
            }
        }
        count.push_back(std::make_pair(word, std::vector<int>{word_count}));
    }
    void saveInsertedWords (std::string filename, std::vector<std::pair<std::string, std::vector<int>>>& count) {
        std::ofstream outfile(filename);

        for (const auto& entry : count) {
            const std::string& word = entry.first;
            const std::vector<int>& indices = entry.second;

            outfile << word << ": ";

            for (int i = 0; i < indices.size(); i++) {
                if (i == indices.size() - 1) {
                    outfile << indices[i];
                } else {
                    outfile << indices[i] << ", ";
                }
            }
            outfile << std::endl;
        }
        outfile.close();

        std::cout << "Parsed words saved to file: " << filename << std::endl;
    }

};
