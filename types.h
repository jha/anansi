#ifndef TYPES_H
#define TYPES_H

typedef enum {
    FALSE   = 0,
    TRUE    = 1
} bool_t;

#define LOG_PREFIX "[anansi] "
#define LOG(fmt, ...) printk(KERN_INFO LOG_PREFIX fmt "\n", ##__VA_ARGS__)

#define MODULE_EXIT_SUCCESS 0
#define MODULE_EXIT_FAILURE 1

#endif /* TYPES_H */
