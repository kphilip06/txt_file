#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "../src/factorial.hpp"
#include <fstream>
#include <string>

// Helper to generate text files of arbitrary word counts
static void generate_input_file(const std::string& filename, std::size_t word_count) {
    std::ofstream out(filename);
    for (std::size_t i = 0; i < word_count; ++i) {
        out << "word" << i << " ";
    }
}

TEST_CASE("Benchmark file_system processing scaling", "[benchmark]") {
    // 1. Prepare sample files of increasing sizes
    generate_input_file("input_1k.txt", 1'000);
    generate_input_file("input_5k.txt", 5'000);
    generate_input_file("input_10k.txt", 10'000);
    generate_input_file("input_20k.txt", 20'000);
    generate_input_file("input_50k.txt", 50'000);
    generate_input_file("input_70k.txt", 70'000);
    generate_input_file("input_80k.txt", 80'000);

    // 2. Benchmark Small Input (1k words)
    BENCHMARK("Input Size: 1,000 words") {
        file_system fs;
        return fs.open_content("input_1k.txt"); // Return value prevents compiler optimizations
    };

    BENCHMARK("Input Size: 5,000 words") {
        file_system fs;
        return fs.open_content("input_5k.txt"); // Return value prevents compiler optimizations
    };

    // 3. Benchmark Medium Input (10k words)
    BENCHMARK("Input Size: 10,000 words") {
        file_system fs;
        return fs.open_content("input_10k.txt");
    };

    BENCHMARK("Input Size: 20,000 words") {
        file_system fs;
        return fs.open_content("input_20k.txt"); // Return value prevents compiler optimizations
    };

    BENCHMARK("Input Size: 50,000 words") {
        file_system fs;
        return fs.open_content("input_50k.txt"); // Return value prevents compiler optimizations
    };

    // 4. Benchmark Large Input (100k words)
    BENCHMARK("Input Size: 70,000 words") {
        file_system fs;
        return fs.open_content("input_70k.txt");
    };

    BENCHMARK("Input Size: 80,000 words") {
        file_system fs;
        return fs.open_content("input_80k.txt"); // Return value prevents compiler optimizations
    };
}