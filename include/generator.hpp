// Copyright 2023 <karl.eyre>
#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Generator {
public:
  explicit Generator(const std::string &filename);
  virtual ~Generator() {}
  const std::string getRandom() const;
  const std::size_t size() const;

private:
  std::vector<std::string> m_items{};
};
