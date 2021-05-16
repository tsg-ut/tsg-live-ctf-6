#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<string.h>
#include<time.h>
#include"../include/sushi-da.h"

#define SUSHI_PATH "/dev/sushi-da"
#define MAX_LENGTH 200
#define die(msg) exit(puts(msg));
#define warn_ret(msg) {puts(msg); return;}

char wordlist[4][MAX_LENGTH] = {
  "We play amongus every nights, can you join us?",
  "TSG stands for Theoretical Science Group? No, it does for Torturer's Six-shooter for Gokiburi!",
  "We have sushi-bot in our Slack. Sometimes, it DDoSushi us.",
  "\x00",
};

void register_record(int result){
  int fd;
  time_t now; time(&now);
  struct tm *t = localtime(&now);
  struct ioctl_register_query q = {.record.result = result};
  if((fd = open(SUSHI_PATH, O_RDWR)) <= 2) warn_ret("[ERROR] failed to open sushi. check if the module is loaded.");
  strftime(q.record.date, sizeof(q.record.date), "%Y/%m/%d", t);
  if(ioctl(fd, SUSHI_REGISTER_RECORD, &q) < 0)
    die("[ERROR] failed to register record");
}
unsigned readn(char *buf, unsigned n){
  int ix;
  for(ix=0; ix!=n-1; ++ix){
    if(read(0, buf + ix, 1) <= 0 || buf[ix] == '\n'){
      buf[ix] = '\x00';
      break;
  }}
  return ix;
}

void wait_ready(void){
  printf("3, 🍣  ");  usleep(500 * 1000);
  printf("2, 🐟  ");  usleep(500 * 1000);
  printf("1, 🍙  ");  usleep(500 * 1000);
  puts("Go...! 🏃🏃\n");
}

void play_game()
{
  unsigned success = 0;
  struct {
    unsigned long start, result;
    char type[MAX_LENGTH + 0x20];
    int pro;
  } info = {0};
  wait_ready();
  info.start = time(NULL);

  while(success < 3){
    unsigned question = rand() % 4;
    if(wordlist[question][0] == '\x00') continue;
    printf("[TYPE]\n");
    printf(wordlist[question]); puts("");
    readn(info.type, 200);
    if(strncmp(wordlist[question], info.type, strlen(wordlist[question])) != 0)  warn_ret("🙅‍🙅 ACCURACY SHOULD BE MORE IMPORTANT THAN SPEED.");
    ++success;
  }
  info.result = time(NULL) - info.start;
  puts("\n[ENTER] again to finish!");
  readn(info.type, 0x200);

  printf("\n🎉🎉🎉Congrats! You typed in %lu secs!🎉🎉🎉\n", info.result);
  register_record(info.result);
  if(info.pro != 0) system("cat flag1");
}

void show_ranking(void)
{
  int fd;
  if((fd = open(SUSHI_PATH, O_RDWR)) <= 2) warn_ret("[ERROR] failed to open sushi. check if the module is loaded.");
  struct ioctl_fetch_query q;
  puts("\n🍣🍣🍣 Hall of Sushi 🍣🍣🍣");
  for (int ix = 0; ix != 3; ++ix){
    q.rank = ix + 1;
    if (ioctl(fd, SUSHI_FETCH_RECORD, &q) < 0) break;
    printf("%d: %ld sec : %s\n", ix + 1, q.record.result, q.record.date);
  }
  puts("🍣🍣🍣🍣🍣🍣🍣🍣🍣🍣🍣🍣🍣");
}

void add_phrase(void){
  char *buf = malloc(MAX_LENGTH + 0x20);
  printf("[NEW PHRASE] ");
  readn(buf, MAX_LENGTH - 1);
  for(int ix=0; ix!=MAX_LENGTH-1; ++ix){
    if(buf[ix] == '\xa') break;
    memcpy(wordlist[3]+ix, buf+ix, 1);
  }
}

void setup(){
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

int main(int argc, char *argv[]){
  char buf[0x100];
  srand(time(NULL));
  setup();

  while(1==1){
    printf("\n\n$ ");
    if (readn(buf, 100) <= 0) die("[ERROR] readn");
    if(strncmp(buf, "play", 4) == 0)
      play_game();
    else if(strncmp(buf, "rank", 4) == 0)
      show_ranking();
    else if(strncmp(buf, "custom", 5) == 0)
      add_phrase();
    else if (strncmp(buf, "exit", 4) == 0)
      break;
    else
      puts("commands: play rank custom exit");
  }
  puts("\nStay foolish, stay sushi...");
}
