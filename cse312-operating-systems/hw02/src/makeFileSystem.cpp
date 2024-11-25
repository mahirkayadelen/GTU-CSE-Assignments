#include "fileSystem.h"



void initializeFileSystem(const char* fileName, unsigned int blockSize) {
    ofstream file(fileName, ios::binary);
    if (!file) {
        cerr << "Error creating file." << endl;
        return;
    }

    // Calculate number of blocks
    unsigned int totalBlocks; 
    if(blockSize == 512)
        totalBlocks= (MAX_FS_SIZE / 2) / blockSize;
    else
        totalBlocks= MAX_FS_SIZE / blockSize;

    // Initialize Super Block
    SuperBlock superBlock;
    superBlock.blockSize = blockSize;
    superBlock.totalBlocks = totalBlocks;
    superBlock.freeBlocks = totalBlocks - 1; // one block used for super block

    // Write Super Block to file
    file.write(reinterpret_cast<const char*>(&superBlock), sizeof(SuperBlock));

    // Initialize and write FAT
    FATEntry fatEntry;
    fatEntry.nextBlock = FAT_ENTRY_FREE;  // Correctly initialize as free
    for (unsigned int i = 0; i < totalBlocks; ++i) {
        file.write(reinterpret_cast<const char*>(&fatEntry), sizeof(FATEntry));
    }

    // Initialize and write Root Directory
    DirectoryEntry emptyEntry = {0};
    for (unsigned int i = 0; i < MAX_FILES; ++i) {
        file.write(reinterpret_cast<const char*>(&emptyEntry), sizeof(DirectoryEntry));
    }

    // Initialize and write Data Blocks
    char emptyBlock[blockSize];
    memset(emptyBlock, 0, blockSize);
    for (unsigned int i = 0; i < totalBlocks; ++i) {
        file.write(emptyBlock, blockSize);
    }

    file.close();
    cout << "File system initialized in " << fileName <<  "\nBlock size: "<<  superBlock.blockSize<<endl;

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <block size (0.5 or 1) KB> <file name>" << endl;
        return 1;
    }

    string blockSizeStr = argv[1];
    const char* fileName = argv[2];

    unsigned int blockSize = 0;

    if (blockSizeStr == "0.5") {
        blockSize = 512; // 0.5 KB in bytes
    } else if (blockSizeStr == "1") {
        blockSize = 1024; // 1 KB in bytes
    } else {
        cerr << "Block size must be 0.5 or 1 KB." << endl;
        return 1;
    }

    initializeFileSystem(fileName, blockSize);

    return 0;
}
