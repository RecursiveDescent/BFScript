# BFScript

This was a quickly made project to mess around with making a programming language that compiles to BF.
<br>
For now, error handling is at a minimum since getting a prototype working was the priority, so a syntax error will usually just segfault.
There is also a lot of redundant code that wasn't removed after no longer being used.

# Syntax
A compiler backend paired with a proof of concept language that compile to BF.
The language itself was put together extremely fast, so right now not much is supported.

## Variables

`let i = 15`

`i = i - 1`

## Output

`print EXPRESSION`

printing simply outputs a cell from brainfuck using the . command, so outputting numbers isn't supported yet.

## If statements

`if (i == 15) { print i + 50 }`

Only == and > are implemented right now.

## While statements

`while (i > 0) { print i + 65; i = i - 1; }`

# Examples

### Print `ABC`
`let i = 32 * 2 + 1; print i; print i + 1; print i + 2` | `print 65; print 66; print 67`

# TODO
- [ ] Comments
- [ ] Input
- [ ] Functions
- [ ] Loops
- [ ] Operators
- [ ] Standard library
- [ ] ? Native bindings ?