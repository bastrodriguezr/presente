#include <stdio.h>
#include "files.h"

int file_exist(){
    FILE *file;
    if((file = fopen(SCORE_FILE_NAME, "r"))){
        fclose(file);
        return 1;
    }
    return 0;
}

void file_initialize(){
    FILE *file;
    file = fopen(SCORE_FILE_NAME, "w");
    fprintf(file, "Hiscore = %d", 0);
    fclose(file);
}

int get_hiscore(){
    int hiscore = 0;
    if(file_exist()){
        FILE *file;
        file = fopen(SCORE_FILE_NAME, "r");
        fscanf(file, "Hiscore = %d", &hiscore);
        fclose(file);
        return hiscore;
    }
    file_initialize();
    return hiscore;
}

void hiscore_update(int new_score){
    FILE *temp_file;
    temp_file = fopen(TEMP_FILE_NAME, "w");
    fprintf(temp_file, "Hiscore = %d", new_score);
    fclose(temp_file);
    remove(SCORE_FILE_NAME);
    rename(TEMP_FILE_NAME, SCORE_FILE_NAME);
}
