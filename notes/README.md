# Notes

DSP and C++ notes for this project: explanations in my own words, equations,
and code snippets. One file per topic, listed below.

Cite the source for anything taken from a book (e.g. "Smith, ch. 2").

## Topics

<!-- - [Power and decibels](power-and-db.md) -->


## Syntax cheat sheet

Math is LaTeX, and GitHub renders it.

| Write | Renders as |
|---|---|
| `$x^2$`, `$x_n$`, `$x[n]$` | $x^2$, $x_n$, $x[n]$ |
| `$\frac{a}{b}$`, `$\sqrt{x}$` | $\frac{a}{b}$, $\sqrt{x}$ |
| `$\sum_{n=0}^{N-1} x[n]$` | $\sum_{n=0}^{N-1} x[n]$ |
| `$\|x\|$`, `$\log_{10}$` | $\|x\|$, $\log_{10}$ |
| `$\pi$`, `$\omega$`, `$\theta$`, `$\Delta f$` | $\pi$, $\omega$, $\theta$, $\Delta f$ |
| `$e^{j \omega n}$`, `$\cos(\theta)$` | $e^{j \omega n}$, $\cos(\theta)$ |
| `$P_{\text{dB}}$` | $P_{\text{dB}}$ |

Inline math goes between single dollar signs. A display equation on its own
line goes between double dollar signs:

$$
P = \frac{1}{N} \sum_{n=0}^{N-1} |x[n]|^2
$$

Code snippets use fenced blocks with a language:

```cpp
float power = std::norm(sample);
```
