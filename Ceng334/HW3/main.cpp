#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "ext2fs.h"

#define BOOT_SECTOR_SIZE 1024

int blockCount;
std::vector<ext2_block_group_descriptor*> biginodetable;
ext2_super_block* sb;

uint8_t* read_image(const char* image_path, size_t* size) {
    int fd = open(image_path, O_RDONLY);
    struct stat st;
    if (fstat(fd, &st) < 0)  exit(EXIT_FAILURE);


    *size = st.st_size;
    uint8_t* buffer = (uint8_t*)malloc(*size);
    if (buffer == NULL) exit(EXIT_FAILURE);
 
    if (read(fd, buffer, *size) != *size) exit(EXIT_FAILURE);
    close(fd);
    return buffer;
}

void print_directory_tree(uint8_t* image, ext2_inode* inode, int depth, int block_size, int inode_size, uint32_t inode_table_block, int curgr);

void PrintBlock(uint8_t* image, uint32_t block, int depth, int block_size, int inode_size, uint32_t inode_table_block,  int curgr) {
    ext2_dir_entry* entry = (ext2_dir_entry*)(image + block * block_size);
    while ((uint8_t*)entry < image + (block + 1) * block_size && entry->inode != 0) {
        std::string name(entry->name, entry->name_length);
        for (int i = 0; i < depth; i++) {
            if (name != "." && name != "..") std::cout << "-";
        }
        if (name != "." && name != "..") std::cout << " ";
        if (name != "." && name != "..") std::cout << name;
        if (entry->file_type == EXT2_D_DTYPE && name != "." && name != "..") {
            std::cout << "/";
        }
        if (name != "." && name != "..") std::cout << std::endl;

        if (entry->file_type == EXT2_D_DTYPE && name != "." && name != "..") {
            int curgr2 = (entry->inode - 1) / sb->inodes_per_group; // new inode is in another group
            int offset = (entry->inode - 1) % sb->inodes_per_group;
            ext2_inode* child_inode = (ext2_inode*)(image + biginodetable[curgr2]->inode_table * block_size + offset * inode_size);
            print_directory_tree(image, child_inode, depth + 1, block_size, inode_size, biginodetable[curgr2]->inode_table, curgr2);
        }
        entry = (ext2_dir_entry*)((uint8_t*)entry + entry->length);
    }
}

void PrintIndirect(uint8_t* image, uint32_t block, int depth, int block_size, int inode_size, uint32_t inode_table_block, int level, int curgr) {
    uint32_t* block_pointers = (uint32_t*)(image + block * block_size);
    for (int i = 0; i < block_size / sizeof(uint32_t); i++) {
        if (block_pointers[i] == 0) continue;

        if (level == 1) {
            PrintBlock(image, block_pointers[i], depth, block_size, inode_size, inode_table_block,  curgr);
        }
        else {
            PrintIndirect(image, block_pointers[i], depth, block_size, inode_size, inode_table_block, level - 1,  curgr);
        }
    }
}

void print_directory_tree(uint8_t* image, ext2_inode* inode, int depth, int block_size, int inode_size, uint32_t inode_table_block, int curgr) {
    for (int i = 0; i < EXT2_NUM_DIRECT_BLOCKS; i++) {
        if (inode->direct_blocks[i] != 0) {
            PrintBlock(image, inode->direct_blocks[i], depth, block_size, inode_size, inode_table_block,  curgr);
        }
    }
    if (inode->single_indirect != 0) {
        PrintIndirect(image, inode->single_indirect, depth, block_size, inode_size, inode_table_block, 1,  curgr);
    }
    if (inode->double_indirect != 0) {
        PrintIndirect(image, inode->double_indirect, depth, block_size, inode_size, inode_table_block, 2,  curgr);
    }
    if (inode->triple_indirect != 0) {
        PrintIndirect(image, inode->triple_indirect, depth, block_size, inode_size, inode_table_block, 3, curgr);
    }
}

int main(int argc, char** argv) {

    const char* image_location = argv[1];
    const char* data_identifier = argv[2];

    size_t image_size;
    uint8_t* image = read_image(image_location, &image_size);

    sb = (ext2_super_block*)(image + EXT2_BOOT_BLOCK_SIZE);
    int block_size = EXT2_UNLOG(sb->log_block_size);

    ext2_block_group_descriptor* bgd = (ext2_block_group_descriptor*)(image + EXT2_BOOT_BLOCK_SIZE + EXT2_SUPER_BLOCK_SIZE);
    uint32_t inode_table_block = bgd->inode_table;

    blockCount = sb->block_count / sb->blocks_per_group;
    for (int k = 0; k < blockCount; k++) {
        biginodetable.push_back(bgd + k);
    }

    
    for (int k = 0; k < blockCount; k++) {
        ext2_inode* inode = (ext2_inode*)(image + biginodetable[k]->inode_table * block_size);
        uint8_t* inodeBitmap = image + biginodetable[k]->inode_bitmap * block_size;
        uint8_t* blockBitmap = image + biginodetable[k]->block_bitmap * block_size;

        for (int j = 0; j < sb->inodes_per_group; j++) {
            if (inode->deletion_time == 0 && inode->link_count != 0 || (k==0 && j<12)) {
                inodeBitmap[j / 8] |= (1 << (j % 8));
                
            }
            inode = (ext2_inode*)((uint8_t*)inode + sb->inode_size);
        }
    }

    
    int fd = open(image_location, O_RDWR);
    if (fd < 0) {
        
        exit(EXIT_FAILURE);
    }

    for (int k = 0; k < blockCount; k++) {
        uint8_t* inodeBitmap = image + biginodetable[k]->inode_bitmap * block_size;
        uint8_t* blockBitmap = image + biginodetable[k]->block_bitmap * block_size;

        if (lseek(fd, biginodetable[k]->inode_bitmap * block_size, SEEK_SET) < 0) exit(EXIT_FAILURE);
        if (write(fd, inodeBitmap, block_size) != block_size)  exit(EXIT_FAILURE);
   

        if (lseek(fd, biginodetable[k]->block_bitmap * block_size, SEEK_SET) < 0)  exit(EXIT_FAILURE);
        

    }

    close(fd);

    ext2_inode* root_inode = (ext2_inode*)(image + inode_table_block * block_size + (EXT2_ROOT_INODE - 1) * sb->inode_size);
    std::cout << "- root/" << std::endl;
    print_directory_tree(image, root_inode, 2, block_size, sb->inode_size, inode_table_block, 0);

    free(image);

    return 0;
}

