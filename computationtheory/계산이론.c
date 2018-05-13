#define PCRE2_CODE_UNIT_WIDTH 8

#include "pcre2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage: [%s] [input path]\n", argv[0]);
		return 0;
	}
	pcre2_code *re;
	pcre2_match_data *match_data;
	PCRE2_SIZE erroffset, *ovector;
	int errorcode;
	int rc;
	char strTemp[255];

	FILE *rfp = NULL;
	FILE *wfp = NULL;

	PCRE2_SPTR pattern = (PCRE2_SPTR)"[0-9]{2}(0[1-9]|1[0-2])(0[1-9]|[1,2][0-9]|3[0,1])\\s-\\s[1-4][0-9]{6}"; // write regular expression here

	if (rfp = fopen(argv[1], "r"))
	{
		wfp = fopen("output.txt", "w+");

		while (!feof(rfp))
		{
			fgets(strTemp, sizeof(strTemp), rfp);
			PCRE2_SPTR input = (PCRE2_SPTR)strTemp;

			re = pcre2_compile(pattern, -1, 0, &errorcode, &erroffset, NULL);

			if (re == NULL)
			{
				PCRE2_UCHAR8 buffer[120];
				(void)pcre2_get_error_message(errorcode, buffer, 120);
				/* Handle error */
				return 0;
			}

			match_data = pcre2_match_data_create(20, NULL);
			rc = pcre2_match(re, input, -1, 0, 0, match_data, NULL);

			if (rc <= 0)
				printf("No match\n");
			else
			{/*
				ovector = pcre2_get_ovector_pointer_8(match_data);
				printf("Match succeeded at offset %d\n", (int)ovector[0]);*/
				int arr[16];
				for (int j = 0; j < 16; j++) {
					arr[j] = strTemp[j] - 48;
				}
				int twoyear= 10*arr[0]+arr[1] ;
				int year;
				int month = 10*arr[2]+arr[3] ;
				int day =  10*arr[4]+arr[5] ;
				int last = arr[15];
				if (twoyear >= 18) {
					year = 1900 + twoyear;
				}
				else {
					year = 2000 + twoyear;
				}
				int sum = 2 * arr[0] + 3 * arr[1] + 4 * arr[2] + 5 * arr[3] + 6 * arr[4] + 7 * arr[5] + 8 * arr[9] + 9 * arr[10] + 2 * arr[11] + 3 * arr[12] + 4 * arr[13] + 5 * arr[14];
				int remainder = sum % 11;
				if (remainder == 1 | remainder == 0) {
					remainder += 10;
				}
				int checksum = 11 - remainder;
				int yeargender = 0;
				if (year >= 2000&&(arr[9]==3|arr[9]==4)) {
					yeargender = 1;
				}
				if (year < 2000 && (arr[9] == 1 | arr[9] == 2)) {
					yeargender = 1;
				}
				if (yeargender == 1) {
					if (checksum == arr[15]) {

						if (month == 2) {
							if (year % 4 == 0) {

								if (day > 29 | day < 1) {
									printf("No match\n");
								}
								else {

									printf("Match!!^^\n");
									for (int i = 0; i < 16; i++) {
										if (i != 6 && i != 7 && i != 8) {
											strTemp[i] = '*';
										}
									}
								}
							}
							else {
								if (day > 28 | day < 1) {
									printf("No match\n");
								}
								else {
									printf("Match!!^^\n");
									for (int i = 0; i < 16; i++) {
										if (i != 6 && i != 7 && i != 8) {
											strTemp[i] = '*';
										}
									}
								}
							}
						}
						else if (month == 1 | month == 3 | month == 5 | month == 7 | month == 8 | month == 10 | month == 12) {
							if (day > 31 | day < 1) {
								printf("No match\n");
							}
							else {
								printf("Match!!^^\n");
								for (int i = 0; i < 16; i++) {
									if (i != 6 && i != 7 && i != 8) {
										strTemp[i] = '*';
									}
								}
							}

						}
						else {
							if (day > 30 | day < 1) {
								printf("No match\n");
							}
							else {
								printf("Match!!^^\n");
								for (int i = 0; i < 16; i++) {
									if (i != 6 && i != 7 && i != 8) {
										strTemp[i] = '*';
									}
								}
							}
						}

					}
					else {
						printf("No match\n");
					}
				}
				else {
					printf("No match\n");
				}
			}

			if (wfp != NULL)
			{
				fputs(strTemp, wfp);
			}

		}
		fclose(wfp);
		fclose(rfp);

		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
	}
	else
	{
		printf("no file found\n");
		return 0;
	}
}
