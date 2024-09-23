// Copyright 2023 <karl.eyre>
#include <fstream>
#include <iterator>
#include <random>
#include <string>
#include <algorithm>
#include <cctype>

#include <generator.hpp>

Generator::Generator(const std::string &filename) {
  std::fstream file;
  file.open(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      // Remove line endings
      line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) {
                return c == '\r' || c == '\n';
      }), line.end());
      // Ensure to Lowercase
      std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) {
          return std::tolower(c);
      });
      // Push back
      m_items.push_back(line);
    }
    file.close();
  }
}

const std::size_t Generator::size() const { return m_items.size(); }

const std::string Generator::getRandom() const {
  std::random_device random_device;
  std::mt19937 engine(random_device());
  std::uniform_int_distribution<int> dist(0, size() - 1);
  return m_items[dist(engine)];
}
