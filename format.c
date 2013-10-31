/*
 * Program: format.c
 * Usage:
 * CS241 hw6
 * Author Shiying Zheng and Ben Stern
 * Mon Oct 28 23:01:59 EDT 2013
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000
#define PARAGRAPH_SIZE 10000
/*
 *returns true if standard input is on an empty line, false otherwise
 *if it encounters EOF, it returns EOF
 */
int is_empty_line(){
	int c;
	while((c=getchar())!=EOF){
		if(c=='\n'){
			ungetc(c,stdin);
			return 1;
		}
		if(c!=' '){
			ungetc(c,stdin);
			return 0;
		}
	}
	return EOF;
}

/*
 * gets the next word in the line
 * skips the next whitespaces
 * returns only a newline if it is called at the end of a line
 */
char* get_next_word(){
	int c;
	int position=0;
	char* buffer;
	char* word;
	if((buffer=(char*)malloc((BUFFER_SIZE+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
	while((c=getchar())!=EOF && c!='\n' && c!=' '){
		buffer[position]=c;
		++position;
	}
	if(c=='\n'&&position==0){
                return "\n";
        }
	while(c==' '){
               	c=getchar();
       	}
        ungetc(c,stdin);
	buffer[position]=0;
	if((word=(char*)malloc((position+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
        strcpy(word, buffer);
        free(buffer);
        return word;
}
/*
 * gets the next line
 * returns a character array with words in the line and 
 * whitespace characters to signal word boundries
 * if it encounters EOF, it stops
 */
char* get_next_line(){
	char* buffer;//holds all the words so far
	char* line;
	char* word;	
	if((buffer=(char*)malloc((BUFFER_SIZE+1)*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
	buffer[0]=0;
	word=get_next_word();
	while(strcmp(word,"\n")){
		strcat(buffer,word);
		strcat(buffer," ");
		free(word);
		word=get_next_word();
	}
	if((line=(char*)malloc((strlen(buffer))*sizeof(char)))==NULL) fprintf(stderr,"out of memory");
	strcpy(line,buffer);
	free(buffer);
	return line;
}
/*
 * Reads input from standard input and returns the next paragraph
 */
char* get_next_paragraph(){
	char *c;
	int position=0;
	char *paragraph;
	int b;
	int h;
	char* line;
	if ((c=(char *)malloc(sizeof(char)*PARAGRAPH_SIZE))==NULL) fprintf(stderr, "out of memory");
	c[0]=0;
	while ((b=is_empty_line())!=EOF&&!b){
		line=get_next_line();
		strcat(c,line);
		position+=strlen(line);
		free(line);
	}
	c[position]=0;
	if((paragraph=(char*)malloc(sizeof(char)*(position+1)))==NULL)  fprintf(stderr, "out of memory");
	strcpy(paragraph,c);
	free(c);
	return paragraph;
}
/*
 * print one paragraph formatted left aligned
 * the paragraph must have a null character at the end
 */
void format_left_align(char* par, int width){
	char exit=0;//tells the loop when to exit
	char* word=par;//this pointer is inside paragraph, and is moved every time we reach a new word
	char* word_buffer;//holds a word before we figure out how long it is.
	char* line_buffer;//holds a line before printing
	if((word_buffer=malloc(BUFFER_SIZE*sizeof(char)))==NULL) fprintf(stderr,"Out of memory");
	if((line_buffer=malloc(width+1*sizeof(char)))==NULL) fprintf(stderr,"Out of memory");
	line_buffer[0]=0;
	int line_position=0;//tells us how many characters we have already put in our line
	int position=0;//the position inside word. If position is 0 we are at the beginning of a new word.
	//gets reset to 0 every time we hit a space
	int bufpos=0;
	int start_of_par=1;
	while(!exit){
		word_buffer[bufpos]=word[position];
		if(word[position]==' '||word[position]==0){//word is finished
			word_buffer[bufpos]=0;//make word_buffer a string
			if(line_position+position>width){
				strcat(line_buffer,"\n");//if the next word would overflow the line, put a newline on
				printf("%s",line_buffer);
				line_position=0;
				line_buffer[0]=0;
			}
			else if (!start_of_par) {
				strcat(line_buffer," ");
				line_position++;
			}
			strcat(line_buffer,word_buffer);//put the word onto line_buffer. It has either a space or a null char at the end.
			line_position+=position;
			if(word[position]==' '){
				word+=position+1;//make word be the next word in the paragraph
				position=0;//reset position
				bufpos=0;
			}
			else{
				exit=1;//because we will have hit the end of paragraph
				printf("%s\n",line_buffer);
			}
			start_of_par=0;
		}
		else {
//			printf("meow");
			++bufpos;
			++position;
//			printf("position is %d\n", position);
		}
	}
	free(word_buffer);
}
/*
 * print one paragraph formatted right aligned
 */
void format_right_align(char* par, int width){
        //TODO not implemented yet
}
/*
 * print one formatted paragraph justified.
 */
void format_justified(char* par, int width){
        //TODO not implemented yet
}

/*
 * format one paragraph in the correct mode, assuming words are 
 * seperated by spaces
 * The format functions should print the formatted paragraph.
 */
void format_paragraph(char* par,char mode, int width){
        if(mode=='l') format_left_align(par,width);
	else if(mode=='r') format_right_align(par,width);
	else if(mode=='j') format_justified(par,width);
}
int main(){
	char* meow=get_next_paragraph();
//	printf("%s", meow);
	format_paragraph(meow,'l',50);
}

