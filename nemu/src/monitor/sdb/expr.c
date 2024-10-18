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
#include <isa.h>
#include <memory/paddr.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
enum {
  TK_NOTYPE = 256, TK_EQ = 255, TK_NQ = 254, NUM = 253,
  TK_REG = 252, TK_AND = 251, TK_HEX = 250, TK_OR = 249,DEREF = 248,//指针
  TK_NEGATIVE = 247,
  /* TODO: Add more token types */

};
void NEGATIVE();
void symbol();
static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  
    {" +", TK_NOTYPE},    // spaces
    {"\\+", '+'},         // plus
    {"\\-", '-'},         // sub
    {"\\*", '*'},         // mul
    {"/", '/'},         // div

    {"\\(", '('},         //  (
    {"\\)", ')'},         //  )
    {"==", TK_EQ},    // equal
    {"\\!=", TK_NQ},	  // !=
    {"\\|\\|", TK_OR},    // ||
    {"\\&\\&", TK_AND},   // &&
    {"\\$[0-9a-zA-Z]+", TK_REG}, //register R代表寄存器
    {"0x[0-9a-fA-F]+", TK_HEX},
    {"(0u?|[1-9][0-9]*u?)",NUM},

};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {//包含token的类型和内容
  int type;
  char str[32];
} Token;

static Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

//-------------------------------make_token-----------------------
static bool make_token(char *e) {
    int position = 0;
    int i;
    regmatch_t pmatch;

    nr_token = 0;

    while (e[position] != '\0') {
        /* Try all rules one by one. */
        for (i = 0; i < NR_REGEX; i ++) {
            if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
                char *substr_start = e + position;
                int substr_len = pmatch.rm_eo;

                position += substr_len;

                /* TODO: Now a new token is recognized with rules[i]. Add codes
                 * to record the token in the array `tokens'. For certain types
                 * of tokens, some extra actions should be performed.
                 */
                Token token;
                switch (rules[i].token_type) {
                    case TK_NOTYPE:
                      break;
                    default: 
                      strncpy(token.str, substr_start, substr_len);
					            token.str[substr_len] = '\0'; 
					            token.type=rules[i].token_type;
					            tokens[nr_token++] = token;
                      break;
                }

                break;
            }
        }

        if (i == NR_REGEX) {
            printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
            return false;
        }
    }

    return true;
}
//---------------------------找主运算符-------------------------------------
word_t find_major(word_t p,word_t q)
{
  word_t ret=0;
  word_t par=0;//括号的数量
  word_t op_type=0; //当前找到的最高优先级的运算符类型
  word_t tmp_type=0; //相应运算符类型的等级
  for(word_t i = p;i <= q;i++)
  {
    //symbol();
    //数字
    if (tokens[i].type ==NUM)
    { 
      continue;
    }
 		
 		else if(tokens[i].type ==TK_HEX)
 		{
 			continue;
 		}
    else if (tokens[i].type=='(')
    {
      par++;
      continue;
    }
 		
    else if (tokens[i].type==')')
    {
      if (par==0)
      {
        return -1;
      }
      par--;
    }
    else if (par>0)
    {
      continue;
    }
    else
    {
      switch (tokens[i].type) 
      {
      case '*': case '/': tmp_type = 1; break;
      case '+': case '-': tmp_type = 2; break;
      case TK_EQ:case TK_NQ:tmp_type=3;break;
      case TK_AND:case TK_OR:tmp_type=4;break;
      case DEREF:case TK_NEGATIVE:tmp_type=5;break;
      default: assert(0);
      }
      if (tmp_type>=op_type)
      {
        op_type=tmp_type;
        ret=i;
      }
      
    }
 
  }
    if(par>0) {return -1;}
    return ret;
}

 
      
//------------------------------------指针和负数----------------------------------
void symbol() {
  int i;

  //负数
  for (i = 0; i < nr_token; i++){
    if (tokens[i].type == '-' && (i == 0 || (tokens[i - 1].type != NUM && tokens[i - 1].type != ')'))){
      tokens[i].str[0] = '-';
      tokens[i].str[1] = '\0';
      tokens[i].type = TK_NEGATIVE;
    }
  }
  //指针
  for (i = 0; i < nr_token; i++){
    if (tokens[i].type == '*' && (i == 0 ||(tokens[i - 1].type != NUM && tokens[i - 1].type != ')'))){
      tokens[i].str[0] = '*';
      tokens[i].str[1] = '\0';
      tokens[i].type = DEREF;//Log("DEREF");
    }
  }
}

//---------------------------------check_parentheses-----------------------------------
bool check_parentheses(int p, int q){
	int i,tag = 0;
  if(tokens[p].type != '(' || tokens[q].type != ')') return false; //判断p q是否为括号
  for(i = p; i <= q; i ++){    
        if(tokens[i].type == '(') tag++;
        else if(tokens[i].type == ')') tag--;
        if(tag == 0 && i < q) return false ;  //(3+4)*(5+3) 返回false
    }                              
    if( tag != 0 ) return false;   
    return true;  
}

