#include <hello1.h>

MODULE_AUTHOR("Max Podloobniy <max.podloobniy@gmail.com>");
MODULE_DESCRIPTION("Lab 4 AK");
MODULE_LICENSE("Dual BSD/GPL");

static uint myCounter = 1;

module_param(myCounter, uint, 0);
MODULE_PARM_DESC(myCounter, "Lab 4 AK\n");

static int __init my_init(void){
    pr_info("hello2 initiated!\n");
    hello_msg(myCounter);
    return 0;
}

static void __exit my_exit(void){
    pr_info("hello2 unloaded!\n");
}

module_init(my_init);
module_exit(my_exit);
