# Chapter 14 – Memory API

## 1. Types of Memory

There are two main types of memory:

### Stack Memory
- Automatically managed by the compiler.
- Used for local variables and function calls.
- Memory is automatically reclaimed when the function returns.

### Heap Memory
- Used for dynamic memory allocation.
- Managed by the programmer using memory allocation functions.
- Memory remains allocated until it is explicitly released or the process exits.

## 2. Memory Allocation Functions

| Function | Purpose |
|---|---|
| `malloc()` | Allocates memory without initializing it. |
| `calloc()` | Allocates memory and initializes all bytes to zero. |
| `realloc()` | Resizes an existing memory allocation. |
| `free()` | Releases dynamically allocated memory. |
| `strdup()` | Creates a dynamically allocated copy of a string. |
| `sizeof()` | Operator that returns the size of a type or object in bytes. |

### malloc() Example

```c
int *ptr = malloc(10 * sizeof(int));

if (ptr == NULL) {
    return 1;
}

free(ptr);
```

- `malloc()` returns a pointer to allocated memory or `NULL` on failure.
- `malloc()` does not initialize the allocated memory.
- Always check whether allocation succeeded.

### calloc() Example

```c
int *arr = calloc(10, sizeof(int));
```

Allocates memory for 10 integers and initializes all allocated bytes to zero.

### realloc() Example

```c
int *temp = realloc(arr, 10 * sizeof(int));

if (temp != NULL) {
    arr = temp;
}
```

- Resizes an existing allocation.
- May extend the allocation in place or move it to another location.
- Use a temporary pointer to avoid losing the original allocation if resizing fails.

### free() Example

```c
free(ptr);
ptr = NULL;
```

- Releases dynamically allocated memory.
- Takes the original pointer returned by an allocation function.
- Does not automatically set the pointer to `NULL`.

## 3. Common Memory Errors

| Error | Description |
|---|---|
| Forgetting to Allocate | Using a pointer without allocating valid memory. |
| Buffer Overflow | Writing beyond allocated memory boundaries. |
| Uninitialized Memory | Reading allocated memory before initializing it. |
| Memory Leak | Forgetting to release allocated memory. |
| Dangling Pointer | Using a pointer after its memory has been freed. |
| Double Free | Releasing the same allocation more than once. |
| Invalid Free | Passing an invalid pointer to `free()`. |

### Best Practices
- Allocate enough memory for the required data.
- Initialize memory before reading it.
- Release memory when it is no longer needed.
- Never access memory after freeing it.
- Avoid double free and invalid free operations.
- Set pointers to `NULL` after freeing when appropriate.

## 4. Memory Management: Application vs OS

Memory management has two levels:

1. **Application Level:** The program manages its heap using functions such as `malloc()` and `free()`.
2. **OS Level:** The operating system manages process memory and reclaims its resources when the process exits.

Memory leaks are especially dangerous in long-running applications because they can accumulate over time.

## 5. System Calls vs Library Functions

### System Call
A mechanism through which a program requests a service from the OS Kernel.

### Library Function
A reusable function provided by a library. It may or may not use system calls internally.

| Comparison | System Call | Library Function |
|---|---|---|
| Provider | OS Kernel interface | Software Library |
| Purpose | Request OS services | Provide reusable functionality |
| Kernel interaction | Enters the Kernel | Not necessarily |
| Examples | `read()`, `write()`, `mmap()` | `malloc()`, `free()`, `strlen()` |

**Important:** `malloc()` and `free()` are library functions, not system calls. The memory allocator may request additional memory from the OS using mechanisms such as `brk()` or `mmap()`.

## 6. Underlying OS Support

| Interface | Purpose |
|---|---|
| `brk()` | Changes the program break (end of the data segment). |
| `sbrk()` | Adjusts the program break by an increment. |
| `mmap()` | Creates memory mappings in a process's virtual address space. |

- `malloc()` does not necessarily invoke a system call every time.
- The allocator may reuse memory it already manages.
- Avoid calling `brk()` and `sbrk()` directly in normal applications.

## 7. Memory Debugging Tools

**Valgrind:** Helps detect memory leaks and invalid memory accesses.

```bash
valgrind --leak-check=full ./program
```

## Key Takeaways

- Stack: Automatically managed memory.
- Heap: Dynamically allocated memory.
- `malloc()`: Allocate memory.
- `calloc()`: Allocate and zero-initialize memory.
- `realloc()`: Resize allocated memory.
- `free()`: Release allocated memory.
- Memory management requires avoiding leaks, invalid access, and buffer overflows.
- The OS reclaims a process's memory resources when it exits.