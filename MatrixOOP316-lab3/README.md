# Matrix

## Description

This project implements the classic **“digital rain”** effect from *The Matrix* in the Windows console.

Two modes of parameter input are supported:

* **Interactive mode** (default) — the program prompts the user for parameters one by one, with validation.
* **CLI mode** — parameters are passed as command-line arguments.

## Parameters and Example Launch

```bash
  make build
 ./solution.out <spawnRate> <speed> <length> <epilepsy> <explosionChance> <minRadius> <maxRadius>
# Пример:
./solution.out 3 23 8 Y 250 2 6
```

> Explosion: when triggered, a line shrinks by one character in length (until it disappears completely).
> Explosion symbols spread radially (in console discretization), and the explosion color is random and independent of epilepsy mode.
> Explosion animation runs strictly at 2 steps per second (every 500 ms), regardless of speed.

### Interactive Mode

```bash
 make run
```

The program will prompt for the required parameters (depending on version/branch).

### Help

```bash
make help
```


## Архитектура (коротко)

* **Figure** — abstract base class (polymorphic methods for stepping, drawing, and completion).
* **Line** — manages the motion of a “rhombic” line and supports shortening after explosions.
* **Explosion** — explosion animation with clipping to screen boundaries, independent timing.
* **Manager** — single main loop (single thread): schedules line spawns at intervals, calls `step()` on figures, and adds/removes figures.

## Build and Run (Linux)

```bash
make build
make run
```

## Notes
* Constraints:

  * `speed ∈ [1;30]`, `length ∈ [1;30]`, `spawnRate ∈ [1;30]`
  * `explosionChance ∈ [1;1000]`, `1 ≤ minRadius ≤ maxRadius ≤ 10`

---
