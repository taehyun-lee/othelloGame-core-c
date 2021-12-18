#include "common.h"

void checkFile()
{
	FILE* file_record, * file_backup;

	file_record = fopen("record.txt", "a");
	file_backup = fopen("backup.txt", "a");

	fclose(file_record);
	fclose(file_backup);
}

bool getRecord(int(*_record)[5])
{
	FILE* file;
	char line[255];
	file = fopen("record.txt","r");
	int i = 0;

	while (fgets(line, sizeof(line), file) != NULL) {
		int j = 0;
		char* ptr = strtok(line, " ");
		while (ptr != NULL) {
			_record[i][j++] = atoi(ptr);
			ptr = strtok(NULL, " ");
		}
		i++;
		if (i >= 10) {
			fclose(file);
			return true;
		}
	}

	fclose(file);
	if (i == 0) {
		return false;
	}

	return true;
}
