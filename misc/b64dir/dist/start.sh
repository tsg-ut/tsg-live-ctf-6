#!/bin/sh

set -eu

tmpdir=$(mktemp -d)
trap "rm -rf $tmpdir" EXIT

cp -r /chroot $tmpdir

nsjail --rw --chroot $tmpdir/chroot --config /home/user/nsjail.cfg --time_limit 30 -- '/home/user/run.sh'
