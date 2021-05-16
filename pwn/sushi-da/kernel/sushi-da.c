#include<linux/errno.h>
#include<linux/file.h>
#include<linux/fs.h>
#include<linux/miscdevice.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/kernel.h>

#include"../include/sushi-da.h"

struct record *records[SUSHI_RECORD_MAX];

long register_record(void *arg)
{
  struct ioctl_register_query request;
  struct record *ent;
  int ix;
  long ret = -EINVAL;

  if(copy_from_user(&request, (struct ioctl_register_query*)arg, sizeof(request)))
    goto end;

  ent = kzalloc(sizeof(struct record), GFP_KERNEL);
  if(IS_ERR_OR_NULL(ent))
    goto end;
  memcpy(ent, &request.record, sizeof(struct record));

  for(ix=0; ix!=SUSHI_RECORD_MAX; ++ix){
    if(records[ix] == (struct record*)0){
      records[ix] = ent;
      break;
    }
  }

  ret = 0;
end:
  return ret;
}

long fetch_record(void *arg)
{
  unsigned req_rank;
  char rank_index[SUSHI_RECORD_MAX], target_index;
  struct ioctl_fetch_query request;
  int ix, jx;
  long ret = -EINVAL;

  if(copy_from_user(&request, (struct ioctl_fetch_query*)arg, sizeof(request))) goto end;
  req_rank = request.rank - 1;

  // calc ranking
  for(ix=0; ix!=SUSHI_RECORD_MAX; ++ix){
    unsigned char count = 0;
    if(records[ix] == (struct record*)0){
      rank_index[ix] = -99;
      continue;
    }
    for(jx=0; jx!=SUSHI_RECORD_MAX; ++jx){
      if(ix == jx) continue;
      else if(records[jx] != (struct record*)0 && records[jx]->result < records[ix]->result) 
        ++count;
    }
    rank_index[ix] = count;
  }
  for(target_index=0; target_index!=SUSHI_RECORD_MAX; ++target_index){
    if(rank_index[(unsigned)target_index] == req_rank) break;
  }
  if(target_index == SUSHI_RECORD_MAX) goto end;

  if(copy_to_user(&((struct ioctl_fetch_query*)arg)->record, records[(unsigned)target_index], sizeof(struct record))){
    goto end;
  }

  ret = 0;
end:
  return ret;
}

long clear_old_records(void)
{
  int ix;
  char tmp[5] = {0};
  long date;
  for(ix=0; ix!=SUSHI_RECORD_MAX; ++ix){
    if(records[ix] == NULL) continue;
    strncpy(tmp, records[ix]->date, 4);
    if(kstrtol(tmp, 10, &date) != 0 || date <= 1990) kfree(records[ix]);
  }
  return 0;
}

long clear_all_records(void){
  int ix;
  for(ix=0; ix!=SUSHI_RECORD_MAX; ++ix) records[ix] = 0;
  return 0;
}

static long sushi_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  switch(cmd){
    case SUSHI_REGISTER_RECORD:
      return register_record((void*)arg);
    case SUSHI_FETCH_RECORD:
      return fetch_record((void *)arg);
    case SUSHI_CLEAR_OLD_RECORD:
      return clear_old_records();
    case SUSHI_CLEAR_ALL_RECORD:
      return clear_all_records();
    default:
      return -EINVAL;
  }
}

static const struct file_operations sushi_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = sushi_ioctl,
};

static struct miscdevice sushi_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "sushi-da",
	.fops = &sushi_fops,
};

static void setup_default_ranking(void)
{
  static struct record haru_urara = {
      .date = "2001/12/24\x00",
      .result = 0,
  };
  static struct record toukai_teio = {
      .date = "2021/05/16\x00",
      .result = 20,
  };
  static struct record raisu_shower = {
      .date = "2021/05/01\x00",
      .result = 12,
  };
  records[0] = &haru_urara;
  records[1] = &toukai_teio;
  records[2] = &raisu_shower;
}

static int __init sushi_init(void)
{
  setup_default_ranking();
  return misc_register(&sushi_device);
}

static void __exit sushi_exit(void)
{
	misc_deregister(&sushi_device);
}

module_init(sushi_init);
module_exit(sushi_exit);
MODULE_AUTHOR("TSGLIVE");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Stay foolish, stay sushi.");