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

## [X] v0

For the initial version, we'll implement this part of the language:

```
print(1 + 2 / 3 * (4 - 1))
```

Simply print statements with arithmetic. This requires:

1. Scanner
2. Parser & AST
3. AST -> TAC
4. TAC -> x86


## [ ] v1

Then, we'll introduce declarations, types, and assignments.

```
let a: i32 = 1;
let b: i32 = 2;

a = b;

print(a + 2);
```

This will help us get used building out that previous pipeline. We'll also 
need to add *variable resolution*, to ensure assignment targets are valid.

## [ ] v2

Once the pipeline is all setup, we want to make sure working on it is as easy
as possible. This means tests and debug information.

Alongside decent test coverage, we should be able to get the following for any
execution;

1. List of tokens
2. A dump of the symbol table
3. `mermaid` graph visualisation of the AST
4. The x86 with the TAC instructions annotated


## [ ] v3

At this stage we have a full pipeline for arithmetic and assignments.
Then, we'll introduce booleans and boolean related expressions.

```
let x: bool = true;

print(1 < 2 || x == false && 1 != 3);
```

This will require a *type checker*, to ensure our both arithmetic and
assignment are well defined (e.g. false < 5 is not valid).

## [ ] v4

We'll need to introduce scope and flesh out scoping rules. This is a
natural first step towards if statements, loops, and so forth which
all have their own scope.

```
var a = 1;
{
    var a = 2;
    {
        a = 3;
        print(a); // 3
    }

    print(a); //3
}

print(a); // 1
```

There will be a number of edge cases to iron out.


## [ ] v5

-- if statements --


## [ ] v6

-- basic blocks in the IR --


## [ ] v7

-- loops --


## [ ] v8

-- functions ?maybe --


## [ ] v8

-- optimisations (?) --
