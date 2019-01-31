/**
 * As in every CS skeleton, the contents of this file are
 * only a suggestion. Please feel free to change anything.
 */

#include "matcher.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * Parses pattern for next character and sets
 * necessary parameters that are referenced inside/outside
 * of this function.
 *
 * Add any additional inputs to function signature if necessary.
 */
char *parse_char(char *partial_pattern, char *target) {
    // You can use this recommended helper function, or not.
    
    return '\0';
}

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // You can use this recommended helper function, or not.
  while((*partial_line)!='\0' && (*pattern)!='\0'){
	  char next_p = *(pattern+1);
	  int escape = 0;
	  if(*pattern == '\\'){
		  if(next_p == '.' || next_p == '+' || 
		     next_p == '?' || next_p == '\\'){
			  escape = 1;
			  pattern++;
		  }
	  }
	  next_p = *(pattern+1);
          /* particular situation of pattern:
	   * 1. 'a+aaa'
	   * 2. '\.+'
	   */
	  if(next_p == '+'){
		  if(*pattern == '.' && !escape){
			  if(*partial_line=='\0'){
				  return 0;
			  }else{
				  return 1;
			  }
		  }else{
			 /* char *start = partial_line;
			  while(*start == *pattern){ // get *pattern
				  start++;
			  }
			  if(start == partial_line){ // if no *pattern 
				  return 0;
			  }
			  // prepare for next match
			  partial_line = start; 
			  pattern += 2;*/
			  

			  // solve situation 'a+aaa'
			  if(*partial_line != *pattern){
				  return 0;
			  }
			  char symbol = *pattern;
			  partial_line++;
			  pattern += 2;
			  while(*pattern == symbol && symbol != '\\'){
				  if(*partial_line != symbol || *partial_line == '\0'){
					  return 0;
				  }
				  pattern++;
				  partial_line++;
			  }
			  // extra symbol
			  while(*partial_line == symbol){
				  partial_line++;
			  }
			  
		  }
	  }
	  else if(next_p == '?'){
		 /* if(*partial_line == *pattern){
			  partial_line++;
		  }
		  pattern += 2;
		 */ //error when 'a' and 'a?a'
		    // ex: pattern a?b                                 
		    if(*partial_line == *(pattern+2)){ // b
			    partial_line++;
			    pattern += 3;
		    }else if(*partial_line == *pattern){ // ab
			    partial_line++;
			    pattern += 2;
		    }else{
			    return 0;
		    }

	  }else{
		  if(*pattern == '.' && !escape){
			  partial_line++;
			  pattern++;
			  continue;
		  }
		  if(*partial_line == *pattern){
			  partial_line++;
			  pattern++;
		  }else{
			  return 0;
		  }
	  }
  }
  if(*pattern == '\0'){
	  return 1;
  }else{
	  return 0;
  }
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 * 
 * This function is REQUIRED and is not a suggestion.
 */
int rgrep_matches(char *line, char *pattern) {

    //
    // TODO: put your code here.
    //
    if(pattern == NULL || *pattern == '\0'){
		    printf("pattern can't be null!\n");
		    exit(1);
    }
    if(line == NULL || *line == '\0'){
	    return 0;
    }
    while(*line != '\0'){
	    if(matches_leading(line, pattern)){
		    return 1;
	    }
	    line++;
    }
    return 0;
}
