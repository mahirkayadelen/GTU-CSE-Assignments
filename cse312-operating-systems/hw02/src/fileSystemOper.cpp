#include "fileSystem.h"



void loadFileSystem(const char* fileName, FileSystem &fs);
void saveFileSystem(const char* fileName, FileSystem &fs);

void mkdir(FileSystem &fs, const string &path);
void rmdir(FileSystem &fs, const string &path);
void write(FileSystem &fs, const string &path, const string &dataFile);
void read(FileSystem &fs, const string &path, const string &outputFile);
void del(FileSystem &fs, const string &path);
void chmod(FileSystem &fs, const string &path, const string &permissions);
void addpw(FileSystem &fs, const string &path, const string &password);
void dir(FileSystem &fs, const string &path);
void dumpe2fs(FileSystem &fs);

bool verifyPassword(const FileSystem& fs, const string& path, const string& password);
bool verifyPermissions(const FileSystem& fs, const string& path, unsigned char requiredPermissions);
bool createOrUpdateDirectoryEntry(FileSystem &fs, const string &path, unsigned int size, unsigned short startBlock, unsigned char permissions);


void loadFileSystem(const char* fileName, FileSystem &fs) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        cerr << "Error loading file system." << endl;
        exit(1);
    }

    // Read Super Block
    file.read(reinterpret_cast<char*>(&fs.superBlock), sizeof(SuperBlock));

    // Read FAT
    fs.fat.resize(fs.superBlock.totalBlocks);
    file.read(reinterpret_cast<char*>(fs.fat.data()), fs.fat.size() * sizeof(FATEntry));

    // Read Root Directory
    fs.rootDirectory.resize(MAX_FILES);
    file.read(reinterpret_cast<char*>(fs.rootDirectory.data()), fs.rootDirectory.size() * sizeof(DirectoryEntry));

    // Read Data Blocks
    fs.data.resize(fs.superBlock.totalBlocks, vector<char>(fs.superBlock.blockSize));
    for (auto &block : fs.data) {
        file.read(block.data(), block.size());
    }

    file.close();

}

void saveFileSystem(const char* fileName, FileSystem &fs) {
    ofstream file(fileName, ios::binary);
    if (!file) {
        cerr << "Error saving file system." << endl;
        exit(1);
    }

    // Write Super Block
    file.write(reinterpret_cast<const char*>(&fs.superBlock), sizeof(SuperBlock));

    // Write FAT
    file.write(reinterpret_cast<const char*>(fs.fat.data()), fs.fat.size() * sizeof(FATEntry));

    // Write Root Directory
    file.write(reinterpret_cast<const char*>(fs.rootDirectory.data()), fs.rootDirectory.size() * sizeof(DirectoryEntry));

    // Write Data Blocks
    for (auto &block : fs.data) {
        file.write(block.data(), block.size());
    }

    file.close();
}

void mkdir(FileSystem &fs, const string &path) {
    // Check if the path is empty or does not start with a backslash
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return;
    }

    // Stream to split the path into segments
    stringstream ss(path.substr(1)); // Remove leading backslash
    string segment;
    DirectoryEntry *currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Default to root directory

    // Process each segment of the path
    while (getline(ss, segment, '\\')) {
        bool found = false;
        
        // Search for the segment in the root directory
        for (auto &entry : fs.rootDirectory) {
            // Check if the entry is a directory and matches the segment name
            if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && 
                (currentDir == nullptr ? entry.parentBlock == FAT_ENTRY_FREE : entry.parentBlock == currentDir->startBlock)) {
                currentDir = &entry;
                found = true;
                break;
            }
        }

        // If the segment was not found in the current directory
        if (!found) {
            if (ss.eof()) { // Check if it's the end of the path to create a new directory here
                for (auto &entry : fs.rootDirectory) {
                    if (entry.name[0] == '\0') { // Find an empty entry to use
                        // Setup the new directory entry
                        strncpy(entry.name, segment.c_str(), MAX_FILENAME);
                        entry.size = 0;
                        entry.ownerPermissions = 0b00000011; // default RW
                        entry.creation = entry.lastModification = time(NULL);
                        entry.isDirectory = true;
                        entry.parentBlock = currentDir ? currentDir->startBlock : FAT_ENTRY_FREE; // Set parent block

                        // Allocate a block for the new directory
                        for (unsigned short i = 1; i < fs.fat.size(); ++i) {
                            if (fs.fat[i].nextBlock == FAT_ENTRY_FREE) {
                                entry.startBlock = i;
                                fs.fat[i].nextBlock = FAT_ENTRY_EOF; // Mark as end of chain
                                fs.superBlock.freeBlocks--;
                                cout << "Directory created" << endl;
                                return;
                            }
                        }

                        cerr << "No space for new directory" << endl;
                        return;
                    }
                }
            } else {
                // Output error if the directory in the path was not found
                cerr << "Directory not found: " << segment << endl;
                return;
            }
        }
    }
}


