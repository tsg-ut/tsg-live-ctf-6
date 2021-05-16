#!/bin/sh

set -eu

# Dockerfile	b64dir.py	flag.txt	nsjail.cfg	run.sh		setpriv		start.sh
cp challenge/b64dir.py dist/
cp challenge/run.sh dist/
cp challenge/Dockerfile dist/
cp challenge/start.sh dist/
tar czvf dist.tar.gz dist/
