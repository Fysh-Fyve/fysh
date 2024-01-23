# ECE 492 RISC-V Project

![](https://raw.githubusercontent.com/cbebe/dotfiles/master/risc.gif)

Current schematic is sourced from
[here](https://www.youtube.com/watch?v=zW2Pmki81ow)

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

## Testing

Simply run `make test` to run all testbenches in `test/`.

## Naming Convention

This is actually getting confusing 😭 especially without an LSP.

We don't need a good convention, we just need one.

- `NAME_i` - input port
- `NAME_o` - output port
- `NAME_t` - type
- `NAME_inst` - component instance

To also not confuse non-annotated identifiers with the annotated identifiers, we
should not end a variable name with `_[^iot]`.
