#include <hello1.h>

MODULE_AUTHOR("Max Podloobniy <max.podloobniy@gmail.com>");
MODULE_DESCRIPTION("Lab 4 AK");
MODULE_LICENSE("Dual BSD/GPL");

struct my_data {
    struct list_head entry;
    ktime_t before;
    ktime_t after;
};

static struct list_head my_list = LIST_HEAD_INIT(my_list);


int hello_msg(uint myCounter){
    struct my_data *list, *tmp;
    uint i;

    if (myCounter > 10) {
        pr_err(KERN_WARNING "Error, parameter is bigger than 10)\n");
        return -EINVAL;
    } else if (myCounter >= 5 && myCounter <= 10) {
        pr_warn(KERN_WARNING "Parameter is between 5 and 10\n");
    } else if (myCounter == 0){
        pr_warn(KERN_WARNING "Parameter is 0\n");
    }

    for (i = 0; i < myCounter; i++) {
        list = kmalloc(sizeof(struct my_data), GFP_KERNEL);
        if (ZERO_OR_NULL_PTR(list))
            goto tidy_away;
        list->before = ktime_get();
        pr_info("Hello, world!\n");
        list->after = ktime_get();
        list_add_tail(&list->entry, &my_list);
    }
    return 0;

tidy_away:
    list_for_each_entry_safe(list, tmp, &my_list, entry) {
        list_del(&list->entry);
        kfree(list);
    }
    pr_err("Error! No memory\n");
    return -1;
}
EXPORT_SYMBOL(hello_msg);

static int __init my_init(void){
    pr_info("hello1 initiated!\n");
    return 0;
}

static void __exit my_exit(void){
    struct my_data *entry, *tmp;

    list_for_each_entry_safe(entry, tmp, &my_list, entry) {
        pr_info("Time: %lld", entry->after - entry->before);
        list_del(&entry->entry);
        kfree(entry);
    }
    BUG_ON(!list_empty(&my_list));
    pr_info("hello1 unloaded!\n");
}

module_init(my_init);
module_exit(my_exit);
