# codename_generator
A tiny C++ microservice, intended to be used withing larger systems to generate randomised codenames for new resources.

[Dockerhub Page](https://hub.docker.com/r/digitalnightjar/codename_generator)

# Usage
## Run using Docker:
Use the following command to run using docker, this will map your desired port to the containers port 8080.
`docker run --rm -d -p <your_port>:8080 digitalnightjar/codename_generator:latest`

## Usage
Requesting a new name:
HTTP GET http://<your_ip>:<your_mapped_port>/
example: `http://127.0.0.1:8080/`

Requesting multiple names:
HTTP GET http://<your_ip>:<your_mapped_port>/?count=<number_of_required_names>
example: `http://127.0.0.1:8080/?count=10`

Stopping the service (remotely)
HTTP GET http://<your_ip>:<your_mapped_port>/shutdown
example: `http://127.0.0.1:8080/shutdown`
