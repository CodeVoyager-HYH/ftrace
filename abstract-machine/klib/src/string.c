#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  //panic("Not implemented");
	assert(s);
	size_t len = 0;
	while(*s != '\0'){
  		len++;
  		s++;
  	}
  	return len;
}

char *strcpy(char *dst, const char *src) {
  //panic("Not implemented");
	assert(src != NULL && dst != NULL);	
	while(*src != '\0'){
		*dst++ = *src++;
	}
	*dst = '\0';
	
	return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  //panic("Not implemented");
	assert(src != NULL && dst != NULL);
	size_t i ;
	
	for(i = 0; i < n && *src != '\0'; i++){
		*dst++ = *src++;
	}
	for(; i < n; i++){
		*dst = '\0';
	}
	return dst;
}

char *strcat(char *dst, const char *src) {
  //panic("Not implemented");
	assert(src != NULL && dst != NULL);
	size_t i = strlen(dst);
	while(*src != '\0'){
		dst[i++] = *src++;
	}
	dst[i] = '\0';
	
	return dst;
}

int strcmp(const char *s1, const char *s2) {
  //panic("Not implemented");
	assert(s1 != NULL && s2 != NULL);

	while(*s1 != '\0' && *s2 != '\0' && (*s1 != *s2)){
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int strncmp(const char *s1, const char *s2, size_t n) {
  //panic("Not implemented");
	assert(s1 != NULL && s2 != NULL);
	int a1 = 0;
	int a2 = 0;
	size_t i = 0;
	while(*s1 != '\0' && *s2 != '\0' && (*s1 != *s2) && i < n){
		a1 = (int)s1[i]	;
		a2 = (int)s2[i] ;
		i++;
	}
	return (a1 - a2);


}

void *memset(void *s, int c, size_t n) {
  //panic("Not implemented");
  	assert(s != NULL);
	char *str = s; 
	while(n--){
		*str++ = (char)c;
	}
	return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  //panic("Not implemented");
  //当src位于dest左侧时（也就是src<dest时）就用从后往前的复制方式。反之，就用从前往后的复制方式
	void* ret = dst;//保存目的空间地址
	assert(dst && src);//断言判断
	if (dst < src){
		while (n--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
	    	}
		
	}
	else{
		while (n--){
			*((char*)dst + n) = *((char*)src + n);
			
		}
	}
	return ret;
}

void *memcpy(void *out, const void *in, size_t n) {
//  panic("Not implemented");
	assert(out && in);
	char *output = out;	
	const char *input  = in;
	for(size_t i = 0; i < n; i++){
		output[i] = input[i];
	}
	return output;
}

int memcmp(const void *s1, const void *s2, size_t n) {
//  panic("Not implemented");
	assert(s1 && s2);
	size_t a1 = 0;//a1和a2是记录ascii码
	size_t a2 = 0;
	size_t i = 0;
	const char *ss1 = s1;
	const char *ss2 = s2;
	while(*ss1 != '\0' && *ss2 != '\0' && (i < n)){
		a1 = (int)ss1[i];
		a2 = (int)ss2[i];
		i++;
	}
	return a1 - a2;
}

#endif
