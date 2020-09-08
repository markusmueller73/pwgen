#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  
#include <string.h>

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif
#define DEFAULT_LENGTH	8
#define UPPERCASE 		0
#define LOWERCASE 		1
#define NUMBER			2
#define SPECIALCHAR		3

void print_usage ( char *exec ) {
	
	fprintf(stdout, "\nRandom Password Generator\n-------------------------\n\n");
	fprintf(stdout, "Usage:\n\n");
	fprintf(stdout, "%s [ARGUMENTS]\n\n", exec);
	fprintf(stdout, "Arguments:\n");
	fprintf(stdout, "\t-c <NB>\tlength of the password, default is %d.\n", DEFAULT_LENGTH);
	fprintf(stdout, "\t-d <NB>\tuse digits\n");
	fprintf(stdout, "\t-h     \tshow this help\n");
	fprintf(stdout, "\t-l <NB>\tuse lower case letters\n");
	fprintf(stdout, "\t-p <NB>\tamount of different passwords\n");
	fprintf(stdout, "\t-s <NB>\tuse special chars\n");
	fprintf(stdout, "\t-u <NB>\tuse upper case letters\n\n");
	fprintf(stdout, "The <NB> option is used for the amount of chars of the type or you choose 0 (NULL) to disable this type of char.\n\n");

}

int str2int ( char string[] ){
	
	if ( !string ) {
		fprintf(stderr, "Error in 'str2int()', empty parameter.\n");
		return -1;
	}
	
	int number = 0;
	int i = 0;
	int stringLen = strlen( string );
	
	while ( i < stringLen ) {
		
		int digit = string[i++] - '0';
		
		if ( digit < 0 || digit > 9 ) {
			fprintf(stderr, "Error in 'str2int()', invalid character '%c' at position '%d'\n", string[i - 1], (i - 1));
			return -i;
		}
		
		number *= 10;
		number += digit;
	}
	
	return number;
	
}

int main ( int argc , char *argv[] ) {
	
	int nbOfPwds = 1;
	int lenOfPwd = DEFAULT_LENGTH;
	
	int maxSpecials = 1;
	int maxDigits = 2;
	int maxLowerCase = 3;
	int maxUpperCase = lenOfPwd - ( maxSpecials + maxDigits + maxLowerCase );
	
	int opt = 0;
	
    while ( ( opt = getopt ( argc, argv, ":c:d:hl:n:p:s:u:" ) ) != -1 ) {
		
		switch( opt )
        {  
			case 'c':
				lenOfPwd = str2int( optarg );
				break;
            case 'd':
				maxDigits = str2int( optarg );
				break;
			case 'h':
				print_usage( argv[0] );
				return 1;
			case 'l':
				maxLowerCase = str2int( optarg );
				break;
			case 'p':
				nbOfPwds = str2int( optarg );
				break;
			case 's':
				maxSpecials = str2int( optarg );;
				break;
			case 'u':
				maxUpperCase = str2int( optarg );
				break;
            case ':':  
                fprintf(stderr, "Error in 'main()', argument needs a value\n");  
                break;  
            case '?':  
                fprintf(stderr, "Error in 'main()', unknown argument: %c\n", optopt);
				print_usage( argv[0] );
                return 1;
				
        }  
		
	}
	
	if ( ( maxUpperCase + maxLowerCase + maxDigits + maxSpecials ) > lenOfPwd ) {
		lenOfPwd = ( maxUpperCase + maxLowerCase + maxDigits + maxSpecials );
	}
	else if ( ( maxUpperCase + maxLowerCase + maxDigits + maxSpecials ) < lenOfPwd ) {
		maxLowerCase = ( lenOfPwd - ( maxDigits + maxSpecials ) ) / 2;
		maxUpperCase = lenOfPwd - ( maxSpecials + maxDigits + maxLowerCase );
	}

	fprintf(stdout, "\nRandom Password Generator\n-------------------------\n\n");
	fprintf(stdout, "Password length:\t%d\n", lenOfPwd);
	fprintf(stdout, "Capitals enabled\t[%c]\n", maxUpperCase > 0 ? 'x' : ' ');
	fprintf(stdout, "Lower case enabled\t[%c]\n", maxLowerCase > 0 ? 'x' : ' ');
	fprintf(stdout, "Digits enabled\t\t[%c]\n", maxDigits > 0 ? 'x' : ' ');
	fprintf(stdout, "Special chars enabled\t[%c]\n", maxSpecials > 0 ? 'x' : ' ');
	fprintf(stdout, "Nb. of passwords\t%d\n\n", nbOfPwds);
	
	int i, j;
	time_t t;
	
	srand((unsigned) time(&t));
	
	if ( nbOfPwds > 1 ) {
		fprintf(stdout, "Passwords:\n");
		fprintf(stdout, "----------\n\n");
	}
	else {
		fprintf(stdout, "Password:\n");
		fprintf(stdout, "---------\n\n");
	}
	
	for ( i = 1 ; i <= nbOfPwds ; i++ ) {
		
		j = 1;
		int muc = maxUpperCase;
		int mlc = maxLowerCase;
		int mds = maxDigits;
		int msc = maxSpecials;
		
		while ( j <= lenOfPwd ) {
			
			int sign = 0;
			int type = rand() % (SPECIALCHAR + 1);
			
			switch ( type ){
				case UPPERCASE:
					if ( muc > 0 ) {
						sign = rand() % ('Z'-'A') + 'A';
						muc--;
					}
					break;
				case LOWERCASE:
					if ( mlc > 0 ) {
						sign = rand() % ('z'-'a') + 'a';
						mlc--;
					}
					break;
				case NUMBER:
					if ( mds > 0 ) {
						sign = rand() % ('9'-'0') + '0';
						mds--;
					}
					break;
				case SPECIALCHAR:
					if ( msc > 0 ) {
						sign = rand() % ('/'-'!') + '!';
						msc--;
					}
					break;
				default:
					sign = '_';
					break;
			}
			
			if ( sign != 0 ) {
				fprintf(stdout, "%c", (char) sign);
				j++;
			}
			
		}
		
		fprintf(stdout, "\n");
		
	}
	
	fprintf(stdout, "\nDone!\n");
	
	return 0;
	
}