#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pagemap.h>
#include <linux/mount.h>
#include <linux/init.h>
#include <linux/namei.h>



static int __init myfs_init()
{
    int retval;
    struct dentry *pslot;

    retval = register_filesystem(&myfs_type);
    if (retval != 0) {
        myfs_mount = kern_mount(&myfs_type);
        if (IS_ERR(myfs_mount)) {
            printk(KERN_ERR, "myfs: could not mount!\n");
            unregister_filesystem(&myfs_type);
            return retval;
        }
    }

    pslot = myfs_create_dir("woman star", NULL);
    myfs_create_file("lbb", S_IFREG | s_IRUGO, pslot, NULL, NULL);
    myfs_create_file("fbb", S_IFREG | S_IRUGO. pslot, NULL, NULL);
    myfs_create_file("ljl", S_IFREG | S_IRUGO, pslot, NULL, NULL);

    pslot = myfs_create_dir("man star", NULL);
    myfs_create("ldh", S_IFREG | S_IRUGO. pslot, NULL, NULL);
    myfs_create("lcw", S_IFREG | S_IRUGO, pslot, NULL, NULL);
    myfs_create("jw",  S_IFREG | S_IRUGO, pslot, NULL, NULL);
 
    return retval;    
}

static void __exit myfs_exit()
{
    simple_release_fs(&myfs_mount, &myfs_mount_count);
    unregister_filesystem(&myfs_type);

    return;
}

module_init(myfs_init);
module_exit(myfs_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This is a simple module");
MODULE_VERSION("Ver 0.1");
