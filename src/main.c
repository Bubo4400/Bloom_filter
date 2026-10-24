#include "bloom_filter.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void trim(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    while ((unsigned char)str[start] == ' ')
        start++;

    while (end > start && (unsigned char)str[end] == ' ')
        end--;

    str[end + 1] = '\0';
    if (start > 0)
        memmove(str, str + start, end - start + 1);
}

static int get_input(char *input, size_t size)
{
    printf("Please enter the item: ");
    if (fgets(input, size, stdin) == NULL)
        return 0;

    input[strcspn(input, "\n")] = '\0';

    return 1;
}

int main(void)
{
    printf("Homemade Bloom_filter\n");
    char input[128] = "";
    while (strcmp(input, "quit") && strcmp(input, "exit"))
    {
        printf("Please enter if you would like to 'add' to the bloom, or 'get'"
               " if your item is already in it: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            return 1;

        input[strcspn(input, "\n")] = '\0';
        trim(input);

        if (!strcmp(input, "add"))
        {
            char item[128];
            if (!get_input(item, sizeof(item)))
                return 1;

            trim(item);
            if (!add_item((uint8_t *)item))
                return 1;
        }
        else if (!strcmp(input, "get"))
        {
            char item[128];
            if (!get_input(item, sizeof(item)))
                return 1;

            trim(item);
            if (is_item_in((uint8_t *)item))
                printf("Your item is probably in the list\n");
            else
                printf("Your item is definitely not in the list\n");
        }
    }

    free_array();
    return 0;
}