// Function to remove a directory in the file system
void rmdir(FileSystem &fs, const string &path) {
    // Check if the path is empty or does not start with a backslash
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return;
    }

    // Stream to split the path into segments
    stringstream ss(path.substr(1)); // Remove leading backslash
    string segment;
    DirectoryEntry *currentDir = nullptr;
    DirectoryEntry *parentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Default to root directory

    // Process each segment of the path
    while (getline(ss, segment, '\\')) {
        bool found = false;

        // Search in the root directory or within the current directory based on the depth in the path
        if (currentDir == nullptr) {
            // Searching in root directory for the first segment
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == FAT_ENTRY_FREE) {
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }
        } else {
            // Searching in the current directory for subsequent segments
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && entry.parentBlock == currentDir->startBlock && strcmp(entry.name, segment.c_str()) == 0) {
                    parentDir = currentDir;
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }
        }

        // Output an error if the directory is not found
        if (!found) {
            cerr << "Directory not found: " << segment << endl;
            return;
        }
    }

    // Ensure the directory is empty before removing
    for (const auto &entry : fs.rootDirectory) {
        if (entry.name[0] != '\0' && entry.parentBlock == currentDir->startBlock) {
            cerr << "Directory not empty: " << segment << endl;
            return;
        }
    }

    // Mark the directory entry as free
    memset(currentDir->name, 0, MAX_FILENAME);
    currentDir->size = 0;
    currentDir->ownerPermissions = 0;
    currentDir->lastModification = 0;
    currentDir->creation = 0;
    memset(currentDir->password, 0, 32);
    currentDir->startBlock = FAT_ENTRY_FREE;
    currentDir->parentBlock = FAT_ENTRY_FREE;
    currentDir->isDirectory = false;

    // Clear the FAT entries linked to the directory
    unsigned short block = currentDir->startBlock;
    while (block != FAT_ENTRY_FREE && block != 0xFFF) {
        unsigned short nextBlock = fs.fat[block].nextBlock;
        fs.fat[block].nextBlock = FAT_ENTRY_FREE;
        block = nextBlock;
    }

    // Increment the count of free blocks
    fs.superBlock.freeBlocks++;

    cout << "Directory removed: " << segment << endl;
}

// Function to create or update a file entry in the file system
bool createOrUpdateDirectoryEntry(FileSystem &fs, const string &path, unsigned int size, unsigned short startBlock, unsigned char permissions) {
    string parentPath, fileName;
    size_t pos = path.rfind('\\'); // Finds the last backslash position in the path

    // Determine if the entry is in the root directory or a subdirectory
    if (pos != string::npos) {
        if (pos == 0) { // The entry is in the root directory
            fileName = path.substr(1); // Extract the file name, omitting the first backslash
        } else {
            parentPath = path.substr(0, pos); // Extract the parent directory's path
            fileName = path.substr(pos + 1); // Extract the file name
        }
    } else { // Path has no backslashes, indicating it's directly in the root
        fileName = path;
    }

    DirectoryEntry *parentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Default to root directory if no parent path specified

    // If there's a parent path, find the corresponding directory entry
    if (!parentPath.empty()) {
        stringstream ss(parentPath); // Create a stream to parse segments
        string segment;
        bool found = false;

        while (getline(ss, segment, '\\')) {
            found = false;
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && 
                   (parentDir == nullptr ? entry.parentBlock == FAT_ENTRY_FREE : entry.parentBlock == parentDir->startBlock)) {
                    parentDir = &entry;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cerr << "Segment not found: " << segment << endl;
                return false;
            }
        }
        parentBlock = parentDir ? parentDir->startBlock : FAT_ENTRY_FREE; // Set the parent block if found
    }

    // Check for an existing file in the correct directory
    for (auto &entry : fs.rootDirectory) {
        if (!entry.isDirectory && strcmp(entry.name, fileName.c_str()) == 0 && entry.parentBlock == parentBlock) {
            // Update existing file entry
            entry.size = size;
            entry.startBlock = startBlock;
            entry.ownerPermissions = permissions;
            entry.lastModification = time(nullptr); // Update modification time
            return true;
        }
    }

    // Create a new file entry if it does not exist
    for (auto &entry : fs.rootDirectory) {
        if (entry.name[0] == '\0') { // Find the first empty slot
            strncpy(entry.name, fileName.c_str(), MAX_FILENAME);
            entry.size = size;
            entry.startBlock = startBlock;
            entry.ownerPermissions = permissions;
            entry.isDirectory = false;
            entry.parentBlock = parentBlock;
            entry.creation = entry.lastModification = time(nullptr); // Set creation and modification times
            return true;
        }
    }

    cerr << "No space for new file in directory." << endl;
    return false; // Return false if no empty slot is found
}

