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

#include "sdb.h"
#include "utils.h"
//监视点数量
#define NR_WP 32

typedef struct watchpoint {
  int NO;// 监视点序号
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  bool flag; //判断是否使用
  char *expression;
  int old_value;
} WP;//所有的监视点

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;//head保存使用中的监视点, free_保存空闲的监视点结构

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

 /*TODO: Implement the functionality of watchpoint */
WP* new_wp(){//从free_链表中返回一个空闲的监视点结构
  Assert(free_ != NULL, "There is no free monitoring point returned in the free_ linked list");
  WP* wp = free_;
  free_=free_->next;
  wp->next = head;
  head = wp;
  return head;
}
   

void free_wp(int no){//把使用的监视点变成空闲的监视点 
  WP *p = head;
  WP *q = NULL;// 保存节点的中间变量
  bool success = false;
  if(head == NULL){
    Log("Don't have any watchpoint!");
    assert(0);
  }
  else{
    if(p->NO == no){//第一个就是要删除的
      head = head->next;
      p->old_value = 0;
      p->expression = NULL;
      p->flag = false;
      p->next = free_;
      free_ = p;
      success = true;
      printf("Success\n");
    }
    else{
      while(p->next != NULL){
        if(p->next->NO == no){
          success = true;
          p->next->old_value = 0;
	  			p->next->expression = NULL;
	 			 	p->next->flag = false;
	  			q = p->next;
	  			if(p->next->next == NULL){
	  			  p->next = NULL; 
	  			}
	  			else{
	  				p = p->next->next;
	  			}	
	  			q->next = free_;
	  			free_ = q;
	  			printf("Success\n");
				}
      	else p=p->next;
      } 
    }    
  }
  if(success == false){
    printf("Don't have this watchpoint!\n");
  } 
}

void watchpoint_print(){//打印链表
  WP *p = head;
  if(head == NULL){
    printf("Please add a watchpoint!\n");
    return;
  }
  else{
    printf("%-15s%-15s\n","NO","express");
    while(p!= NULL){
      printf("%-15d%-15s\n",p->NO,p->expression);
      p = p->next;
    }
  }
}

//watchpoint_delete用free_wp代替

void watchpoint_create(char *args, word_t res){
   WP* p =  new_wp();
   p -> expression = strdup(args);
   p -> old_value = res;
   printf("Create watchpoint No.%d success.\n", p -> NO);
}


void checkWatchPoint(){
  WP* freeWP = head;
  word_t newValue;
  bool success = true;
  while (freeWP != NULL){
    Assert(freeWP->expression != NULL, "There are no express in watchpoint");
    newValue = expr(freeWP->expression, &success);
    Assert(success == true, "The error express was put into watchpoint");
    if (newValue != freeWP->old_value){
      nemu_state.state = NEMU_STOP;
      printf("Hardware watchpoint %d: %s\n\n", freeWP->NO, freeWP->expression);
      Log("");
      printf("Old value = %u\n", freeWP->old_value); 
      printf("New value = %u\n", newValue);freeWP->old_value = newValue;
    }
    freeWP = freeWP->next;
  }
}
