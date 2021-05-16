timeout --foreground 300 qemu-system-x86_64 \
  -kernel /home/user/bzImage \
  -initrd /home/user/rootfs.cpio \
  -nographic \
  -monitor none \
  -cpu qemu64 \
  -append "console=ttyS0 kaslr panic=1 nosmep nosmap pti=off quiet oops=panic" \
  -no-reboot \
  -m 256M 