// Function to write data from an external file into the file system
void write(FileSystem &fs, const string &path, const string &dataFile) {
    // Check if the path is empty or does not start with a backslash
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return;
    }

    // Open the input file in binary mode
    ifstream inputFile(dataFile, ios::binary);
    if (!inputFile) {
        cerr << "Error reading input file: " << dataFile << endl;
        return;
    }

    // Determine the size of the data to be written
    inputFile.seekg(0, ios::end);
    size_t dataSize = static_cast<size_t>(inputFile.tellg());
    inputFile.seekg(0, ios::beg);

    // Calculate the number of blocks needed to store the data
    unsigned int blocksNeeded = (dataSize + fs.superBlock.blockSize - 1) / fs.superBlock.blockSize;
    if (blocksNeeded > fs.superBlock.freeBlocks) {
        cerr << "File is too big, Not enough free block available\nBlocks needed: " << blocksNeeded << "\nfreeBlocks: " << fs.superBlock.freeBlocks << endl;
        return;
    }

    // Variables to track the allocation of blocks
    unsigned short previousBlock = FAT_ENTRY_EOF;
    unsigned short firstBlock = FAT_ENTRY_FREE;
    bool foundFreeBlock;

    // Allocate blocks and write data
    for (unsigned int i = 0; i < blocksNeeded; ++i) {
        foundFreeBlock = false;
        unsigned short currentBlock = FAT_ENTRY_FREE;

        // Find a free block
        for (unsigned short j = 1; j < fs.superBlock.totalBlocks; ++j) {
            if (fs.fat[j].nextBlock == FAT_ENTRY_FREE) {
                currentBlock = j;
                fs.fat[j].nextBlock = FAT_ENTRY_EOF;
                fs.superBlock.freeBlocks--; // Decrement the count of free blocks
                foundFreeBlock = true;
                break;
            }
        }

        // If no free block is found, terminate the operation
        if (!foundFreeBlock) {
            cerr << "No free block available" << endl;
            break;
        }

        // Chain the blocks together
        if (firstBlock == FAT_ENTRY_FREE) firstBlock = currentBlock;
        if (previousBlock != FAT_ENTRY_EOF) fs.fat[previousBlock].nextBlock = currentBlock;
        previousBlock = currentBlock;

        // Read data from file and write it to the data block
        vector<char> buffer(fs.superBlock.blockSize, 0);
        inputFile.read(buffer.data(), fs.superBlock.blockSize);
        fs.data[currentBlock] = buffer;
    }

    // Mark the last block in the chain
    if (previousBlock != FAT_ENTRY_EOF) {
        fs.fat[previousBlock].nextBlock = FAT_ENTRY_EOF;
    }

    // If blocks were successfully allocated, update or create the directory entry
    if (firstBlock != FAT_ENTRY_FREE && foundFreeBlock) {
        cout << "File written successfully " << endl;
        if (!createOrUpdateDirectoryEntry(fs, path.substr(1), dataSize, firstBlock, 0b00000011)) { // Example permissions: Read and Write
            cerr << "Failed to create or update directory entry." << endl;
        }
    } else {
        cerr << "Failed to write the file." << endl;
    }

    // Close the input file
    inputFile.close();
}

