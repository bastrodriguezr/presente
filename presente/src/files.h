#ifndef FILES_H
#define FILES_H

#define SCORE_FILE_NAME "../scores/hiscore.txt"
#define TEMP_FILE_NAME "../scores/temp_file_name.txt"


//Check if the file "hiscore.txt" exist
int file_exist();

//Initialize the file "hiscore.txt"
void file_initialize();

//Return hiscore in "hiscore.txt"
int get_hiscore();

//Update the highest score
void hiscore_update(int new_score);


#endif