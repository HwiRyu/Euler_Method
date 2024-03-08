![ezgif-7-b69c36f4b8](https://github.com/HwiRyu/Euler_Method/assets/123755711/7baeb340-b509-424e-bb43-c8b5148bbded)

This code can draw parameter functions and single-variable functions, 
and it can find the original function from a differential equation using the Euler method. 

In tracer mode, press the 'T' key to draw the phase line. 
Observe the point moving according to time by pressing the 'F' key.

And for one-variable differential equation, Can find meaningfull error.

Update:


## Euler Method

For the initial problem

$$
\begin{align*}
\frac{dy}{dx} &= f(x, y(x)), \\
y(x_0) &= y_0.
\end{align*}
$$

$$\text{Suppose that} \( f(x, y) \) \text{ satisfies the Lipschitz condition, }\forall x \in [x_0, p], \forall y \in \mathbb{R}.$$

Let

$$
y(x+h) = y(x) + h \cdot f(x, y(x))
$$

$$\text{where } x_k = x_0 + kh.$$

$$\text{For } N = ⌊\frac{p - x_0}{h}⌋,$$

$$y_N \to y(x_N) \text{ as }h \to 0.$$

**Proof:**

$$\text{Let }e_n = y_n - y(x_n) \text{ , }  \( 0 \leq n \leq N \).$$

$$
\begin{align*}
e_{n+1} &= y_{n+1} - y(x_{n+1}) \\
&= y_n + h \cdot f(x_n, y_n) - \left( y(x_n) + h \cdot f(x_n, y(x_n)) + \frac{h^2}{2!} \cdot f'(x_n) + \dots \right) \\
|e_{n+1}| &\leq |y_n - y(x_n)| + h \cdot |f(x_n, y_n) - f(x_n, y(x_n))| + C \cdot h^2 \quad (C > 0, \text{for enough small h.}) \\
&= |e_n| \cdot (1 + L \cdot h) + C \cdot h^2.
\end{align*}
$$

Use induction, then

$$
|e_n| \leq |e_0| \cdot (1 + L \cdot h)^n + C \cdot h^2 \cdot \sum_{k=0}^{n-1} (1 + L \cdot h)^k
$$


$$
|e_n| \leq C \cdot h^2 \cdot \frac{(1 + L \cdot h)^n - 1}{L \cdot h}
$$

Consequently,

$$
|e_N| \leq C \cdot h^2 \cdot (1 + L \cdot h)^N \to 0 \text{ as } h \to 0.
$$