// Function to read data from a file within the file system and write it to an output file
void read(FileSystem &fs, const string &path, const string &outputFile) {
    // Check if the path is empty or does not start with a backslash
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return;
    }

    // Create an output file stream in binary mode
    ofstream outputFileStream(outputFile, ios::binary);
    if (!outputFileStream) {
        cerr << "Error creating output file: " << outputFile << endl;
        return;
    }

    // Stream to split the path into segments
    stringstream ss(path.substr(1)); // Remove leading backslash
    string segment;
    DirectoryEntry *currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Default to root directory

    // Process each segment of the path
    while (getline(ss, segment, '\\')) {
        bool found = false;

        // Search in the root directory or within the current directory based on the depth in the path
        if (currentDir == nullptr) {
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == FAT_ENTRY_FREE) {
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }
        } else {
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && entry.parentBlock == currentDir->startBlock && strcmp(entry.name, segment.c_str()) == 0) {
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }
        }

        // Check for directory not found error
        if (!found && !ss.eof()) {
            cerr << "Directory not found: " << segment << endl;
            return;
        }

        // Attempt to find the file at the end of the path
        if (!found && ss.eof()) {
            for (const auto &entry : fs.rootDirectory) {
                if (!entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                    unsigned short currentBlock = entry.startBlock;
                    streamsize remainingDataSize = entry.size;

                    // Read data block by block
                    while (currentBlock != 0xFFF && remainingDataSize > 0) {
                        streamsize bytesToWrite = min(remainingDataSize, (streamsize)fs.superBlock.blockSize);
                        outputFileStream.write(fs.data[currentBlock].data(), bytesToWrite);

                        remainingDataSize -= bytesToWrite;
                        currentBlock = fs.fat[currentBlock].nextBlock;
                    }
                    cout << "File read: " << path << endl;
                    outputFileStream.close();
                    return;
                }
            }
            cerr << "File not found: " << segment << endl;
            return;
        }
    }
}

// Function to delete a file from the file system
void del(FileSystem &fs, const string &path) {
    // Check if the path is empty or does not start with a backslash
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return;
    }

    // Stream to split the path into segments
    stringstream ss(path.substr(1)); // Remove leading backslash
    string segment;
    DirectoryEntry *currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Default to root directory

    // Process each segment of the path
    while (getline(ss, segment, '\\')) {
        bool found = false;

        // Search in the root directory or within the current directory based on the depth in the path
        if (currentDir == nullptr) {
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == FAT_ENTRY_FREE) {
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }
        } else {
            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && entry.parentBlock == currentDir->startBlock && strcmp(entry.name, segment.c_str()) == 0) {
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }
        }

        // Check for directory not found error
        if (!found && !ss.eof()) {
            cerr << "Directory not found: " << segment << endl;
            return;
        }

        // Attempt to find and delete the file at the end of the path
        if (!found && ss.eof()) {
            for (auto &entry : fs.rootDirectory) {
                if (!entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                    unsigned short currentBlock = entry.startBlock;
                    // Loop to free all blocks associated with the file
                    while (currentBlock != 0xFFF) {
                        unsigned short nextBlock = fs.fat[currentBlock].nextBlock;
                        fs.fat[currentBlock].nextBlock = FAT_ENTRY_FREE; // Free the block
                        fs.superBlock.freeBlocks++; // Increment the count of free blocks
                        currentBlock = nextBlock;
                    }
                    memset(&entry, 0, sizeof(DirectoryEntry)); // Zero out the directory entry
                    cout << "File deleted: " << path << endl;
                    return;
                }
            }
            cerr << "File not found: " << segment << endl;
            return;
        }
    }
}

