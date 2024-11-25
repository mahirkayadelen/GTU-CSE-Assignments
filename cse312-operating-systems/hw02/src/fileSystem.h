#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <iostream>
#include <fstream> // for file operations
#include <vector>
#include <string> 
#include <cstring> // for strcmp
#include <ctime> // for time()
#include <bitset> // for binary representation to permissions
#include <iomanip>


// Constants
#define MAX_FS_SIZE (4 * 1024 * 1024) // 4 MB default for 1KB block size
#define MAX_FILES 128
#define MAX_FILENAME 255
#define FAT_ENTRY_FREE 0x0000  // Represents a free block
#define FAT_ENTRY_EOF 0xFFF    // Represents the end of a file

using namespace std;

// Structure for Super Block
struct SuperBlock {
    unsigned int blockSize;    // Block size in bytes
    unsigned int totalBlocks;  // Total number of blocks
    unsigned int freeBlocks;   // Number of free blocks
};

// Structure for Directory Entry
struct DirectoryEntry {
    char name[MAX_FILENAME]; // Keep file/dir name
    unsigned int size; 
    unsigned char ownerPermissions; // permissions default : 0b00000011 -> 3 -> +rw
    time_t lastModification; // modification time
    time_t creation;
    char password[32]; // default '\0' null
    unsigned short startBlock; // Keeps first block of the file/dir
    unsigned short parentBlock; // Keep the parent directory's start block
    bool isDirectory; // Indicate if it's a directory
};

// Structure for File Allocation Table Entry
struct FATEntry {
    unsigned short nextBlock; // 16 bit
};

// Structure for File System
struct FileSystem {
    SuperBlock superBlock;
    std::vector<DirectoryEntry> rootDirectory;
    std::vector<FATEntry> fat;
    std::vector<std::vector<char>> data;
};

#endif // FILE_SYSTEM_H
