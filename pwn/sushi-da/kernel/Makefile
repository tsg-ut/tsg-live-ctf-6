obj-m += sushi-da.o
BUILDHOME=/home/wataru/buildroot-2020.08.1/output/build/linux-4.19.98

all:
	make -C $(BUILDHOME) M=$(PWD) modules

clean: 
	make -C $(BUILDHOME) M=$(PWD) clean 