# stuff

a repository of different smaller projects.

## helper

```bash
python helper/helper.py
```

## pkmn-day

```bash
tcc -ffunction-sections -fdata-sections pkmn-day/main.c
odin build pkmn-day/ -o:aggressive -sanitize:address
```

## rname

```bash
tcc -ffunction-sections -fdata-sections rname/sr.c
```

## rot

rotate 13

```bash
tcc -ffunction-sections -fdata-sections rot/a.c
```

## secret

A little recreational program to encrypt/decrypt data.

> [!DANGER]
> Do NOT use this for real security, this is intended for recreational
> purpose only!

```bash
tcc -ffunction-sections -fdata-sections secret/generate.c -o sg.exe
```

# tsuyu

ref: https://en.wikipedia.org/wiki/Japanese_calendar

```bash
tcc -ffunction-sections -fdata-sections tsuyu/main.c
```