// Function to change permissions within the file system
void chmod(FileSystem &fs, const string &path, const string &permissions) {
    // Stream to split the path into segments, starting after the leading backslash
    stringstream ss(path.substr(1)); 
    string segment;
    DirectoryEntry *currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Start from root directory

    // Navigate through the directory structure to the specified file or directory
    while (getline(ss, segment, '\\')) {
        bool found = false;

        // Search for the directory or file in the current directory or root
        for (auto &entry : fs.rootDirectory) {
            if ((entry.isDirectory || !entry.isDirectory) && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                currentDir = &entry;
                parentBlock = entry.startBlock; // Update parent block for the next level
                found = true;
                break;
            }
        }

        // If the directory or file is not found, display an error and exit
        if (!found) {
            cerr << "File or directory not found: " << segment << endl;
            return;
        }
    }

    // If no directory entry is found by the end of the path, report an error
    if (currentDir == nullptr) {
        cerr << "File not found: " << path << endl;
        return;
    }

    // Parse the permissions string and apply changes to the file or directory's permissions
    if (permissions[0] == '+' || permissions[0] == '-') {
        for (size_t i = 1; i < permissions.length(); ++i) {
            switch (permissions[i]) {
                case 'r': // Read permission
                    if (permissions[0] == '+') {
                        currentDir->ownerPermissions |= 0b00000010; // Set read bit
                    } else {
                        currentDir->ownerPermissions &= ~0b00000010; // Clear read bit
                    }
                    break;
                case 'w': // Write permission
                    if (permissions[0] == '+') {
                        currentDir->ownerPermissions |= 0b00000001; // Set write bit
                    } else {
                        currentDir->ownerPermissions &= ~0b00000001; // Clear write bit
                    }
                    break;
                default:
                    // Handle invalid permission flags
                    cerr << "Invalid permission flag: " << permissions[i] << endl;
                    return;
            }
        }
        // Confirm permissions update
        cout << "Permissions updated for: " << path << endl;
    } else {
        // Handle invalid permissions format
        cerr << "Invalid permissions format: " << permissions << endl;
    }
}

// Function to add or update a password for a file or directory in the file system
void addpw(FileSystem &fs, const string &path, const string &password) {
    // Check if the path is empty or does not start with a backslash
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return;
    }

    // Stream to split the path into segments, removing the leading backslash for uniform handling
    stringstream ss(path.substr(1)); 
    string segment;
    DirectoryEntry *currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Start at the root directory

    // Traverse the directory structure to find the specified file or directory
    while (getline(ss, segment, '\\')) {
        bool found = false;

        // Search for the directory or file in the current directory or root
        for (auto &entry : fs.rootDirectory) {
            if ((entry.isDirectory || !entry.isDirectory) && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                currentDir = &entry;
                parentBlock = entry.startBlock; // Update parent block for the next level
                found = true;
                break;
            }
        }

        // If the directory or file is not found, display an error and exit
        if (!found) {
            cerr << "File or directory not found: " << segment << endl;
            return;
        }
    }

    // If the directory entry is found, add or update the password
    if (currentDir) {
        strncpy(currentDir->password, password.c_str(), 31); // Copy password to directory entry, ensuring not to overflow buffer
        currentDir->password[31] = '\0'; // Ensure the password is null-terminated
        cout << "Password added for: " << path << endl;
    } else {
        cerr << "File or directory not found for password addition." << endl;
    }
}

