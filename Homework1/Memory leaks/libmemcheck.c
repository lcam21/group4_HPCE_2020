
void *malloc(size_t size){
	mallocTotal++;
}

void free(void *ptr){
	freeTotal++;
}
	