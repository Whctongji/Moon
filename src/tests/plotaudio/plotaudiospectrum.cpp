#include <iostream>
#include <vector>
#include <sndfile.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
    // Open the audio file
    SF_INFO info;
    //SNDFILE *file = sf_open("/home/whc/Desktop/file_example_WAV_5MG.wav", SFM_READ, &info);
    SNDFILE *file = sf_open("/home/whc/Desktop/bicycle_bell.wav", SFM_READ, &info);

    if (!file) {
        std::cerr << "Error opening audio file\n";
        return 1;
    }

    // Read the audio data
    std::vector<double> audioData(info.frames);
    sf_read_double(file, audioData.data(), info.frames);

    // Close the audio file
    sf_close(file);

    // Export the data to a CSV file
    std::ofstream outFile("/home/whc/Desktop/audio_data0.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file\n";
        return 1;
    }
    for (int i = 0; i < audioData.size(); ++i) {
        outFile << i / double(info.samplerate) << "," << audioData[i] << "\n";
    }
    outFile.close();


    // Open the CSV file
    std::ifstream file2("/home/whc/Desktop/audio_data0.csv");
    if (!file2.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // Read and parse the CSV data
    std::vector<std::vector<std::string>> csvData;
    std::string line;
    while (getline(file2, line)) {
        if (line.empty()) {
            // Skip empty lines
            continue;
        }
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> row;
        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        csvData.push_back(row);
    }
    file2.close();

    //system("unset GTK_PATH");
    //system("unset GIO_MODULE_DIR");

    // Open the CSV file
    ifstream file7("/home/whc/Desktop/audio_data0.csv");

    if (!file7.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Create a Gnuplot script file
    ofstream script("plot_script.gnu");

    if (!script.is_open()) {
        cerr << "Error creating Gnuplot script file!" << endl;
        return 1;
    }

    // Write Gnuplot commands to the script file
    script << "set title 'CSV Data Plot'" << endl;
    script << "set xlabel 'X-axis'" << endl;
    script << "set ylabel 'Y-axis'" << endl;
    script << "set datafile separator comma" << endl;
    //script << "set term png" << endl;
    //script << "set output '/home/whc/Desktop/audio_spectrum.png'" << endl;
    script << "plot '/home/whc/Desktop/audio_data0.csv' using 1:2 with linespoints title 'Data'" << endl;
    //script << "set output" << endl;
    script << "pause -1" << endl;

    // Close the script file
    script.close();

    // Execute Gnuplot to create the plot
    system("gnuplot plot_script.gnu");

    return 0;
}
