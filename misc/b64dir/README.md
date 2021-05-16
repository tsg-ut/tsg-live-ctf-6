# b64dir

base64をディレクトリにも適用できるようにしてみたよ

```
$ ls test
k	p	t
$ python b64dir.py --enc test
dGVzdAB0ZXN0L3QAMTEAdGhlb3JlbW9vbgp0ZXN0L2sAOQBrdXJlbmFpZgp0ZXN0L3AAMTAAcHRyLXl1ZGFpCg==
$ rm -rf test
$ python b64dir.py
dGVzdAB0ZXN0L3QAMTEAdGhlb3JlbW9vbgp0ZXN0L2sAOQBrdXJlbmFpZgp0ZXN0L3AAMTAAcHRyLXl1ZGFpCg==
test
$ ls test
k	p	t
```

サーバーにデプロイしてみたよ(`run.sh`)

```
$ nc 35.187.220.104 5010
dGVzdAB0ZXN0L3QAMTEAdGhlb3JlbW9vbgp0ZXN0L2sAOQBrdXJlbmFpZgp0ZXN0L3AAMTAAcHRyLXl1ZGFpCg==
k
p
t
```

