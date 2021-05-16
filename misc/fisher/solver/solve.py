import soundfile as sf
import numpy as np
from utils import signals_to_string

frames, samplerate = sf.read('../challenge/result.wav')
vs = [0] * 473
for i, frame in enumerate(frames):
  if frame == 0:
    continue
  if abs(frame) > 0.01:
    continue
  d = np.arcsin(frame)
  d /= 2 * np.pi
  d *= 4410000
  a = int(np.round(d)) * pow(43997, -1, 4410000) % 4410000
  if a // 2000 < 473:
    vs[a // 2000] = 1

print(signals_to_string(vs))

