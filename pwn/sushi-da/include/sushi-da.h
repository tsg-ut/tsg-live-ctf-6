#define SUSHI_REGISTER_RECORD 0xdead001
#define SUSHI_FETCH_RECORD 0xdead002
#define SUSHI_CLEAR_OLD_RECORD 0xdead003
#define SUSHI_CLEAR_ALL_RECORD 0xdead004

#define SUSHI_RECORD_MAX 0x10
#define SUSHI_NAME_MAX 0x10

struct record{
  char date[0x10];
  unsigned long result;
};

struct ioctl_register_query{
  struct record record;
};

struct ioctl_fetch_query{
  unsigned rank;
  struct record record;
};