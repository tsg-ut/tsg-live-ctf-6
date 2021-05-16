CC := gcc
USER := user
EXP := exploit
DIST := dist
KERN := kernel
INC := include
BUILD := build
DEPLOY := deploy
KCHALL := challenge
KHEALTH := healthcheck
# should be built and copied into /dist
DISTOBJ_B = $(DIST)/client $(DIST)/sushi-da.ko $(DIST)/bzImage $(DIST)/rootfs.cpio $(DIST)/run.sh
# use as it is
DISTOBJRAW = 
DISTOBJ = $(DISTOBJRAW) $(DISTOBJ_B) $(DIST)/src
BUILDOBJ = $(BUILD)/client

CPPFLAGS = -o $@
$(USER)/client: CPPFLAGS += -z execstack -static -Wall -O0 -o $@
$(EXP)/exploit: CPPFLAGS += -static -Os -masm=intel -o $@

# user
$(USER)/client: $(USER)/client.c
	$(CC) $(CPPFLAGS) $<

# exploit
$(EXP)/exploit: $(EXP)/exploit.c
	docker run -it --rm -v "$$PWD:$$PWD" -w "$$PWD" alpine /bin/sh -c 'apk add gcc musl-dev linux-headers && $(CC) $(CPPFLAGS) $<'
	#$(CC) $(CPPFLAGS) $<
	strip $@

.INTERMEDIATE: $(EXP)/exploit.gz
$(EXP)/exploit.gz: $(EXP)/exploit
	gzip $<
$(EXP)/exploit.gz.b64: $(EXP)/exploit.gz
	base64 $< > $@

# dist
$(DIST)/sushi-da.tar.gz: $(DISTOBJ)
	rm -rf $@
	tar -C $(DIST) -czf  $(CURDIR)/$@ $(notdir $(DISTOBJ))
	rm -rf $(DIST)/src

.INTERMEDIATE: $(DIST)/client $(DIST)/sushi-da.ko $(DIST)/bzImage $(DIST)/rootfs.cpio
$(DIST)/src: $(INC) $(USER) $(KERN)
	rm -rf $@
	mkdir $@
	rm $(USER)/client
	cp -rf $^ $@
$(DISTOBJ_B): $(DIST)/%: $(BUILD)/%
	cp $< $@

# build
$(BUILD)/client: $(USER)/client
	cp $< $@

# image
$(BUILD)/rootfs.cpio: $(USER)/client $(BUILD)/sushi-da.ko $(BUILD)/init
	rm -rf $(BUILD)/extracted && mkdir $(BUILD)/extracted
	cd $(BUILD)/extracted && cpio -idv < $(CURDIR)/$(BUILD)/rootfs.cpio
	rm -f $@
	echo "TSGLIVE{flag1}" > $(BUILD)/extracted/flag1
	echo "TSGLIVE{flag2}" > $(BUILD)/extracted/flag2
	echo "TSGLIVE{flag3}" > $(BUILD)/extracted/flag3
	cp $^ $(BUILD)/extracted/
	chmod 777 -R $(BUILD)/extracted
	cd $(BUILD)/extracted && find . -print0 | cpio --owner root --null -o --format=newc > $(CURDIR)/$@
	rm -rf $(BUILD)/extracted

# kctf
$(DEPLOY)/rootfs.cpio: $(DIST)/rootfs.cpio
	$(MAKE) -C $(DEPLOY)

# phonies
.PHONY: clean user dist build image $(BUILD)/rootfs.cpio kctf deploy
deploy: Makefile
	$(MAKE) -C deploy
user: $(USER)/client
exp: $(EXP)/exploit.gz.b64
dist: $(DIST)/sushi-da.tar.gz Makefile
	$(MAKE) clean
build: $(BUILDOBJ)
image: $(BUILD)/rootfs.cpio
KCTF_CHALLS := $(DEPLOY)/rootfs.cpio $(BUILD)/bzImage $(BUILD)/run.sh 
KCTF_HEALTH := $(EXP)/exploit.gz.b64 $(EXP)/exploit.py
kctf: $(KCTF_CHALLS) $(KCTF_HEALTH)
	cp $(KCTF_CHALLS) $(KCHALL)
	cp $(KCTF_HEALTH) $(KHEALTH)
	mv $(KHEALTH)/exploit.py $(KHEALTH)/healthcheck.py
	chmod +x ./healthcheck/*
clean:
	rm -f $(USER)/client
	rm -f $(EXP)/exploit
	rm -f $(EXP)/exploit.gz.b64
	rm -rf $(DIST)/src
	rm -rf $(BUILD)/client
	rm -rf $(KCHALL)/rootfs.cpio $(KCHALL)/bzImage $(KCHALL)/run.sh $(KHEALTH)/exploit.gz.b64 $(KHEALTH)/healthcheck.py
	$(MAKE) -C deploy clean
clean-all:
	$(MAKE) clean
	$(MAKE) -C deploy clean-all
	rm -f $(DIST)/sushi-da.tar.gz