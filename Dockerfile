# Development / CI image for the BCE exterior light project.
#
# Provides everything needed to regenerate the test RTEs (ArUnit headless
# generator requires Java 8) and to build / test the software components:
#
#   docker build -t autosar-architect .
#
#   # Build and run the unit tests:
#   docker run --rm -v "$(pwd)":/workspace -w /workspace \
#       autosar-architect make test
#
#   # Regenerate the test RTEs with ArUnit:
#   docker run --rm -v "$(pwd)":/workspace -w /workspace \
#       autosar-architect make rte
#
FROM eclipse-temurin:8-jdk-jammy

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ca-certificates \
        git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/bash"]
