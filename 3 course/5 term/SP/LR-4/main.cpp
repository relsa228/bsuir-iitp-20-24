#include "mono_encr.hpp"
#include "multithread_encr.hpp"
#include <chrono>

int main()
{
    std::fstream fmut;
    std::string inpt_f, inpt_s;

    std::string filename = "big_test.txt";
    int key = 4;
    int threadCount = 4;

    fmut.open(filename, std::fstream::in);
    getline( fmut, inpt_f, '\0');
    fmut.close();

    fmut.open(filename, std::fstream::in);
    getline( fmut, inpt_s, '\0');
    fmut.close();

    std::chrono::time_point<std::chrono::system_clock> start_f, end_f, start_s, end_s;

    start_f = std::chrono::system_clock::now();
    initMultiEncrypt(&inpt_f, "multiencr.txt", key, threadCount);
    end_f = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_f - start_f;
    std::cout << "Whith thread: " << elapsed_seconds.count() << "s\n";

    start_s = std::chrono::system_clock::now();
    monoEncrypt(&inpt_s, "monoencr.txt", 4);
    end_s = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_s = end_s - start_s;
    std::cout << "No thread: " << elapsed_seconds_s.count() << "s\n";

    initMultiDecrypt("multiencr.txt", 4);
    monoDecrypt("monoencr.txt", 4);
}