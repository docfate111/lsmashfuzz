#include "lsmash.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Usage: %s file", argv[0]);
		return 0;
	}
	lsmash_root_t *root = lsmash_create_root();
	if(!root){ printf("root is NULL"); exit(0); }
	lsmash_file_parameters_t file_param = { 0 };
	if(lsmash_open_file(argv[1], 1, &file_param)<0){
		exit(0);
	}
	int dump_box = 1;
	if( dump_box )
        	file_param.mode |= LSMASH_FILE_MODE_DUMP;
	lsmash_file_t *file = lsmash_set_file( root, &file_param );
	if(!file){ printf("Failed to set file"); exit(0); }
	if( lsmash_read_file( file, &file_param ) < 0 ){ printf("Failed to read file"); exit(0); }
	/*if (dump_box) {
		if(lsmash_print_movie(root, "-")<0){
			printf("error printing movie");
		}
	}*/
	uint32_t id = lsmash_create_track(root, ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK);
	lsmash_delete_track(root, id);
	if(lsmash_activate_file(root, file)<0){
		printf("Error activating file");
		exit(0);
	}
	lsmash_box_t *box = lsmash_file_as_box(file);
	if(!box){
		printf("Error converting file to box");
		exit(0);
	}
	if(lsmash_add_box(box, box)<0){
		printf("Error adding box to itself");
		exit(0);
	}
	lsmash_destroy_box(box);
	lsmash_close_file(&file_param);
	lsmash_destroy_root( root );
	return 0;
}
