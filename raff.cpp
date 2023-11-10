#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string fileName = "data.txt";

    // Open the file for appending
    std::ofstream outfile(fileName, std::ios::app);

    // Check if the file is opened successfully
    if (!outfile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return 1;
    }

    while (true) {
        std::string tableIdentifier;
        std::cout << "Enter Table Identifier (or type 'exit' to finish): ";
        std::cin >> tableIdentifier;

        if (tableIdentifier == "exit") {
            break;
        }

        // Write the table identifier as a comment
        outfile << "// Table: " << tableIdentifier << std::endl;

        // Write table header to the file
        std::string header;
        std::cout << "Enter Table Header: ";
        std::cin.ignore();  // Clear the newline character from the previous input
        std::getline(std::cin, header);
        outfile << header << std::endl;

        // Manually input and append data to the file
        while (true) {
            std::string data;
            std::cout << "Enter Data (or type 'exit' to finish): ";
            std::getline(std::cin, data);

            if (data == "exit") {
                break;
            }

            outfile << data << std::endl;
        }
    }

    // Close the file
    outfile.close();

    std::cout << "Tables have been appended to " << fileName << "." << std::endl;

    return 0;
}