// Helper function to format time
string formatTime(time_t time) {
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void dir(FileSystem &fs, const string &path) {
    DirectoryEntry *currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Default to root directory

    if (path == "\\" || path.empty()) {
        // Handle root directory listing explicitly
        parentBlock = FAT_ENTRY_FREE;
    } else {
        stringstream ss(path.substr(1)); // Remove leading backslash
        string segment;

        while (getline(ss, segment, '\\')) {
            bool found = false;

            for (auto &entry : fs.rootDirectory) {
                if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                    currentDir = &entry;
                    parentBlock = entry.startBlock;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cerr << "Directory not found: " << path << endl;
                return;
            }
        }
    }

    // List contents of the current directory
    cout << left << setw(20) << "Name"
              << setw(10) << "Size"
              << setw(10) << "Permissions"
              << setw(20) << "Last Modified"
              << setw(20) << "Creation Date"
              << setw(20) << "Password Protected" << endl;

    for (const auto &entry : fs.rootDirectory) {
        if (entry.name[0] != '\0' && entry.parentBlock == parentBlock) {
            cout << left << setw(20) << entry.name
                      << setw(10) << entry.size
                      << setw(10) << bitset<2>(entry.ownerPermissions)
                      << setw(20) << formatTime(entry.lastModification)
                      << setw(20) << formatTime(entry.creation)
                      << (entry.password[0] != '\0' ? "Yes" : "No")
                      << endl;
        }
    }
}

void dumpe2fs(FileSystem &fs) {
    cout << "SuperBlock Information:" << endl;
    cout << "Block Size: " << fs.superBlock.blockSize << " bytes" << endl;
    cout << "Total Blocks: " << fs.superBlock.totalBlocks << endl;
    cout << "Free Blocks: " << fs.superBlock.freeBlocks << endl;

    int fileCount = 0;
    int directoryCount = 0;

    // Iterate over root directory entries to count files and directories
    for (const auto &entry : fs.rootDirectory) {
        if (entry.name[0] != '\0') {
            if (entry.isDirectory) {
                directoryCount++;
            } else {
                fileCount++;
            }
        }
    }

    cout << "Total Files: " << fileCount << endl;
    cout << "Total Directories: " << directoryCount << endl;


    // Display information about each file and the blocks it occupies
    for (const auto &entry : fs.rootDirectory) {
        if (entry.name[0] != '\0' && !entry.isDirectory) {  // Only process files, not directories
            cout << "------------------------------" << endl;
            cout << "File: " << entry.name << ", Size: " << entry.size 
                      << ", Permissions: " << bitset<2>(entry.ownerPermissions) << endl;

            cout << "Blocks occupied: ";
            unsigned short currentBlock = entry.startBlock;
            while (currentBlock != FAT_ENTRY_EOF && currentBlock != FAT_ENTRY_FREE) {
                cout << currentBlock << " ";
                if (fs.fat[currentBlock].nextBlock != FAT_ENTRY_EOF) {
                    currentBlock = fs.fat[currentBlock].nextBlock;
                } else {
                    break;
                }
            }
            cout << endl;

        }
    }
}

bool verifyPassword(const FileSystem& fs, const string& path, const string& password) {
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return false;
    }

    stringstream ss(path.substr(1)); // Remove the leading backslash for parsing
    string segment;
    const DirectoryEntry* currentDir = nullptr; 
    unsigned short parentBlock = FAT_ENTRY_FREE; // Start at the root directory

    while (getline(ss, segment, '\\')) {
        bool found = false;

        for (const auto& entry : fs.rootDirectory) { 
            if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && 
               (currentDir == nullptr ? entry.parentBlock == FAT_ENTRY_FREE : entry.parentBlock == currentDir->startBlock)) {
                currentDir = &entry;
                parentBlock = entry.startBlock;
                found = true;
                break;
            }
        }

        if (!found && !ss.eof()) { // If not found and not at the end of the path, it's an error
            cerr << "Directory not found: " << segment << endl;
            return false;
        }

        if (!found && ss.eof()) { // Check at the end of the path for the file
            for (const auto& entry : fs.rootDirectory) { // Use 'const auto&'
                if (!entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                    if (entry.password[0] != '\0') { // Check if the file has a password
                        return password == entry.password; // Verify the password
                    }
                    return true; // No password set, so allow access
                }
            }
            cerr << "File not found: " << segment << endl;
            return false; // File not found at the end of the path
        }
    }

    return false; // Default return if nothing else triggered
}


