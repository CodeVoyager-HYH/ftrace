/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
static int buf_index = 0;

static uint32_t choose(uint32_t n){
  return (uint32_t)(rand() % n);
}

static void gen(char c){
  buf[buf_index++] = c;
  buf[buf_index] = '\0';
}

static void gen_num(){
  uint32_t len = choose(10);
  if (len == (uint32_t)(0))
    len += 1;
  if (len == 1){
    gen((char)(choose(10) + '0'));
    return ;
  }
  uint32_t firstNum = choose(10);
  if (firstNum == (uint32_t)(0)){//防止首位为0
    firstNum += 1;
  }
  gen((char)(firstNum + '0'));
  uint32_t i;
  for (i = 2; i <= len; i++){
    gen((char)(choose(10) + '0'));
  }
}

static void gen_space(){
  uint32_t len = choose(11);
  uint32_t i;
  
  for (i = 1; i <= len; i++){
    gen(' ');
  }
}

static void gen_rand_op(){
  switch (choose(4))
  {
  case 0: gen('+'); break;
  case 1: gen('-'); break;
  case 2: gen('*'); break;
  default: gen('/'); break;
  }
}


static void gen_rand_expr(uint32_t n) {
  uint32_t chooseAns = choose(3);
  if (n >= 10){
    chooseAns = 0;
  }
  switch (chooseAns)
  {
  case 0://判断表达式数字前不能是 )，  
  	if(buf[buf_index-1] != ')'){
  		gen_space(); gen_num(); gen('u'); gen_space();}
  	else {
  		gen_rand_expr(n);
  	}	
   	break;
  case 1://只有+-*/后才能加括号
  	if(strchr("+-*/", buf[buf_index - 1])){
  		gen('('); gen_space(); gen_rand_expr(n + 1); gen_space(); gen(')'); 
  		}
  	else 	{
  		gen_rand_expr(n);
  	}
  	break;
  default: gen_rand_expr(n + 1); gen_space(); gen_rand_op(); gen_space(); gen_rand_expr(n + 1); break; 
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    buf_index = 0;
    gen_rand_expr(1);
	//写入代码
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);
	//把警告变成error，这样system就会返回一个不为0的数
    int ret = system("gcc -o /tmp/.expr -Wall -Werror /tmp/.code.c");
    if (ret != 0) continue;
	//创建一个管道，这个管道只能输出    
    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);
	/*pclose 函数关闭文件流 stream 所关联的管道，并等待与之关联的子进程终止。
	 *如果成功关闭管道并获取了子进程的终止状态，pclose 函数会返回子进程的终止状态；
	 *如果关闭管道或等待子进程终止失败，则返回 -1。 
	 */ 
    int result;
    int status;
    ret = fscanf(fp, "%d", &result);
    status = pclose(fp);
  
  
    if (WIFEXITED(status)){//判断退出状态，如果退出成功返回true
      if (WEXITSTATUS(status) == 136){//退出状态的状态码 ，除零是136
        continue;
      }
    }
    printf("%u %s\n", result, buf);
  }
  return 0;
}
