# ECE 492 RISC-V Project

## Prequisites

```
sudo apt install ghdl
```

If you want to format the code, you will need `emacs`.

```
sudo apt install emacs
```

Then run:

```
make -j fmt
```

## Naming Convention

This is actually getting confusing 😭 especially without an LSP.

We don't need a good convention, we just need one.

- Identifiers
    - `NAME_i` - input port
    - `NAME_o` - output port
    - `NAME_s` - signal
    - `NAME_t` - type

- Labels
    - `NAME_u` - component instance
    - `NAME_p` - process
    - `NAME_g` - generate
