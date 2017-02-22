#include "string.h"
#include "iostream"
#include "dirent.h"
#include "vector"
#include "stdio.h"
#include "fstream"

// TODO: Fix any memory leaks
// TODO: Implement memory mapped files (only if needed)

// Function for scanning the files for inputted word
void scanfile(std::string input, std::string filepath) {
    std::ofstream oFile;
    std::ifstream pFile;
    pFile.open(filepath, std::ifstream::in);
    while (!pFile.eof())
    {
      //pFile.read(<>, <>)
      std::string line;
      getline(pFile, line);
      if (line.find(input, 0) != std::string::npos) {
        std::string path = "/root/Desktop/" + input + ".txt";
        line = line + '\n';
        oFile.open(path, std::ifstream::binary);
        oFile.write(line.c_str(), line.length());
        oFile.close();
      }
    }
    pFile.close();
}

int main(int argc, char * argv[]) {
  // Take command line input
  std::string input;
  input = argv[1];

  // Get the directory contents
  DIR * directory;
  struct dirent * entrance;
  std::vector < std::string > databases;
  if ((directory = opendir("/root/databases/uncommon/")) != NULL) {
    while ((entrance = readdir(directory)) != NULL) {
      databases.push_back(entrance -> d_name);
    }
  } else {
    std::perror("Error: no folder 'uncommon' in '/root/databases'");
    return EXIT_FAILURE;
  }

  // Loop through database files
  for (int i = 0; i < databases.size(); i++) {
    if(databases[i] != "." || databases[i] != "..") {
      std::cout << "[" + databases[i] + "]";
      std::cout << "Searching file: " + databases[i] + "\n";
      scanfile(input, "/root/databases/uncommon/" + databases[i]);
      std::cout << "Moving onto next file! \n";
    };
  }

  std::cout << "Done";

  return 0;
};
