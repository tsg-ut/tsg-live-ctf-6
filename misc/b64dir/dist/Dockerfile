FROM alpine as chroot

RUN apk add --update --no-cache python3 bash && ln -sf python3 /usr/bin/python

RUN adduser -D -u 1000 user

COPY --chown=root:user ./flag.txt /home/user/flag.txt
COPY --chown=root:user ./b64dir.py /home/user/b64dir.py
COPY --chown=root:user ./run.sh /home/user/run.sh
RUN mv /home/user/flag.txt /home/user/flag-$(md5sum /home/user/flag.txt | awk '{print $1}').txt

FROM gcr.io/kctf-docker/challenge@sha256:6dd60da626bc43bf3175d9d7436006db5acc7710d5d1b7006ab53e718fe51e40

COPY --chown=user:user --from=chroot / /chroot

COPY nsjail.cfg /home/user/
COPY start.sh /home/user/

EXPOSE 5010

CMD  kctf_setup && kctf_drop_privs socat \
      TCP-LISTEN:5010,reuseaddr,fork \
      EXEC:"/home/user/start.sh"
