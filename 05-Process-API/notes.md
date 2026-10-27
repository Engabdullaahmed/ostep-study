# Chapter 5 — Process API

## fork()

`fork()` → create a new process

```text
        fork()
       /      \
   Parent     Child
```

| | Parent | Child |
|---|---|---|
| `fork()` return | Child PID | `0` |
| `getpid()` | Parent PID | Child PID |
| New process? | No | Yes |
| Continue after `fork()`? | Yes | Yes |

The Parent and Child continue running from the point after `fork()`.

---

## wait()

`wait()` → parent waits for child

```text
Parent
   |
 wait()
   |
wait for child
   |
Child finishes
   |
Parent continues
```

Without `wait()` → the order of execution can be different.

With `wait()` → Parent waits for the Child to finish.

---

## exec()

`exec()` → replace the current program and run another program.

It does **not** create a new process.

```text
Child
  |
exec()
  |
replace current program
  |
run another program
```

Example:

```text
fork()
  ↓
Child
  ↓
exec()
  ↓
run another program
```

---

## Process API

```text
fork()  → create child
wait()  → parent waits
exec()  → run another program
```

---

## kill()

`kill()` → send a signal to a process.

A signal can be used to control a process, for example:

```text
stop
terminate
```

---

## ps

`ps` → command to show running processes and information about them.

```text
ps
 ↓
processes
PID
information
```

---

## top

`top` → continuous view of processes and their resources.

It can show things like:

```text
CPU usage
Memory usage
Processes
```