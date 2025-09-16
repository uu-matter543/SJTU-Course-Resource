#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *address;
FILE *external;
FILE *result_file;

struct pt_item{
    bool valid;
    int frame;
};
struct pt_item page_table[256];

struct tlb_item{
    int page;
    int frame;
};
struct tlb_item tlb[16];

char memory[128][256];

int tlb_p = 0;
int mem_p = 0;

void initialize()
{
    for (int i = 0; i < 256; i++)
    {
        page_table[i].valid = false;
        page_table[i].frame = -1;
    }
    for (int i = 0; i < 16; i++)
    {
        tlb[i].page = -1;
        tlb[i].frame = -1;
    }
    printf("Reset page table and TLB.\n");
}

int main(int argc, char **argv)
{
    address = fopen("address.txt", "r");
    external = fopen("BACKING_STORE.bin", "rb");
    result_file = fopen("result.txt", "w");
    
    initialize();
    
    int addr;
    int page;
    int offset;
    int frame;
    int visit = 0;
    int tlb_hit = 0;
    int memory_hit = 0;
    
    while(fscanf(address, "%u", &addr) != EOF)
    {
        visit++;
        page = addr>>8;
        offset = addr % 256;
        bool in_tlb = false;
        for (int i = 0; i < 16; i++)
            if (page == tlb[i].page)
            {
                tlb_hit++;
                memory_hit++;
                in_tlb = true;
                frame = tlb[i].frame;
                break;
            }
        if (!in_tlb)
        {
            bool in_page = false;
            if (page_table[page].valid)
            {
                memory_hit++;
                in_page = true;
                frame = page_table[page].frame;
                tlb[tlb_p].page = page;
                tlb[tlb_p].frame = frame;
                tlb_p = (tlb_p+1) % 16;
            }
            else
            {
                for (int i = 0; i < 256; i++)
                    if (page_table[i].frame == mem_p)
                        page_table[i].valid = false;
                for (int i = 0; i < 16; i++)
                    if (tlb[i].frame == mem_p)
                        tlb[i].page = page;
                fseek(external, page*256, SEEK_SET);
                fread(memory[mem_p], sizeof(char), 256, external);
                page_table[page].frame = mem_p;
                page_table[page].valid = true;
                frame = mem_p;
                mem_p = (mem_p+1) % 128;
            }
        }
        int phy_addr = frame * 256 + offset;
        int data = memory[frame][offset];
        fprintf(result_file, "Vir: %d, Phy: %d, Data: %d\n", addr, phy_addr, data);
    }
    printf("TLB Hit Rate: %d/%d\n", tlb_hit, visit);
    printf("Memory Hit Rate: %d/%d\n", memory_hit, visit);
}
