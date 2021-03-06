#include <stdio.h>  //printf, scanf, puchar
#include <ctype.h>  //isdigit, isalpha, isalnum, tolower, toupper, strlen, strcat, strcmp
#include <string.h> //strlwr,  strupr, strchr, strrchr, strstr


main(int argc, char **argv)
{
	FILE *outf, *inf;
	char ch;		//new encrypted char
	char k[129];		//vetor para a shared-key
	int num;		//encrypt or decrypt
	char replace;		//replace it? yes or no?
	

	if (argc!=3) {
		printf("\nsyntax ERROR!\nerror#1\nsyntax:  command inputFile outputFile\n");
		exit(1);
	}

	if ((inf=fopen(argv[1],"rb"))==NULL) {
		printf("get info ERROR\nFile NOT found!\nerror#2");
		exit(2);
	}


	if (fopen(argv[2],"rb")!=0) {
		
		printf("\nThere already is a file named \"%s\".\nDo you wanna replace it?\n",argv[2]);
		
		do {
			printf("(y/n): ");
			scanf(" %c",&replace);
			fflush(stdin);
		}
		while (tolower(replace)!='y' && tolower(replace)!='n');
		
		if (tolower(replace)=='n') {
			printf("\nOperation aborted...\n");
			exit(4);
		}
	}


	if ((outf=fopen(argv[2],"wb"))==NULL) {
		printf("create file ERROR\nerror#3");
		exit(3);
	}


	printf("\n\tChoose an option:\n\n");
	printf("0- Encrypt\n");
	printf("1- Decrypt\n\n");
	do {
		printf(">");
		scanf(" %d",&num);
		//scanf("%*s"); //read and ignore the value
		//getchar(); //read and ignore the value
		fflush(stdin); //works better, bug fixer
	}
	while (num!=0 && num!=1);


	printf("\nShared-key: ");
	fflush(stdin);
	gets(k);
	printf("\n");
	

	//XXXXXXXXXXXXXXXXXX ENCRYPT XXXXXXXXXXXXXXXX
	
	int i,j,n=0;
	//i- char position from message (to be encrypted/decrypted)
	//j- helper to shift current char, then jump from "z" to "a" and vice versa
	//n- char position from sharedKey.

	if (num==0) {	//encrypt
		
		while( (ch=fgetc(inf))!=EOF ) {
			
			if (k[n]=='\0')	//se char da key é nulo entao começa de novo (na primeira posicao do vetor key)
				n=0;

			if (isalpha(ch)) {
			
				for(j=1; j<=( (int)toupper(k[n]) -65 ); j++) {	//**1** incrementar ASCII do char atual da messsage
					if (toupper(ch)=='Z')
						if (ch>96 && ch<123)
							ch='a'-1;
						else 
							ch='A'-1;
					ch++;								//**1**
				}
			n++;	// char atual ENCRIPTADA, incrementar posicao da key para determinar quantos valores aumentar a char da message
			}
			fputc(ch,outf);
		}
	
	printf("Encryption file completed!");
	}

	else  {	//decrypt
		
		while( (ch=fgetc(inf))!=EOF ) {
			if (k[n]=='\0')	//se char da key é nulo entao começa de novo (na primeira posicao do vetor key)
				n=0;

			if (isalpha(ch)) {

				for(j=1; j<=( (int)toupper(k[n]) -65 ); j++) //**1** incrementar ASCII do char atual da messsage
				{
					if (toupper(ch)=='A')
						if (ch>96 && ch<123)
							ch='z'+1;
						else 
							ch='Z'+1;
					ch--;								//**1**
				}
			n++;	// char atual ENCRIPTADA, incrementar posicao da key para determinar quantos valores aumentar a char da message
			}
			fputc(ch,outf);
		}
	
	printf("Decryption file completed!");
	}

	fclose(inf);
	fclose(outf);

	puts("\n\n\nEncoded using the Vigenere Cipher encryption scheme\nCoded by prtpereira\n\n");

}
