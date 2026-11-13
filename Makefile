# Convenience wrapper for the standard workflow.
# Build/test delegate to CMake; rte delegates to the ArUnit generator;
# docker-* run the same steps inside the pinned toolchain container.

BUILD_DIR ?= build

.PHONY: build test rte clean docker-image docker-build docker-test docker-rte

## Configure and build all targets (gtest, test RTE, SWCs, unit tests)
build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DIR) -j

## Build and run the unit tests
test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

## Regenerate the test RTEs from the AUTOSAR model (requires Java 8)
rte:
	cd bceutil/Scripts && ./generateTestRte.sh

## Remove the local build directory
clean:
	rm -rf $(BUILD_DIR)

## Build the pinned toolchain container (JDK 8 + build tools)
docker-image:
	docker build -t autosar-architect .

## Build inside the container
docker-build: docker-image
	docker run --rm -v "$(CURDIR)":/workspace -w /workspace \
	    autosar-architect make build

## Build and run the unit tests inside the container
docker-test: docker-image
	docker run --rm -v "$(CURDIR)":/workspace -w /workspace \
	    autosar-architect make test

## Regenerate the test RTEs inside the container
docker-rte: docker-image
	docker run --rm -v "$(CURDIR)":/workspace -w /workspace \
	    autosar-architect make rte