bool verifyPermissions(const FileSystem& fs, const string& path, unsigned char requiredPermissions) {
    if (path.empty() || path[0] != '\\') {
        cerr << "Invalid path. It should start with '\\'." << endl;
        return false;
    }

    stringstream ss(path.substr(1));  // Remove the leading backslash for parsing
    string segment;
    const DirectoryEntry* currentDir = nullptr;
    unsigned short parentBlock = FAT_ENTRY_FREE; // Start at the root directory

    while (getline(ss, segment, '\\')) {
        bool found = false;

        for (const auto& entry : fs.rootDirectory) {
            if (entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 &&
               (currentDir == nullptr ? entry.parentBlock == FAT_ENTRY_FREE : entry.parentBlock == currentDir->startBlock)) {
                currentDir = &entry;
                parentBlock = entry.startBlock;
                found = true;
                break;
            }
        }

        if (!found && !ss.eof()) {
            cerr << "Directory not found: " << segment << endl;
            return false;
        }

        if (!found && ss.eof()) {
            for (const auto& entry : fs.rootDirectory) {
                if (!entry.isDirectory && strcmp(entry.name, segment.c_str()) == 0 && entry.parentBlock == parentBlock) {
                    // Check permissions
                    if ((entry.ownerPermissions & requiredPermissions) == requiredPermissions) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            cerr << "File not found: " << segment << endl;
            return false;
        }
    }

    return false; // File not found at the end of the path
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <file system data file> <operation> [parameters]" << endl;
        return 1;
    }

    const char* fileName = argv[1];
    string operation = argv[2];
    FileSystem fs;


    loadFileSystem(fileName, fs);

    if (operation == "mkdir") {
        if (argc != 4) {
            cerr << "Usage: " << argv[0] << " <file system data file> mkdir <path>" << endl;
            return 1;
        }
        string path = argv[3];
        mkdir(fs, path);
        saveFileSystem(fileName, fs);
    } else if (operation == "rmdir") {
        if (argc != 4) {
            cerr << "Usage: " << argv[0] << " <file system data file> rmdir <path>" << endl;
            return 1;
        }
        string path = argv[3];
        rmdir(fs, path);
        saveFileSystem(fileName, fs);
    } else if (operation == "write") {
        if (argc != 5) {
            cerr << "Usage: " << argv[0] << " <file system data file> write <path> <data file>" << endl;
            return 1;
        }
        string path = argv[3];
        string dataFile = argv[4];
        write(fs, path, dataFile);
        saveFileSystem(fileName, fs);
    } else if (operation == "read") {
        if (argc != 5 && argc != 6) {
            cerr << "Usage: " << argv[0] << " <file system data file> read <path> <output file> [password]" << endl;
            return 1;
        }
        string path = argv[3];
        string outputFile = argv[4];
        string password = (argc == 6) ? argv[5] : "";

        if (verifyPermissions(fs, path, 0b00000010)) {
            if(verifyPassword(fs, path, password)){
                read(fs, path, outputFile);
            }
            else{
                cerr << "Access denied: Incorrect or no password provided for file: " << path << endl;
            }
        } else {
            cerr << "Permission denied: Insufficient permissions for operation on file: " << path << endl;
            return 1; // Exit with error
        }
    } else if (operation == "del") {
    if (argc != 5 && argc != 4) {
        cerr << "Usage: " << argv[0] << " <file system data file> del <path> [password]" << endl;
        return 1;
    }
    string path = argv[3];
    string password = (argc == 5) ? argv[4] : "";

    // Verify write permissions (write permission is represented by 0b00000001)
    if (verifyPermissions(fs, path, 0b00000001)) {
        // Check if the password is correct before deleting
        if (verifyPassword(fs, path, password)) {
            del(fs, path);  // Proceed with deletion
            saveFileSystem(fileName, fs);  // Save changes
        } else {
            cerr << "Access denied: Incorrect or no password provided for file: " << path << endl;
            return 1; // Exit with error
        }
    } else {
        cerr << "Permission denied: Insufficient permissions for deleting the file: " << path << endl;
        return 1; // Exit with error
    }
    } else if (operation == "chmod") {
        if (argc != 5 && argc != 6) {  // Expect path, permissions, and password as arguments
            cerr << "Usage: " << argv[0] << " <file system data file> chmod <path> <permissions> <password>" << endl;
            return 1;
        }
        string path = argv[3];
        string permissions = argv[4];
        string password = (argc == 6) ? argv[5] : "";

        // Verify password before changing permissions
        if (verifyPassword(fs, path, password)) {
            chmod(fs, path, permissions);  // Proceed with changing permissions
            saveFileSystem(fileName, fs);  // Save changes
        } else {
            cerr << "Access denied: Incorrect or no password provided for file: " << path << endl;
            return 1; // Exit with error
        }
    } else if (operation == "addpw") {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <file system data file> addpw <path> <password>" << endl;
        return 1;
    }
    string path = argv[3];
    string password = argv[4];

    // Verify write permissions (assuming write permission is represented by 0b00000001)
    if (verifyPermissions(fs, path, 0b00000001)) {
        addpw(fs, path, password);  // Proceed with adding a password
        saveFileSystem(fileName, fs);  // Save changes
    } else {
        cerr << "Permission denied: Insufficient permissions for adding password to file: " << path << endl;
        return 1; // Exit with error
    }
    } else if (operation == "dir") {
        if (argc != 4) {
            cerr << "Usage: " << argv[0] << " <file system data file> dir <path>" << endl;
            return 1;
        }
        string path = argv[3];
        if (path == "\\") {
            path = ""; // Interpret "\\" as the root directory
        }
        dir(fs, path);
    } else if (operation == "dumpe2fs") {
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " <file system data file> dumpe2fs" << endl;
            return 1;
        }
        dumpe2fs(fs);
    } else {
        cerr << "Unknown operation: " << operation << endl;
        return 1;
    }

    return 0;
}
