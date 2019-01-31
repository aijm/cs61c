/*
 * Project 1-1: Computing a Displacement Map
 *
 * Feel free to define additional helper functions.
 */

#include "calc_depth.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Implements the normalized displacement function */
unsigned char normalized_displacement(int dx, int dy,
        int maximum_displacement) {
    double squared_displacement = dx * dx + dy * dy;
    double normalized_displacement = round(255 * sqrt(squared_displacement)
            / sqrt(2 * maximum_displacement * maximum_displacement));
    return (unsigned char) normalized_displacement;
}

/* Helper function to return the square euclidean distance between two values. */
unsigned int square_euclidean_distance(unsigned char a, unsigned char b) {
   /*
    * This is an optional helper function which you may find useful. It
    * currently has an incomplete example CUnit test to help with debugging.
    * This test is not graded and is merely for your convenience. See the spec
    * for details on how to use CUnit.
    */
    return (a-b)*(a-b);
}

/* Helper function to check if (x,y) is valid for feature patch */
int valid_pixel(int x, int y, int image_width, int image_height,
		int feature_width, int feature_height){
	return x - feature_width >= 0 && x + feature_width < image_width &&
		y - feature_height >= 0 && y + feature_height < image_height;
}
/* Helper function to compute distance between two patches*/
unsigned int patch_distance(int lx, int ly, int rx, int ry,
		unsigned char *left, unsigned char *right,
		int image_width, int image_height,
		int feature_width, int feature_height){
	if(!valid_pixel(lx,ly,image_width,image_height,feature_width,feature_height)){
		printf("invalid pixel position (%d,%d) in left image!\n",lx,ly);
		exit(1);
	}
	if(!valid_pixel(rx,ry,image_width,image_height,feature_width,feature_height)){
		printf("invalid pixel position (%d,%d) in right image!\n",rx,ry);
		exit(1);
	}
	unsigned int sum = 0;
	int x_off = 0;
	int y_off = 0;
	/* sum distance for all pixels in the patch*/
	for(y_off = -feature_height;y_off <= feature_height;y_off++)
		for(x_off = -feature_width;x_off <= feature_width; x_off++){
			unsigned char pixel_l = *(left + (ly+y_off)*image_width+lx+x_off);
			unsigned char pixel_r = *(right+ (ry+y_off)*image_width+rx+x_off);
			sum += square_euclidean_distance(pixel_l,pixel_r);
		}
	return sum;

}
/* Helper function to find the best match position */
void best_match(int lx, int ly, int *rx, int *ry, unsigned char *displacement,
		unsigned char *left, unsigned char *right,
		int image_width, int image_height,
		int feature_width, int feature_height, int maximum_displacement){
	
	*rx = lx;
	*ry = ly;
	*displacement = 0;
	unsigned int min_distance = patch_distance(lx,ly,lx,ly,left,right,
											image_width,image_height,
											feature_width,feature_height);
	
	int minx = lx - maximum_displacement;
	int maxx = lx +  maximum_displacement;
	int miny = ly - maximum_displacement;
	int maxy = ly + maximum_displacement;
	// valid region for matching
	minx = (minx >= feature_width) ? minx : feature_width;
	maxx = (maxx <= image_width - feature_width -1) ? maxx : image_width - feature_width -1;
	miny = (miny >= feature_height) ? miny : feature_height;
	maxy = (maxy <= image_height - feature_height -1) ? maxy : image_height - feature_height -1;
	
	int j = 0;
	int i = 0;
	for(j = miny;j <= maxy; j++){
		for(i = minx;i <= maxx; i++){
			unsigned int curr_distance = patch_distance(lx,ly,i,j,left,right,
											image_width,image_height,
											feature_width,feature_height);
			if(curr_distance < min_distance){
				*rx = i;
				*ry = j;
				*displacement = normalized_displacement(abs(*rx-lx),abs(*ry-ly),maximum_displacement);
				min_distance = curr_distance;
			}else if(curr_distance == min_distance){
				/* Ties in the Euclidean Distance should be won by
				 the one with the smallest resulting normalized displacement 
				*/
				unsigned char curr_displacement = normalized_displacement(abs(i-lx),abs(j-ly),maximum_displacement);
				if(curr_displacement < *displacement){
					*rx = i;
					*ry = j;
					*displacement = curr_displacement;
				}
			}
					 
		}
	}
}
void calc_depth(unsigned char *depth_map, unsigned char *left,
        unsigned char *right, int image_width, int image_height,
        int feature_width, int feature_height, int maximum_displacement) {
    /* YOUR CODE HERE */
	int x = 0;
	int y = 0;
	for(y = 0;y < image_height;y++){
		for(x = 0;x < image_width;x++){

			if(!valid_pixel(x,y,image_width,image_height,feature_width,feature_height)){
				// if pixel is in invalid region, set to 0(infinity)
				*(depth_map + y*image_width+x) = 0;
				continue;
			}

			int match_x = x;
			int match_y = y;
			/* find best match in right image */
			unsigned char *depth_map_ptr = depth_map + y*image_width+x;
			best_match(x,y,
			           &match_x,&match_y,depth_map_ptr,
					   left,right,
					   image_width,image_height,
					   feature_width,feature_height,maximum_displacement);
		}
	}
	
}
