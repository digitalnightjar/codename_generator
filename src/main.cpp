#include <cstdint>
#include <generator.hpp>
#include <httplib.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const std::string generate(const Generator& first, const Generator& second) {
  std::string codename = first.getRandom();
  codename.append("_");
  codename.append(second.getRandom());
  return codename;
}

int main(void) {
  httplib::Server server;
  Generator animals("/app/animals.txt");
  Generator adjectives("/app/adjectives.txt");
  std::cout << "Name Generator<Animals> instantiated with [" << animals.size() << "] elements.\n";
  std::cout << "Name Generator<Adjectives> instantiated with [" << adjectives.size() << "] elements." << std::endl;

  server.Get("/", [&animals, &adjectives](const httplib::Request & req,
                                          httplib::Response &res) {
    if (animals.size() > 0 && adjectives.size() > 0) {
      if (req.has_param("count")) {
        auto countParam = req.get_param_value("count");
        std::string badCountMsg = "Bad Request: please provide a valid number for 'count' parameter.\n";
        try {
          std::int32_t count = std::stoi(countParam);
          if (count > 0) {
            std::string responseData = "";
            for (std::uint32_t i = 0; i < count; ++i) {
              responseData.append(generate(adjectives, animals));
              responseData.append("\n");
            }
            res.set_content(responseData, "text/plain");
          } else {
            res.status = 400;
            res.set_content(badCountMsg, "text/plain");
          }
        } catch(const std::invalid_argument& iaException) {
          res.status = 400;
          badCountMsg.append(iaException.what());
          res.set_content(badCountMsg, "text/plain");
        } catch (const std::out_of_range& oorException) {
          res.status = 400;
          badCountMsg.append(oorException.what());
          res.set_content(badCountMsg, "text/plain");
        }
      } else {
      const std::string codename = generate(adjectives, animals);
      res.set_content(codename, "text/plain");
      }
    } else {
      std::cout << "No seed data was initialised!" << std::endl;
      res.set_content("Unable to generate a random name!", "text/plain");
    }
  });

  server.Get("/shutdown", [&](const httplib::Request & req,
                              httplib::Response &res) {
    std::cout << "Service received request to shutdown from " << req.remote_addr << std::endl;
    server.stop();
  });

  server.listen("0.0.0.0", 8080);
  return 0;
}
