#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
typedef struct {
    int id;
    char data[65535];
} Page;

void initialize_page_table(int size);
int translate_address(int virtual_address);
void update_page_table(int page_id, int frame_id);
Page *get_page(int page_id);
void load_page(int page_id, const char *data);

#endif // PAGE_TABLE_H
