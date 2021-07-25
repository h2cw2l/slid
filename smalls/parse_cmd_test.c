#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static int32_t parse_cmd(int argc, char *const argv[])
{
    int32_t c = 0;

    while ((c = getopt(argc, argv, "i:p:t:m:c:n:h")) != -1) {
        switch (c) {
        case 'i':
            char *addr = optarg;
            printf("server addr:%s %s\n", g_client.serv, optarg);
            break;
        case 'h':
        default:
            printf("server: ./netlib_test_server -p [port] -m [size] -c [count] -n [numa_node]\n");
            printf("server: ./netlib_test_client -i [ip] -p [port] -m [size] -c [count] -n [numa_node]\n");
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
  parse_cmd(argc, argv);
  
  printf("2 argc %d, [0] %s, [1] %s\n", argc, argv[0], argv[1]);
  for (int i = 1; i < argc; i++) {
      argv[i] = NULL;
  }


  return 0;
}

