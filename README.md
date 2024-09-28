# compiler_v2

An optimising compiler for a statically typed language targetting the x86
architecture.

```
let integer: i32 = 1;
const boolean: bool = true;

fn function(arg: i32) -> bool {
    return arg < 10;
}

let arr: i32[10];
for (let i: i32 = 0; i < 10; i++) {
    arr[i] = i * 10;
}

if (arr[0] == integer) {
    print("equal");
} elif (arr[0] > integer) {
    print("greater");
} else {
    print("less");
}
```

## [ ] v1

For the initial version, we'll implement this part of the language:

```
let a: i32 = 1;
let b: i32 = 2;

a = (a - b) / 2;

print(a + 2);
```

We'll need to implement:

1. Scanner & Tokens
2. Parser & AST
4. Variable resolution
5. Typechecker
6. AST -> TAC
7. TAC -> x86


## [ ] v2

Once the pipeline is all setup, we want to make sure working on it is as easy
as possible. This means tests and debug information.

Alongside decent test coverage, we should be able to get the following for any
execution;

1. List of tokens
2. A dump of the symbol table
3. `mermaid` graph visualisation of type-annotated AST
4. The x86 with the TAC instructions annotated


## [ ] v3

At this stage we have a full pipeline for arithmetic. Then, we'll introduce
booleans and boolean related expressions.

```
let x: bool = true;

print(1 < 2 || x == false && 1 != 3);
```

This will help us get used to adding onto the pipeline.


## [ ] v4

-- if statements --


## [ ] v5

-- basic blocks in the IR --


## [ ] v6

-- loops --


## [ ] v7

-- functions ?maybe --


## [ ] v8

-- optimisations (?) --
