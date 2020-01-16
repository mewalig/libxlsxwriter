/*
 * Example of using libxlsxwriter for writing large files in constant memory
 * mode.
 *
 * Copyright 2014-2018, John McNamara, jmcnamara@cpan.org
 *
 */

#include "xlsxwriter.h"

int main() {

    lxw_row_t row;
    lxw_col_t col;
    lxw_row_t max_row = 1000;
    lxw_col_t max_col = 50;

    /* Set the worksheet options. */
    lxw_workbook_options options = {.constant_memory = LXW_TRUE,
                                    .sst_memory = 16384,
                                    .tmpdir = NULL};

    const char *strings[] = {
      "Lorem", "ipsum", "dolor", "sit", "amet,", "consectetur", "adipiscing", "elit,", "sed", "do", "eiusmod", "tempor", "incididunt", "ut", "labore", "et", "dolore", "magna", "aliqua.", "Ut", "enim", "ad", "minim", "veniam,", "quis", "nostrud", "exercitation", "ullamco", "laboris", "nisi", "ut", "aliquip", "ex", "ea", "commodo", "consequat.", "Duis", "aute", "irure", "dolor", "in", "reprehenderit", "in", "voluptate", "velit", "esse", "cillum", "dolore", "eu", "fugiat", "nulla", "pariatur.", "Excepteur", "sint", "occaecat", "cupidatat", "non", "proident,", "sunt", "in", "culpa", "qui", "officia", "deserunt", "mollit", "anim", "id", "est", "laborum", NULL
    };
    int string_index = 0;

    /* Create a new workbook with options. */
    lxw_workbook  *workbook  = workbook_new_opt("constant_memory_with_sst.xlsx", &options);
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    lxw_worksheet *worksheet2 = workbook_add_worksheet(workbook, NULL);

    const char *string;
    int counter = 0;
    char counter_string[50];
    for (row = 0; row < max_row; row++) {
        for (col = 0; col < max_col; col++) {
            // worksheet_write_number(worksheet, row, col, 123.45, NULL);
            string = strings[string_index];
            if(!strings[++string_index])
                string_index = 0;

            snprintf(counter_string, sizeof(counter_string), "count: %i", ++counter);
            if(row % 2) {
                worksheet_write_string(worksheet, row, col, string, NULL);
                worksheet_write_string(worksheet2, row, col, counter_string, NULL);
            } else {
                worksheet_write_string(worksheet, row, col, counter_string, NULL);
                worksheet_write_string(worksheet2, row, col, string, NULL);
            }
        }
    }

    return workbook_close(workbook);
}
