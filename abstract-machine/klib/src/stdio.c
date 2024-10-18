#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
	
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  //panic("Not implemented");
  	int count = 0;
  	while(*fmt){
		if(*fmt == '%'){
			fmt++;
			switch(*fmt){
				case 'd':
					char *num_d = (char *)va_arg(ap, int);
					*out++ = *num_d++;
					count++;
					fmt++;
					break;
				case 's':
					char *str = (char *)va_arg(ap, char *);
                    			while (*str) {
                        			*out++ = *str++;
						count++;
                    			}
					fmt++;
                    			break;
                		case 'c':
					char c = (char)va_arg(ap, int);
					*out++ = c;
					count++;
					fmt++;
					break;
			/*	case 'f'://用double直接可以把float也包含了
					double num_f = va_arg(ap, double);
					while(num_f == 0){
						*out++ = 
					}
					fmt++;
					count++;
					break;
			*/	default:
					*out++ = '%';
					*out++ = *fmt++;
					count+=2;
					break;
			}
		}
		else{
			*out++ = *fmt++;
			count++;
		}
	}
	*out = '\0';
	return count;
}

int sprintf(char *out, const char *fmt, ...) {
  //panic("Not implemented");
	va_list args;
    	va_start(args, fmt);
    	int result = vsprintf(out, fmt, args);
    	va_end(args);
    	return result;

}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");


}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
	
  panic("Not implemented");
}

#endif
