# USAGE
- `make dist`: compile `dist/sushi-da.tar.gz` to distribute.
- `make exp`: compile exploit. It uses docker to compile exploit with musl-libc.
- `make kctf`: compile and place files for kCTF deploy.
- `make clean`: remove intermidiate files
- `make clean-all`: remove all files
- `make deploy`: compile file-system for deploy.

# SUSHI-DA1

## Description
Eat sushi, just eat sushi.

## Difficulty Estimate
baby

## Note
- Flag for this chall is `/home/user/flag1`.
- You **DON'T HAVE TO** use the distributed kernel to pwn `flag1` and `flag2`. You can simply **USE ONLY `CLIENT`** binary for debug purpose.
- The userland binary is compiled with `-static`, so libc is not distributed.

# SUSHI-DA2
## Description
Mora says **pwning is to get a shell**. I know. Then get the shell, as you want...

## Difficulty Estimate
med-easy

## Note
- Flag for this chall is `/home/user/flag2`.
- You **DON'T HAVE TO** use the distributed kernel to pwn `flag1` and `flag2`. You can simply **USE ONLY `CLIENT`** binary for debug purpose.
- The userland binary is compiled with `-static`, so libc is not distributed.
- The chall uses the files of `SUSHI-DA1`.

# SUSHI-DA3 
Hey, you got a shell! What? You're not satisfied til you get root? OK, pwn the root, if you can.
## Difficulty Estimate
hard

## Note
- Flag for this chall is `/home/user/flag3`.
- **If you are the member of UT team, it'd be wiser to solve challs from other genres,** though this challs is designed to be solved in time. 
- The chall uses the files of `SUSHI-DA1`.
