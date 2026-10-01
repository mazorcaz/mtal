# MTAL: A C-inspired low level language

`mtal` is an iteration on C that attempts to fix common pain points
while being ABI compatible.

## Hello World

```
$inc ctypes.h

cint_t printf(cchar_t*);

int main()
{
	printf("Hello, world\n");
}
```
