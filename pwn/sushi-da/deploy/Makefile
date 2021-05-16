rootfs.cpio: ../dist/sushi-da.tar.gz Makefile
	# change flag in rootfs
	cp ../dist/sushi-da.tar.gz .
	tar xvf ./sushi-da.tar.gz
	rm ./sushi-da.tar.gz
	mkdir extracted
	cd extracted && cpio -idv < $(CURDIR)/rootfs.cpio
	rm -f ./rootfs.cpio
	echo "TSGLIVE{pu1pu1m0lc4r_1s_50_cUt3!}" > ./extracted/flag1
	echo "TSGLIVE{l5_1t_t00_345Y?tH3n_pwn_wh013_k3rn31!!}" > ./extracted/flag2
	echo "TSGLIVE{M0r4_5AY_NIRUGIRI_I_4n5w3r3d_NIRUGIRI!!!}" > ./extracted/flag3
	cd ./extracted && find . -print0 | cpio --owner root --null -o --format=newc > $(CURDIR)/rootfs.cpio
	rm -rf $(CURDIR)/extracted

	# remove all
	find . ! -name Makefile ! -name "." ! -name rootfs.cpio | xargs rm -rf

../dist/sushi-da.tar.gz: Makefile
	$(MAKE) -C ../ dist

.PHONY: clean
clean:
	find . ! -name Makefile ! -name "." ! -name rootfs.cpio | xargs rm -rf
clean-all:
	$(MAKE) clean
	rm -f ./rootfs.cpio