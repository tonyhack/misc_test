#include <stdio.h>

#include <unistd.h>

void testFreopen() {
  ::freopen("/dev/null", "r", stdin);
  ::freopen("stdout.io", "w", stdout);
  ::freopen("stderr.io", "w", stderr);

  ::fprintf(stdout, "stdout...\n");
  ::fprintf(stderr, "stderr...");
}

void testFreopen2() {
  ::freopen("/dev/null", "r", stdin);
  ::freopen("stdout.io", "a", stdout);
  ::freopen("stderr.io", "a", stderr);

  if (::daemon(1, 1) != 0) {
    return;
  }

  ::fprintf(stdout, "stdout...\n");
  ::fprintf(stderr, "stderr...");

  // 需要设置行缓冲，不然不能输出
  ::setvbuf(stdout, NULL, _IONBF, 0);
  ::setvbuf(stderr, NULL, _IONBF, 0);

  while (true) {
  }
}

int main(int argc, char *argv[]) {
  // testFreopen();
  testFreopen2();

  return 0;
}