//++++++++++++++++++++++++++++++++++++++eval+++++++++++++++++++++++++++++++++++++++++++++++++++
int eval(int p, int q){ 
 // Log("In eval");
 
  if (p > q) {//Log("p > q");
    /* Bad expression */
    printf("Error:p > q");
    assert(0);
  }
  
  else if (p == q) {//判断开头，有可能是寄存器，数字，十六进制
    
    if (tokens[p].type==NUM){//数字
       
       return atoi(tokens[p].str);
    }
    else if (tokens[p].type==TK_HEX){//十六进制
			 return strtol(tokens[p].str, NULL, 16);
    }
    else if(tokens[p].type==TK_REG){//寄存器
      word_t num;
      bool t = true;
      num = isa_reg_str2val(tokens[p].str+1, &t);
      printf("0x%x\n",num);
      return num;
    }
  }
  
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */ 
    return eval(p + 1, q - 1);
  }
  
  else if(tokens[p].type == NUM){
    //全是数字
    word_t result = 0;
    bool success = false;
    int tmp = 0;
    for(int i = 0;i<nr_token;i++){
      if(tokens[i].type == NUM){
        success = true;
      } 
      else {
        success = false;
				break;
		  }
    }
    if(success == true){
      for (int i = 0; i<nr_token; i++) {
        // 将字符转换为对应的整数，并累加到 result 中
        sscanf(tokens[i].str,"%d",&tmp);
        result = result * 10 + tmp;        
    	}
    	return result;
    }
		goto here;
  }
  
  else 
  { 
    here:
    //Log("else");
    word_t op=find_major(p,q);
    //Log("op = %s",tokens[op].str);
    int val2 = eval(op + 1, q);
    //指针
    if(tokens[op].type == DEREF){
        return paddr_read(val2,4);
      }

    int val1 = eval(p, op - 1);
      switch (tokens[op].type) {  
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/': return val1 / val2;
          if (val2 == 0){
        		printf("不能除0\n");
        		return 0;
      		}
                  
        case TK_EQ:return val1 == val2; break;//==
        case TK_NQ:return val1 != val2;  break;//!=
        case TK_AND:return val1 && val2;  break;//&&
        case TK_OR:return val1 || val2; break; // ||

        default: assert(0);
      }
    
  }

  return -1;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void NEGATIVE(){
  /*遍历tokens如果有负数则把该为的type变成空格
	 *数字变成相反数，最后跳过空格即可
	 */
	int index = 0;
	int tmp = 0;
	int a = 0, b = 0;
  for(int i = 0; i < nr_token; i++){
    if(tokens[i].type == TK_NEGATIVE){//247
      if(i+2<nr_token){//判断--1
      	if(tokens[i+1].type == TK_NEGATIVE){//--1
      		//if(i+2=nr_token) goto elseif;
      		tokens[i].type = TK_NOTYPE;//256
      		tokens[i+1].type = TK_NOTYPE;//256
      		sscanf(tokens[i+2].str,"%d",&tmp);
  	  		tmp = tmp;
  	  		a = 1;
	    		snprintf(tokens[i+2].str,sizeof(tokens[i+2].str),"%d",tmp);     
      		continue;
      	}
      }
      if(i+3<nr_token){//判断1-(-1)
        if(tokens[i+1].type == '(' && tokens[i+2].type == TK_NEGATIVE){
        	tokens[i].type = TK_NOTYPE;//256
        	tokens[i+2].type = TK_NOTYPE;//256
      		sscanf(tokens[i+3].str,"%d",&tmp);
  	  		tmp = tmp;b=1;
	    		snprintf(tokens[i+3].str,sizeof(tokens[i+3].str),"%d",tmp);     
        	continue;
        }
      }
      if(a == 0 &&b == 0) {//正常的-1+1或者1+(-1)
      	tokens[i].type = TK_NOTYPE;
      	sscanf(tokens[i+1].str,"%d",&tmp);
  	  	tmp = -tmp;
	    	snprintf(tokens[i+1].str,sizeof(tokens[i+1].str),"%d",tmp);   
      }
    }
    a=0;b=0;   
  }
  
  //移动元素组成新的tokens
/*	for(int i = 0; i < nr_token; i++){
	 Log("tokens[%d].type = %d, tokens[%d].str = %s",i,tokens[i].type,i,tokens[i].str);
	}
	printf("\n");*/
	for(int i = 0; i < nr_token; i++){
		if(tokens[i].type != TK_NOTYPE){
      tokens[index] = tokens[i];  // 移动元素      
      index++;
    }
    else continue;
  }
	
	nr_token = index;
	//Log("nr_token = %d,index = %d",nr_token,index);
  printf("\n");
}
//------------------------------------------expr-----------------------------------
word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    //Log("expr1");
    *success = false;
    printf("success is false!\n");
    return 0;
  }
  
  
  //Log("expr2");
  symbol();//标记指针和负数
  NEGATIVE();
  return eval(0,nr_token-1);
}

